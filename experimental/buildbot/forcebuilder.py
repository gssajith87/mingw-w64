# vim: set et sw=2 :

""" buildbot resource for submitting forced builds with custom properties """

from twisted.web.resource import Resource
from twisted.web.error import ErrorPage
from twisted.web import http
from twisted.python import log
import twisted.web.server

from buildbot import interfaces
from buildbot.sourcestamp import SourceStamp
from buildbot.status.web.base import HtmlResource
from buildbot.process.base import BuildRequest
from buildbot.process.properties import Properties
import os, time, random, cgi, re, datetime

DEBUG = False

class ForceBuilder(HtmlResource):
  """ a IResource to accept forcing a build with custom properties """

  type = ""

  def __init__(self, builders=[], userpass=None, properties={}):
    Resource.__init__(self)
    self.builders = builders
    if userpass is not None:
      assert len(userpass) is 2
    self.userpass = userpass
    self.properties = properties

  def setProperty(self, name, value):
    self.properties[name] = value

  def render(self, request):
    """ Check for HTTP basic auth, and pass to normal rendering if accepted """

    try:
      self.projectName = request.site.buildbot_service.parent.projectName
    except:
      self.projectName = ""

    if self.userpass is not None:
      if request.getUser() != self.userpass[0] or request.getPassword() != self.userpass[1]:
        realm = "%s buildbot force builder" % self.projectName

        request.setHeader('WWW-Authenticate',
                          'Basic Realm="%s"' % realm)
        errpage = ErrorPage(http.UNAUTHORIZED,
                            "Unauthorized",
                            "401 Authentication required")
        return errpage.render(request)
    return Resource.render(self, request)

  def render_header(self, request):
    request.write("""
      <html>
        <head>
          <title>%(projectName)s Buildbot %(title)s</title>
          <style type="text/css">
      body[type="warn"] {
        background-color: #FFEEEE;
      }
      textarea {
        display: block;
        height: 80%%;
        width: 100%%;
      }
      select, input:not([type="submit"]):not([type="checkbox"]) {
        min-width: 20em;
        width: 100%%;
      }
          </style>
        </head>
        <body type="%(type)s">
          <h1>%(projectName)s Buildbot %(title)s</h1>
      """ % {
        'projectName': self.projectName,
        'title'      : self.title,
        'type'       : self.type,
      })

  def render_GET(self, request):
    self.render_header(request)
    request.write("""
          <form method="post" action="%(url)s">
            <input type="submit" accesskey="s">
      """ % {
        'url'        : request.URLPath()
      })
    checked = 'checked="true"'
    for builder in self.builders:
      request.write("""
        <nobr>
          <input type="checkbox" name="builder" value="b_%(builder)s" id="b_%(builder)s" accesskey="b" %(checked)s>
          <label for="b_%(builder)s">%(builder)s</label>
        </nobr>
        """ % ({
          'builder': builder,
          'checked': checked
        }))
      checked = ""
    request.write("""
        <table width="100%">
          <tr>
            <th>Name</th>
            <th width="100%">Value</th>
          </tr>
        """)
    for prop in sorted(self.properties):
      request.write("""
              <tr>
                <th><label for="p_%(prop)s">%(prop)s</label></th>
                <td>
        """ % {'prop': prop})
      if prop == "datestamp":
        # special case datestamp to use the current date
        request.write("""
          <input name="p_%s" id="p_%s" type="text" value="%s">
          """ % (prop, prop, datetime.date.today().strftime("_%Y%m%d")))
      elif type(self.properties[prop]) is str:
        request.write("""
          <input name="p_%s" id="p_%s" type="text" value="%s">
          """ % (prop, prop, self.properties[prop]))
      elif type(self.properties[prop]) is bool:
        request.write("""
          <input name="p_%s" id="p_%s" type="checkbox" %s>
          """ % (prop, prop, {True: "checked='true'", False: ""}[self.properties[prop]]))
      elif type(self.properties[prop]) is list:
        request.write("""<select name="p_%s" id="p_%s">""" % (prop, prop))
        for item in self.properties[prop]:
          request.write("""<option value="%s">%s</option>""" % (str(item), str(item)))
      else:
        request.write("ERROR: " + str(self.properties[prop]))
      request.write("""
                </td>
              </tr>
        """)
    request.write("""
              <tr>
                <td colspan="2">
                  <hr>
                </td>
              </tr>
              <tr>
                <th>
                  Your name:
                </th>
                <td>
                  <input type="text" name="username">
                </td>
              </tr>
              <tr>
                <th>
                  Reason:
                </th>
                <td>
                  <input type="text" name="comments">
                </td>
              </tr>
            </table>
          </form>
        </body>
      </html>
      """)

    if DEBUG:
      object = request.site.buildbot_service.parent
      for i in dir(object):
        request.write("%s<br> " % i)
      request.write("<pre>%s</pre>" % str(object).replace("<", "&lt;"))

    request.finish()
    return twisted.web.server.NOT_DONE_YET

