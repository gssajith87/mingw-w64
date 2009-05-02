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

class Mingw64Factory(factory.BuildFactory):
  clobber = True
  target = "x86_64-pc-mingw32"
  gccConfigExtraArgs = ["--disable-multilib"]
  crtConfigExtraArgs = []
 
  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # set properties about this builder
    self.addStep(SetProperty,
                 command=["bash", "-c", "pwd"],
                 property="basedir")

    if self.platform:
      # we have a platform specified
      self.addStep(SetProperty,
                   command=["echo", self.platform],
                   property="platform")
    else:
      # unknown platform, fall back to buildername
      self.addStep(SetProperty,
                   command=["echo", WithProperties("%(buildername)s")],
                   property="platform")

    self.addStep(M64NightlyRev)

    # set up build root
    if self.clobber:
      self.addStep(ShellCommand,
                   name="clobber",
                   workdir=".",
                   command=["rm", "-rfv", "build"],
                   haltOnFailure=False,
                   description=["clobber all"],
                   descriptionDone=["clobbered"])

    self.addStep(FileDownload,
                 name="root-script",
                 workdir=".",
                 mastersrc="scripts/root-init.sh",
                 slavedest="root-init.sh",
                 maxsize=102400,
                 mode=0755,
                 haltOnFailure=True)

    self.addStep(ShellCommand,
                 name="root-init",
                 workdir=".",
                 command=["bash", "-x", "./root-init.sh"],
                 haltOnFailure=True,
                 env={'TGT': self.target},
                 description=["root initializing"],
                 descriptionDone=["root initialized"])

    self.addStep(FileDownload,
                 name="exec-script",
                 workdir="build",
                 mastersrc="scripts/wrapped-exec.sh",
                 slavedest="wrapped-exec.sh",
                 maxsize=102400,
                 mode=0755,
                 haltOnFailure=True)

    self.addStep(FileDownload,
                 name="src-download",
                 workdir="build",
                 mastersrc="mingw-w64-src.tar.bz2",
                 slavedest="mingw-w64-src.tar.bz2",
                 mode=0644,
                 haltOnFailure=True)
    self.addStep(ShellCommand,
                 name="src-extract",
                 workdir="build",
                 description=["source extract"],
                 descriptionDone=["source extracted"],
                 command=["tar", "xvjpf", "mingw-w64-src.tar.bz2"])

    # Install mingw headers
    self.addStep(ShellCommand,
                 name="mingw-headers-install",
                 description=["mingw headers install"],
                 workdir="build/root/%s/include" % self.target,
                 command="tar cf - --exclude=.svn -C ../../../mingw/mingw-w64-headers/include . | tar xpvf -")

    # Make binutils
    self.addStep(Configure,
                 name="binutils-configure",
                 description=["binuils configure"],
                 descriptionDone=["binutils configured"],
                 workdir="build/binutils/obj",
                 command=["bash",
                            "../src/configure", 
                            "--target=%s" % self.target,
                            WithProperties("--prefix=%s/root", "basedir"),
                            WithProperties("--with-sysroot=%s/root", "basedir")])
    self.addStep(Compile,
                 name="binutils-compile",
                 description=["binutils compile"],
                 descriptionDone=["binutils compiled"],
                 workdir="build/binutils/obj",
                 command=["make"])
    self.addStep(Compile,
                 name="binutils-install",
                 description=["binutils install"],
                 descriptionDone=["binutils installed"],
                 workdir="build/binutils/obj",
                 command=["make", "install"])

    # Make bootstrap gcc
    self.addStep(Configure,
                 name="gcc-configure",
                 description=["gcc configure"],
                 descriptionDone=["gcc configured"],
                 workdir="build/gcc/obj",
                 command=["bash",
                            "../gcc/configure",
                            "--target=%s" % self.target,
                            WithProperties("--prefix=%s/root", "basedir"),
                            WithProperties("--with-sysroot=%s/root", "basedir"),
                            "--enable-languages=all,obj-c++"] +
                            self.gccConfigExtraArgs)

    self.addStep(Compile,
                 name="gcc-bootstrap-compile",
                 description=["bootstrap gcc compile"],
                 descriptionDone=["bootstrap gcc compiled"],
                 workdir="build/gcc/obj",
                 command=["make", "all-gcc"],
                 env={'found_asm': 'yes'})
    self.addStep(Compile,
                 name="gcc-bootstrap-install",
                 description=["bootstrap gcc install"],
                 descriptionDone=["bootstrap gcc install"],
                 workdir="build/gcc/obj",
                 command=["make", "install-gcc"])

    # Compile CRT
    self.addStep(Configure,
                 name="crt-configure",
                 description=["CRT configure"],
                 descriptionDone=["CRT configured"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "../mingw-w64-crt/configure",
                            "--host=%s" % self.target,
                            WithProperties("--prefix=%s/root", "basedir"),
                            WithProperties("--with-sysroot=%s/root", "basedir")] +
                         self.crtConfigExtraArgs)
    self.addStep(Compile,
                 name="crt-compile",
                 description=["CRT compile"],
                 descriptionDone=["CRT compiled"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make"])
    self.addStep(Compile,
                 name="crt-install",
                 description=["CRT install"],
                 descriptionDone=["CRT installed"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make",
                            "install"])

    # Compile full gcc
    self.addStep(Compile,
                 name="gcc-compile",
                 description=["gcc compiled"],
                 descriptionDone=["gcc compile"],
                 workdir="build/gcc/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make"])
    self.addStep(Compile,
                 name="gcc-install",
                 description=["gcc install"],
                 descriptionDone=["gcc installed"],
                 workdir="build/gcc/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make",
                            "install"])

    # make the tarball
    self._step_Archive()

    # upload the tarball (to the build master)
    self.addStep(FileUpload,
                 slavesrc=WithProperties("../%(filename)s"),
                 masterdest=WithProperties("%(filename)s"),
                 mode=0644,
                 haltOnFailure=True)

    # tell the master to upload the file to sourceforge
    self.addStep(Trigger,
                 schedulerNames=["sourceforge-upload"],
                 waitForFinish=True,
                 set_properties={"masterdir": WithProperties("%(masterdir)s"),
                                 "filename": WithProperties("%(filename)s"),
                                 "destname": WithProperties("%(destname)s"),
                                 "datestamp": WithProperties("%(datestamp:-)s"),
                                 "is_nightly": WithProperties("%(is_nightly:-)s")})

  def _step_Archive(self):
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-bin_%(platform)s.tar.bz2")],
                 property="filename")
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-bin_%(platform)s%(platform-extra:-)s%(datestamp:-)s.tar.bz2")],
                 property="destname")
    # make the tarball
    self.addStep(ShellCommand,
                 name="makedist",
                 description=["tarball", "package"],
                 workdir="build/root",
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
  platform = "i686-linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64Linux64Factory(Mingw64Factory):
  platform = "x86_64-linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64CygwinFactory(Mingw64Factory):
  platform = "i686-cygwin"
  #gccConfigExtraArgs = ["--enable-bootstrap"]
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_Archive(self):
    self.addStep(SetProperty,
                 command=["bash", "-c",
                          """cygcheck -c -d cygwin | perl -ne 'm/^cygwin\s+(\S+)/ and print "-$1"'"""],
                 property="platform-extra")
    return Mingw64Factory._step_Archive(self)
 
class Mingw64MingwFactory(Mingw64Factory):
  platform = "i686-mingw"
  #gccConfigExtraArgs = ["--enable-bootstrap"]
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_Archive(self):
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-bin_%(platform)s.zip")],
                 property="filename")
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-bin_%(platform)s%(datestamp:-)s.zip")],
                 property="destname")
    # make the tarball
    self.addStep(ShellCommand,
                 name="makedist",
                 description=["zipfile", "package"],
                 workdir="build/root",
                 command=["zip",
                          "-r",
                          "-9",
                          "-v",
                          WithProperties("../../%(filename)s"),
                          ".",
                          "-x", ".svn"],
                 haltOnFailure=True)

class Mingw32Linux32Factory(Mingw64Linux32Factory):
  target = "i586-pc-mingw32"
  crtConfigExtraArgs = ["--enable-lib32", "--disable-lib64"]
  def __init__(self, **kwargs):
    Mingw64Linux32Factory.__init__(self, **kwargs)

class Mingw32Linux64Factory(Mingw64Linux64Factory):
  target = "i586-pc-mingw32"
  crtConfigExtraArgs = ["--enable-lib32", "--disable-lib64"]
  def __init__(self, **kwargs):
    Mingw64Linux64Factory.__init__(self, **kwargs)

class Mingw32CygwinFactory(Mingw64CygwinFactory):
  target = "i586-pc-mingw32"
  crtConfigExtraArgs = ["--enable-lib32", "--disable-lib64"]
  def __init__(self, **kwargs):
    Mingw64CygwinFactory.__init__(self, **kwargs)

class Mingw32MingwFactory(Mingw64MingwFactory):
  target = "i586-pc-mingw32"
  crtConfigExtraArgs = ["--enable-lib32", "--disable-lib64"]
  def __init__(self, **kwargs):
    Mingw64MingwFactory.__init__(self, **kwargs)
