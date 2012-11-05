# vim: set et sw=2 :

""" buildbot resource for submitting forced builds with custom properties """

from twisted.web.resource import Resource
#from twisted.web.error import ErrorPage
from twisted.web.util import Redirect
from twisted.web import http
from twisted.python import log
import twisted.web.server

from buildbot import interfaces
from buildbot.sourcestamp import SourceStamp
from buildbot.status.web.base import HtmlResource, path_to_authfail, path_to_root
#from buildbot.process.base import BuildRequest
from buildbot.process.properties import Properties
import os, time, random, cgi, re, datetime
import itertools

DEBUG = False

class ForceBuilderBase(HtmlResource):
  """ Base class for both sorts of force builders """
  addSlash = True

  def __init__(self, builders=[], properties={}):
      HtmlResource.__init__(self)
      self.builders = builders
      self.properties = properties

  def setProperty(self, name, value):
    self.properties[name] = value

  def getChild(self, path, req):
    if path == "build":
      if not self.getAuthz(req).actionAllowed('forceBuild',
                                              req):
        return Redirect(path_to_authfail(req))
      return self.build(req)
    return HtmlResource.getChild(self, path, req)

  def getBuilders(self, req):
    builders = req.args.get("builder", [])
    if len(builders) < 1:
      return [None, BuildError("no builders specified!", req)]
    for builder in builders:
      if not builder.startswith("b_"):
        return [None,
                BuildError("""invalid builder "%s" specified""" % (builder[2:]),
                           req)]
      if not builder[2:] in self.builders:
        return [None,
                BuildError("""unknown builder "%s" specified""" % (builder[2:]),
                           req)]
    return [[b[2:] for b in builders], None]

  def getProperties(self, req):
    properties = Properties()
    for i in itertools.count(0):
      pname = req.args.get("property%dname" % i, [""])[0]
      pvalue = req.args.get("property%dvalue" % i, [""])[0]
      if not pname or not pvalue:
        break
      properties.setProperty(pname, pvalue, "Custom Force Build Form")
    return [properties, None]

  def build(self, req):
    [builders, error] = self.getBuilders(req)
    if error is not None:
      return error

    reason = str(req.args.get("comments", [""])[0])
    if len(reason) < 1:
      reason = "<no reason specified>"
    
    [properties, error] = self.getProperties(req)
    if error is not None:
      return error

    log.msg("web force build with properties for builders=[%s]" % (
      " ".join(builders)))

    failed_builders = []
    control = interfaces.IControl(self.getBuildmaster(req))
    source_stamp = SourceStamp(branch=None, revision=None)
    for builder_name in builders:
      bc = control.getBuilder(builder_name)
      if not bc:
        failed_builders.append((builder_name, "Failed to get builder controller"))
        log("could not force build %s - failed to get build control" % (
            builder_name))
        continue
      try:
        bc.submitBuildRequest(source_stamp, reason, properties)
      except interfaces.NoSlaveError:
        failed_builders.append((builder_name, "No slave available"))
    
    if (len(failed_builders) > 0):
      reasons = ["<dt>%s</dt><dd>%s</dd>" % (
                 cgi.escape(x[0]), cgi.escape(x[1])) for x in failed_builders]
      return BuildError("The following builders failed to build: <dl>%s</dl>" % (
                        "\n".join(reasons)), req, False)

    # this isn't an error, but at this point I'm feeling lazy
    # it should realy be a templated html instead
    HTML = "<p>Build request submitted.</p>"
    return BuildError(HTML, req, False)

class BuildError(HtmlResource):
  def __init__(self, msg, req = None, escape = True):
    if escape:
      self.msg = cgi.escape(msg)
    else:
      self.msg = msg

    if req:
      self.suffix = """<p>back to <a href="%s">waterfall</a>.</p>""" % (
        path_to_root(req) + "waterfall")
    else:
      self.suffix = ""

  def render(self, req):
    req.write(self.msg)
    req.write(self.suffix)
    req.finish()
    return ""

class ForceBuilder(ForceBuilderBase):
  """ a page to start forced builds as-is """

  def getTitle(self, req):
      return ("Buildbot: %s force build" %
              (self.getBuildmaster(req).projectName))

  def content(self, req, cxt):
    cxt['builders'] = self.builders
    cxt['properties'] = self.properties
    cxt['now'] = datetime.date.today().strftime("_%Y%m%d")
    cxt['authz'] = self.getAuthz(req)
    cxt['build_url'] = '/'.join([] + req.prepath + ['build'])
    template = req.site.buildbot_service.templates.get_template("force.html")
    return template.render(**cxt)

class ForceBuilderSrc(ForceBuilderBase):
  """ a page to start forced builds while re-pulling the source """

  def getTitle(self, req):
      return ("Buildbot: %s force build (+source)" %
              (self.getBuildmaster(req).projectName))

  def content(self, req, cxt):
    cxt['builders'] = self.builders
    cxt['properties'] = self.properties
    cxt['now'] = datetime.date.today().strftime("_%Y%m%d")
    cxt['authz'] = self.getAuthz(req)
    cxt['build_url'] = '/'.join([] + req.prepath + ['build'])
    cxt['warn'] = True
    template = req.site.buildbot_service.templates.get_template("force.html")
    return template.render(**cxt)

  def getProperties(self, req):
    [properties, error] = ForceBuilderBase.getProperties(self, req)
    if error is not None:
      return [None, error]
    [builders, error] = ForceBuilderBase.getBuilders(self, req)
    if error is not None:
      return [None, error]
    properties.setProperty("builders",
                           ",".join(["trigger-" + b for b in builders]),
                           "Custom Force Build Form")
    return [properties, None]

  def getBuilders(self, req):
    return [["src-package"], None]
