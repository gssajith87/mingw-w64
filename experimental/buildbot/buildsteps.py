# -*- python -*-

from buildbot.steps.shell import ShellCommand, SetProperty
from buildbot.steps.trigger import Trigger
from buildbot.status.builder import SKIPPED
from buildbot.process.properties import WithProperties
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

class SetPropertyConditional(SetProperty):
    """Sets a property if a different property (given by "condprop") is set"""
    def __init__(self,
                 condprop=None,
                 condinvert=False,
                 condvalue=None,
                 conddefault=None,
                 **kwargs):
        SetProperty.__init__(self, **kwargs)
        self.addFactoryArguments(condprop=condprop,
                                 condinvert=condinvert,
                                 condvalue=condvalue,
                                 conddefault=conddefault)
        self.condProp = condprop
        self.condInvert = condinvert
        self.condValue = condvalue
        self.condDefault = conddefault

    def start(self):
        if self.condProp is not None:
            value = self.condDefault
            matched = False
            if self.build.getProperties().has_key(self.condProp):
                value = self.build.getProperty(self.condProp)
            elif self.condDefault is None:
                # no value and no default, assume we want to execute
                matched = True

            if not matched:
                if self.condValue is None:
                    matched = bool(value)
                else:
                    matched = (value == self.condValue)
                if self.condInvert:
                    matched = not matched

            if not matched:
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

        # substract one from datestamp because we want the rev before that
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
    def __init__(self,
                 prop_prefix="",
                 config_dir=".",
                 **kwargs):

        if kwargs.has_key("command"):
           del kwargs["command"]
        if kwargs.has_key("extract_fn"):
           del kwargs["extract_fn"]

        command = ["svn", "info", "--xml", "--incremental",
                   "--config-dir", config_dir, "--no-auth-cache", "--non-interactive"]
        SetPropertyConditional.__init__(self,
                                        extract_fn=self._extract,
                                        command=command,
                                        **kwargs)
        self.addFactoryArguments(prop_prefix=prop_prefix,
                                 config_dir=config_dir)
        self.prop_prefix = prop_prefix

    def _extract(self, rc, stdout, stderr):
        dom = minidom.parseString(stdout)
        revision = dom.documentElement.getAttribute("revision")
        datestring = dom.getElementsByTagName("date")[0].firstChild.nodeValue
        datestamp = datetime.datetime.strptime(datestring[:-7], "%Y-%m-%dT%H:%M:%S.")
        datestring = datestamp.strftime("%Y-%m-%d")
        return { self.prop_prefix + 'revision': revision,
                 self.prop_prefix + 'datestamp': datestring }

class WithPropertiesRecursive(WithProperties):
    """
    This is a version of WithProperties that knows to recursively expand
    """

    def getRenderingFor(self, build):
        origfmtstring = self.fmtstring
        if isinstance(origfmtstring, WithProperties):
            self.fmtstring = origfmtstring.getRenderingFor(build)

        try:
            ret = WithProperties.getRenderingFor(self, build)
        finally:
            self.fmtstring = origfmtstring

        return ret
