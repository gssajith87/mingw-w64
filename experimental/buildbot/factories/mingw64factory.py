# -*- python -*-
# ex: set syntax=python:

# This is the config for just the MinGW-W64 build factory
# See master.cfg for the actual main script

import buildbot, os
from buildbot.process import factory
from buildbot.steps.source import CVS, SVN
from buildbot.steps.shell import Configure, Compile, ShellCommand, WithProperties, SetProperty
from buildbot.steps.transfer import FileDownload, FileUpload
from buildbot.steps.trigger import Trigger
from scripts.buildsteps import M64CVS, M64NightlyRev, ShellCommandConditional
import re

class Mingw64Factory(factory.BuildFactory):
  clobber = True
  target = "x86_64-w64-mingw32"
  gccConfigExtraArgs = "--enable-fully-dynamic-string --disable-multilib"
  crtConfigExtraArgs = ""
  binutilsConfigExtraArgs = ""
 
  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # set properties about this builder
    self.addStep(SetProperty(property="basedir",
                             command=["bash", "-c", """pwd | sed 's@\\\\\\\\@/@g; s@^\\\\(.\\\\):@/\\\\1@ '"""],
                             haltOnFailure=True))

    if self.host_pair:
      # we have a host pair specified
      self.addStep(SetProperty(property="host-pair",
                               command=["echo", self.host_pair]))
    else:
      # unknown host pair, fall back to buildername
      self.addStep(SetProperty(property="host-pair",
                               command=["echo", WithProperties("%(buildername)s")]))

    target_os = "unknown"
    for os_mask in [ { "expr": "x86_64", "value": "w64" },
                     { "expr": "i.86",   "value": "w32" } ]:
      if re.match(os_mask["expr"], self.target) is not None:
        target_os = os_mask["value"]
        break
    self.addStep(SetProperty,
                 command=["echo", target_os],
                 property="target-os")

    self.addStep(SetProperty(property="target_arch",
                             command=["echo", self.target]))

    self.addStep(SetProperty(property="gcc_config_args",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%%(gcc_config_args:-%s)s" % (self.gccConfigExtraArgs))]))
    self.addStep(SetProperty(property="mingw_config_args",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%%(mingw_config_args:-%s)s" % (self.crtConfigExtraArgs))]))
    self.addStep(SetProperty(property="binutils_config_args",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%%(binutils_config_args:-%s)s" % (self.binutilsConfigExtraArgs))]))

    self.addStep(SetProperty(property="gcc_branch",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%(gcc_branch:-trunk)s")]))
    self.addStep(SetProperty(property="gcc_revision",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%(gcc_revision:-head)s")]))
    self.addStep(SetProperty(property="mingw_revision",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%(mingw_revision:-head)s")]))
    self.addStep(SetProperty(property="binutils_revision",
                             command=["python", "-c", "import sys ; print ' '.join(sys.argv[1:])",
                                      WithProperties("%(binutils_revision:-)s")]))


    # set up build root
    if self.clobber:
      self.addStep(ShellCommand(name="clobber",
                                workdir=".",
                                command=["rm", "-rfv", "build"],
                                haltOnFailure=False,
                                description=["clobber all"],
                                descriptionDone=["clobbered"]))

    # force the build/ directory to exist so we can download into it
    self.addStep(ShellCommand(name="mkdir-build",
                              description=["mkdir", "build/"],
                              workdir="build",
                              command=["echo", ""],
                              haltOnFailure=True))

    self.addStep(FileDownload(mastersrc="mingw-makefile",
                              slavedest="mingw-makefile",
                              maxsize=102400,
                              mode=0600,
                              haltOnFailure=True))

    self.addStep(FileDownload(name="src-download",
                              mastersrc="mingw-w64-src.tar.bz2",
                              slavedest="mingw-w64-src.tar.bz2",
                              mode=0644,
                              haltOnFailure=True))

    # Normally, this ends up being a no-op; it's used for custom forced builds to pull gcc
    self.addStep(Compile(name="src-archive",
                         description=["source archive", "create"],
                         descriptionDone=["source archive", "created"],
                         command=["make", "-f", "mingw-makefile", "src-archive"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "GCC_BRANCH" : WithProperties("%(gcc_branch)s"),
                              "GCC_REVISION": WithProperties("%(gcc_revision)s"),
                              "MINGW_REVISION": WithProperties("%(mingw_revision)s"),
                              "BINUTILS_REVISION": WithProperties("%(binutils_revision)s")}))

    self.addStep(Compile(name="src-extract",
                         description=["source", "extract"],
                         descriptionDone=["source", "extracted"],
                         command=["make", "-f", "mingw-makefile", "src-extract"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s"),
                              "SRC_ARCHIVE": WithProperties("%(src_archive)s")}))

    # Install mingw headers
    self.addStep(Compile(name="mingw-headers-install",
                         description=["mingw headers install"],
                         command=["make", "-f", "mingw-makefile", "headers-install"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Make binutils
    self.addStep(Configure(name="binutils-configure",
                           description=["binuils", "configure"],
                           descriptionDone=["binutils", "configured"],
                           command=["make", "-f", "mingw-makefile", "binutils-configure"],
                           env={"BINUTILS_CONFIG_EXTRA_ARGS": WithProperties("%(binutils_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="binutils-compile",
                         description=["binutils compile"],
                         descriptionDone=["binutils compiled"],
                         command=["make", "-f", "mingw-makefile", "binutils-compile"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="binutils-install",
                         description=["binutils install"],
                         descriptionDone=["binutils installed"],
                         command=["make", "-f", "mingw-makefile", "binutils-install"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Make bootstrap gcc
    self.addStep(Configure(name="gcc-configure",
                           description=["gcc configure"],
                           descriptionDone=["gcc configured"],
                           command=["make", "-f", "mingw-makefile", "gcc-configure"],
                           env={"GCC_CONFIG_EXTRA_ARGS": WithProperties("%(gcc_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-bootstrap-compile",
                         description=["bootstrap gcc compile"],
                         descriptionDone=["bootstrap gcc compiled"],
                         command=["make", "-f", "mingw-makefile", "gcc-bootstrap-compile"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-bootstrap-install",
                         description=["bootstrap gcc install"],
                         descriptionDone=["bootstrap gcc install"],
                         command=["make", "-f", "mingw-makefile", "gcc-bootstrap-install"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Compile CRT
    self.addStep(Configure(name="crt-configure",
                           description=["CRT configure"],
                           descriptionDone=["CRT configured"],
                           command=["make", "-f", "mingw-makefile", "crt-configure"],
                           env={"MINGW_CONFIG_EXTRA_ARGS": WithProperties("%(mingw_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="crt-compile",
                         description=["CRT compile"],
                         descriptionDone=["CRT compiled"],
                         command=["make", "-f", "mingw-makefile", "crt-compile"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="crt-install",
                         description=["CRT install"],
                         descriptionDone=["CRT installed"],
                         command=["make", "-f", "mingw-makefile", "crt-install"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Compile full gcc
    self.addStep(Compile(name="gcc-compile",
                         description=["gcc compiled"],
                         descriptionDone=["gcc compile"],
                         command=["make", "-f", "mingw-makefile", "gcc-compile"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-install",
                         description=["gcc install"],
                         descriptionDone=["gcc installed"],
                         command=["make", "-f", "mingw-makefile", "gcc-install"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s")}))


    # make the tarball
    self._step_Archive()

    # upload the tarball (to the build master)
    self.addStep(FileUpload,
                 slavesrc=WithProperties("%(filename)s"),
                 masterdest=WithProperties("%(filename)s"),
                 mode=0644,
                 haltOnFailure=True)

    # tell the master to upload the file to sourceforge
    self.addStep(Trigger,
                 schedulerNames=["sourceforge-upload"],
                 waitForFinish=True,
                 set_properties={"masterdir": WithProperties("%(masterdir)s"),
                                 "target-os": WithProperties("%(target-os)s"),
                                 "filename": WithProperties("%(filename)s"),
                                 "destname": WithProperties("%(destname)s"),
                                 "datestamp": WithProperties("%(datestamp:-)s"),
                                 "is_nightly": WithProperties("%(is_nightly:-)s")})

  def _step_Archive(self):
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-%(target-os)s-bin_%(host-pair)s.tar.bz2")],
                 property="filename")
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-%(target-os)s-bin_%(host-pair)s%(host-extra:-)s%(datestamp:-)s.tar.bz2")],
                 property="destname")
    # make the tarball
    self.addStep(ShellCommand,
                 name="makedist",
                 description=["tarball", "package"],
                 workdir="build/build/root",
                 command=["tar",
                          "cjf",
                          WithProperties("../../%(filename)s"),
                          "--owner", "0",
                          "--group", "0",
                          "--checkpoint",
                          "--exclude=.svn",
                          "."],
                 haltOnFailure=True)
                

class Mingw64Linux32Factory(Mingw64Factory):
  host_pair = "i686-linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64Linux64Factory(Mingw64Factory):
  host_pair = "x86_64-linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64CygwinFactory(Mingw64Factory):
  host_pair = "i686-cygwin"
  #gccConfigExtraArgs = "--enable-bootstrap"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_Archive(self):
    self.addStep(SetProperty(property="host-extra",
                             command=["bash", "-c",
                                      """cygcheck -c -d cygwin | perl -ne 'm/^cygwin\s+(\S+)/ and print "-$1"'"""]))
    return Mingw64Factory._step_Archive(self)
 
class Mingw64MingwFactory(Mingw64Factory):
  host_pair = "i686-mingw"
  #gccConfigExtraArgs = "--enable-bootstrap"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_Archive(self):
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-%(target-os)s-bin_%(host-pair)s.zip")],
                 property="filename")
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-%(target-os)s-bin_%(host-pair)s%(datestamp:-)s.zip")],
                 property="destname")
    # make the tarball
    self.addStep(ShellCommand,
                 name="makedist",
                 description=["zipfile", "package"],
                 workdir="build/build/root",
                 command=["zip",
                          "-r",
                          "-9",
                          "-v",
                          WithProperties("../../%(filename)s"),
                          ".",
                          "-x", ".svn"],
                 haltOnFailure=True)

class Mingw32Linux32Factory(Mingw64Linux32Factory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64Linux32Factory.__init__(self, **kwargs)

class Mingw32Linux64Factory(Mingw64Linux64Factory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64Linux64Factory.__init__(self, **kwargs)

class Mingw32CygwinFactory(Mingw64CygwinFactory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64CygwinFactory.__init__(self, **kwargs)

class Mingw32MingwFactory(Mingw64MingwFactory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64MingwFactory.__init__(self, **kwargs)