class ForceBuilderSlave(ForceBuilder):
  title = "Force Build"

  def render_POST(self, request):
    self.render_header(request)
    controller = self.getControl(request)
    if not controller:
      return "no control allowed"

    builders = request.args.get("builder", [])
    if len(builders) < 1:
      return "no builders specified!"
    for builder in builders:
      if not builder.startswith("b_"):
        return cgi.escape("""invalid builder "%s" specified""" % (builder[2:]))
      if not builder[2:] in self.builders:
        return cgi.escape("""unknown builder "%s" specified""" % (builder[2:]))

    builders = [builder[2:] for builder in builders]

    name = str(request.args.get("username", [""])[0])
    if len(name) < 1:
      name = "<unknown>"

    reason = str(request.args.get("comments", [""])[0])
    if len(reason) < 1:
      reason = "<no reason specified>"

    properties = Properties()
    for prop_name in request.args:
      if not prop_name[:2] == "p_":
        continue
      if request.args[prop_name][0] == "-":
        continue
      properties.setProperty(prop_name[2:],
                             request.args[prop_name][0],
                             "ForceBuilder")

    r = "The force builder was initiated by '%s': %s\n" % (name, reason)
    log.msg("web force build with properties for builders=[%s]"
            " by user '%s'" % (" ".join(builders), name))

    for builder in builders:
      builder_control = controller.getBuilder(builder)
      if not builder_control:
        request.write("ERROR: control for builder %s not available" % (cgi.escape(builder)))
        continue

      s = SourceStamp(branch=None, revision=None)
      req = BuildRequest(r, s, builderName=builder, properties=properties)
      try:
        builder_control.requestBuildSoon(req)
        request.write("successfully submitted request for %s<br>" % (cgi.escape(builder)))
      except interfaces.NoSlaveError:
        request.write("build for builder %s failed, no slave available<br>" % (cgi.escape(builder)))

    request.write("""
      Build request submitted.
      <a href="../waterfall">Back to waterfall</a>
      """)
    request.finish()
    return ""

class ForceBuilderSrc(ForceBuilder):
  title = "Force Source Build"
  type = "warn"

  def render_POST(self, request):
    self.render_header(request)
    controller = self.getControl(request)
    if not controller:
      return "no control allowed"

    builders = request.args.get("builder", [])
    if len(builders) < 1:
      return "no builders specified!"
    for builder in builders:
      if not builder.startswith("b_"):
        return cgi.escape("""invalid builder "%s" specified""" % (builder[2:]))
      if not builder[2:] in self.builders:
        return cgi.escape("""unknown builder "%s" specified""" % (builder[2:]))

    builders = [builder[2:] for builder in builders]

    name = str(request.args.get("username", [""])[0])
    if len(name) < 1:
      name = "<unknown>"

    reason = str(request.args.get("comments", [""])[0])
    if len(reason) < 1:
      reason = "<no reason specified>"

    properties = Properties()
    for prop_name in request.args:
      if not prop_name[:2] == "p_":
        continue
      if request.args[prop_name][0] == "-":
        continue
      properties.setProperty(prop_name[2:],
                             request.args[prop_name][0],
                             "ForceBuilder")

    properties.setProperty("builders",
                           ",".join(["trigger-" + builder for builder in builders]),
                           "ForceBuilder")

    r = "The force builder was initiated by '%s': %s\n" % (name, reason)
    log.msg("web force build with properties for builders=[%s]"
            " by user '%s'" % (" ".join(builders), name))

    builder_control = controller.getBuilder("src-package")
    if not builder_control:
      request.write("ERROR: control for builder %s not available" % ("src-package"))

    else:
      s = SourceStamp(branch=None, revision=None)
      req = BuildRequest(r, s, builderName="src-package", properties=properties)
      try:
        builder_control.requestBuildSoon(req)
        request.write("successfully submitted request for %s<br>" % ("src-package"))
      except interfaces.NoSlaveError:
        request.write("build for builder %s failed, no slave available<br>" % ("src-package"))

      request.write("""
        Build request submitted.
        <a href="../waterfall">Back to waterfall</a>
        """)
    request.finish()
    return ""

