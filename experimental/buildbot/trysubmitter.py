# vim: set et sw=2 :

""" buildbot resource for submitting try server patches via HTTP """

from twisted.web.resource import Resource
#from twisted.web.error import ErrorPage
from twisted.web import http
import twisted.web.server
from buildbot.sourcestamp import SourceStamp
import os, time, random

DEBUG = False

class TrySubmitter(Resource):
  """ a IResource to accept submission of a patch for the try server """

  def __init__(self, trydir, builders=[], userpass=None):
    Resource.__init__(self)
    self.builders = builders
    self.path = trydir
    if userpass is not None:
      assert len(userpass) is 2
    self.userpass = userpass

  def render(self, request):
    """ Check for HTTP basic auth, and pass to normal rendering if accepted """

    try:
      self.projectName = request.site.buildbot_service.parent.projectName
    except:
      self.projectName = ""

    if self.userpass is not None:
      if request.getUser() != self.userpass[0] or request.getPassword() != self.userpass[1]:
        realm = "%s buildbot tryserver" % self.projectName

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
          <title>Buildbot try submit</title>
          <style type="text/css">
      textarea {
        display: block;
        height: 80%%;
        width: 100%%;
      }
          </style>
        </head>
        <body>
          <form method="post" action="/try">
            <h1>%s buildbot try server request submission</h1>
            <input type="submit" accesskey="s">
            <nobr>
              <label for="branch">Branch:</label>
              <input name="branch" id="branch" accesskey="b">
            </nobr>
            <nobr>
              <label for="rev">Revision:</label>
              <input name="rev" id="rev" accesskey="r" size="8">
            </nobr>
            <nobr>
              <label for="patchlevel">Patch Level:</label>
              <input name="patchlevel" id="patchlevel" accesskey="l" value="1" size="2">
            </nobr>
      """ % (self.projectName))
    checked = 'checked="true"'
    for builder in self.builders:
      request.write("""
        <nobr>
          <input type="checkbox" name="builder" value="%s" id="%s" accesskey="b" %s>
          <label for="%s">%s</label>
        </nobr>
        """ % (builder, builder, checked, builder, builder))
      checked = ""
    request.write("""
            <textarea name="patch" accesskey="p"></textarea>
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
    request.write("""
      <style type="text/css">
        .error {
          color: red;
        }
      </style>
      """)
    if not request.args.has_key("patch"):
      request.write("no patch submitted")
      request.finish()
      return twisted.web.server.NOT_DONE_YET

    patch = "\n".join(request.args["patch"])
    
    #ss = SourceStamp(self.branch, self.baserev, (self.patchlevel, patch))
    # generate random unique build stamp id
    bsid = "%d-%s" % (time.time(), random.randint(0, 1000000))

    if request.args.has_key("branch"):
      branch = str(request.args["branch"][0])
    else:
      branch = None

    if request.args.has_key("rev"):
      rev = str(request.args["rev"][0])
    else:
      rev = None

    if request.args.has_key("builder"):
      builders = request.args["builder"]
    else:
      builders = self.builders
    for builder in builders:
      if not builder in self.builders:
        request.write("""<div class="error">builder <code>%s</code> unknown</div>""" % builder)

    patchlevel = 1 # default vaule
    if request.args.has_key("patchlevel"):
      try:
        lvl = int(request.args["patchlevel"][0])
        if lvl >= 0:
          patchlevel = lvl
      except (TypeError, ValueError):
        pass

    request.write("""submitting patch:<br>
                     revision <code>%s</code> branch <code>%s</code> with patchlevel <code>%s</code> to builders <i>%s</i>
                     <pre style="border: 1px inset; padding: 0.5em; ">%s</pre>
                  """ % ((rev or "HEAD"), (branch or "trunk"), patchlevel, ", ".join(builders), patch))

    def ns(s):
      return "%d:%s," % (len(s), s)
  
    job = ""
    job += ns("1") # jobspec version
    job += ns(bsid) # build stamp id
    job += ns(str(branch or ""))
    job += ns(str(rev or ""))
    job += ns("%d" % patchlevel)
    job += ns(patch)
    for name in builders:
      job += ns(name)

    if DEBUG:
      request.write("""<pre class="error">%s</pre>""" % job)
    else:
      path = os.path.join(self.path, "new", bsid)
      f = open(path, "w")
      f.write(job)
      f.close()

    request.finish()
    return twisted.web.server.NOT_DONE_YET


