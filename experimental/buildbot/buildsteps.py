# -*- python -*-

from buildbot.steps.shell import ShellCommand, SetProperty
from buildbot.status.builder import SKIPPED
import datetime
from xml.dom import minidom

class M64CVS(ShellCommand):
    def __init__(self, cvsroot, cvsmodule, workdir=None,
                 branch=None,
                 global_options=[],
                 checkoutDelay=None,
                 **kwargs):
        assert checkoutDelay is None
        if workdir is None:
            workdir = cvsmodule
        self.cvsmodule = cvsmodule

        ShellCommand.__init__(self, **kwargs)
        command = (["cvs", '-d', cvsroot, '-z3'] +
                   global_options +
                   ["checkout", '-d', workdir, '-N'])
        if branch:
            command += ['-r', branch]
#        if self.revision:
#            command += ['-D', revision]
        command += [cvsmodule]
        self.setCommand(command)

    def describe(self, done=False):
        if not done:
            return ["pulling " + self.cvsmodule]
        else:
            return [self.cvsmodule + " pulled"]

class ShellCommandConditional(ShellCommand):
    """Runs a remote command if a property (given by "condprop") is set"""
    def __init__(self, **kwargs):
        self.condProp = None
        self.condValue = None
        self.condInvert = False

        if kwargs.has_key('condprop'):
            self.condProp = kwargs['condprop']
            del kwargs['condprop']
        if kwargs.has_key('condvalue'):
            self.condValue = kwargs['condvalue']
            del kwargs['condvalue']
        if kwargs.has_key('condinvert'):
            self.condInvert = kwargs['condinvert']
            del kwargs['condinvert']

        ShellCommand.__init__(self, **kwargs)

    def start(self):
        if self.condProp is not None:
            if self.build.getProperties().has_key(self.condProp):
                matched = True
                if self.condValue is None:
                    matched = self.build.getProperty(self.condProp)
                else:
                    matched = (self.build.getProperty(self.condProp) == self.condValue)
                if self.condInvert:
                    matched = not matched
                if not matched:
                    return SKIPPED
        ShellCommand.start(self)

class SetPropertyConditional(SetProperty):
    """Sets a property if a different property (given by "condprop") is set"""
    def __init__(self, **kwargs):
        self.condprop = None

        if kwargs.has_key('condprop'):
            self.condprop = kwargs['condprop']
            del kwargs['condprop']

        SetProperty.__init__(self, **kwargs)

    def start(self):
        if self.condprop is not None:
            if not (self.build.getProperties().has_key(self.condprop) and
                    self.build.getProperty(self.condprop)):
                # we have a conditional that's not met
                return SKIPPED
        SetProperty.start(self)

class M64NightlyRev(SetPropertyConditional):
    """Sets the revision based on the gcc daily time stamp"""
    def __init__(self, **kwargs):
        SetPropertyConditional.__init__(self,
                                        condprop='is_nightly',
                                        extract_fn=self._extract,
                                        command=None,
                                        **kwargs)

    def start(self):
        now = datetime.datetime.utcnow()
        nowstamp = now.strftime("%Y%m%d")

        # XXX Mook: extra hack for mingw because it has trouble passing {} to svn
        argtemplate = "{%sT0000Z}:{%sT0030Z}"
        if (self.build.getProperties().has_key("platform") and
            self.build.getProperty("platform")[-5:] == "mingw"):
            argtemplate = "\\{%sT0000Z\\}:\\{%sT0030Z\\}"

        command = ['svn', 'log', '-r',
                   (argtemplate % (nowstamp, nowstamp)),
                   '--non-interactive', '--no-auth-cache',
                   'svn://gcc.gnu.org/svn/gcc/trunk']
        self.setCommand(command)

        # substract one from datestamp because we we want te rev before that
        yesterday = now - datetime.timedelta(1)
        self.datestamp = yesterday.strftime("%Y%m%d")

        return SetPropertyConditional.start(self)

    def _extract(self, rc, stdout, stderr):
        if not (self.build.source.revision is None and
          self.build.source.branch is None and
          self.build.source.patch is None):
            # don't ever overwrite revisions
            return { }
        for line in stdout.split("\n"):
            fields = line.split("|")
            if len(fields) != 4 or fields[1] != " gccadmin ":
                continue
            # just overriding the revision property doesn't affect the pull
            # so we modify the source stamp directly instead
            # but we still return it, so it's marked as being set here
            rev = fields[0].strip("r ")
            rev = int(rev) - 1
            self.build.source.revision = rev
            return { 'revision'  : rev,
                     'datestamp' : ("_%s" % self.datestamp) }
        # if we reach here, we failed to find a revision
        return { }

class SubversionRevProperty(SetPropertyConditional):
    """Sets a revision property based on a check out"""
    def __init__(self, **kwargs):
        if kwargs.has_key('prop_prefix'):
            self.prop_prefix = kwargs['prop_prefix']
            del kwargs['prop_prefix']
        else:
            self.prop_prefix = ""

        command = ["svn", "info", "--xml", "--incremental",
                   "--config-dir", ".", "--no-auth-cache", "--non-interactive"]
        SetPropertyConditional.__init__(self,
                                        extract_fn=self._extract,
                                        command=command,
                                        **kwargs)

    def _extract(self, rc, stdout, stderr):
        dom = minidom.parseString(stdout)
        revision = dom.documentElement.getAttribute("revision")
        datestring = dom.getElementsByTagName("date")[0].firstChild.nodeValue
        datestamp = datetime.datetime.strptime(datestring[:-7], "%Y-%m-%dT%H:%M:%S.")
        datestring = datestamp.strftime("%Y-%m-%d")
        return { self.prop_prefix + 'revision': revision,
                 self.prop_prefix + 'datestamp': datestring }
