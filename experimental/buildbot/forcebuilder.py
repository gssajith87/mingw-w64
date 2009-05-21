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
import os, time, random, cgi, re

DEBUG = False

class ForceBuilder(HtmlResource):
  """ a IResource to accept forcing a build with custom properties """

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

  def render_GET(self, request):
    request.write("""
      <html>
        <head>
          <title>%(projectName)s Buildbot Force Build</title>
          <style type="text/css">
      textarea {
        display: block;
        height: 80%%;
        width: 100%%;
      }
          </style>
        </head>
        <body>
          <form method="post" action="%(url)s">
            <h1>%(projectName)s buildbot force build</h1>
            <input type="submit" accesskey="s">
      """ % {
        'projectName': self.projectName,
        'url'        : request.URLPath()
      })
    checked = 'checked="true"'
    for builder in self.builders:
      request.write("""
        <nobr>
          <input type="checkbox" name="builder" value="%(builder)s" id="%(builder)s" accesskey="b" %(checked)s>
          <label for="%(builder)s">%(builder)s</label>
        </nobr>
        """ % ({
          'builder': builder,
          'checked': checked
        }))
      checked = ""
    request.write("""
        <table>
          <tr>
            <th>Name</th>
            <th>Value</th>
          </tr>
        """)
    for prop in self.properties:
      request.write("""
              <tr>
                <th>%(prop)s</th>
                <td>
        """ % {'prop': prop})
      if type(self.properties[prop]) is str:
        request.write("""
          <input name="p_%s" type="text" value="%s">
          """ % (prop, self.properties[prop]))
      elif type(self.properties[prop]) is list:
        request.write("""<select name="p_%s">""" % (prop))
        for item in self.properties[prop]:
          request.write("""<option value="%s">%s</option>""" % (str(item), str(item)))
      else:
        request.write("ERROR: " + str(self.properties[prop]))
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
              <tr>
                <th>
                  Branch:
                </th>
                <td>
                  <input type="text" name="branch">
                </td>
              </tr>
              <tr>
                <th>
                  Revision:
                </th>
                <td>
                  <input type="text" name="revision">
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


  def render_POST(self, request):
    controller = self.getControl(request)
    if not controller:
      return "no control allowed"

    builders = request.args.get("builder", [])
    if len(builders) < 1:
      return "no builders specified!"
    for builder in builders:
      if not builder in self.builders:
        return cgi.escape("""unknown builder "%s" specified""" % (builder))

    name = str(request.args.get("username", [""])[0])
    if len(name) < 1:
      name = "<unknown>"

    reason = str(request.args.get("comments", [""])[0])
    if len(reason) < 1:
      reason = "<no reason specified>"

    branch = request.args.get("branch", [""])[0]
    revision = request.args.get("revision", [""])[0]

    # keep weird stuff out of the branch and revision strings. TODO:
    # centralize this somewhere.
    if not re.match(r'^[\w\.\-\/]*$', branch):
        log.msg("bad branch '%s'" % branch)
        return Redirect("..")
    if not re.match(r'^[\w\.\-\/]*$', revision):
        log.msg("bad revision '%s'" % revision)
        return Redirect("..")
    if not branch:
        branch = None
    if not revision:
        revision = None
    
    properties = Properties()
    for prop_name in request.args:
      if not prop_name[:2] == "p_":
        continue
      properties.setProperty(prop_name[2:],
                             request.args[prop_name][0],
                             "ForceBuilder")

    r = "The force builder was initiated by '%s': %s\n" % (name, reason)
    log.msg("web force build with properties for builders=[%s], branch='%s', revision='%s'"
            " by user '%s'" % (" ".join(builders), branch, revision, name))

    for builder in builders:
      builder_control = controller.getBuilder(builder)
      if not builder_control:
        request.write("ERROR: control for builder %s not available" % (cgi.escape(builder)))
        continue

      s = SourceStamp(branch=branch, revision=revision)
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


