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
                 description=["initializing root"],
                 descriptionDone=["initialize root"])

    self.addStep(FileDownload,
                 name="exec-script",
                 workdir="build",
                 mastersrc="scripts/wrapped-exec.sh",
                 slavedest="wrapped-exec.sh",
                 maxsize=102400,
                 mode=0755,
                 haltOnFailure=True)

    self.addStep(ShellCommand,
                 name="patch-download",
                 workdir="build",
                 command=["svn", "co",
                          "https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/experimental/patches/"],
                 description=["patches", "download"],
                 descriptionDone=["downloaded", "patches"])

    # download binutils
    self.addStep(M64CVS,
                 name="binutils-pull",
                 cvsroot=":pserver:anoncvs@sourceware.org:/cvs/src",
                 cvsmodule="binutils",
                 login=None)
    self.addStep(ShellCommandConditional,
                 name="binutils-patch",
                 workdir="build/binutils",
                 description=["patch", "binutils"],
                 descriptionDone=["binutils", "patched"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ $( ls ../patches/binutils/*.patch ) ] ; then
                               for i in ../patches/binutils/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download gcc                 
    self.addStep(SVN,
                 name="gcc-pull",
                 workdir="build/gcc/gcc",
                 baseURL="svn://gcc.gnu.org/svn/gcc/",
                 defaultBranch="trunk")
    self.addStep(ShellCommandConditional,
                 name="gcc-patch",
                 workdir="build/gcc/gcc",
                 description=["patch", "gcc"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ $( ls ../../patches/gcc/*.patch ) ] ; then
                               for i in ../../patches/gcc/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download gmp
    self.addStep(FileDownload,
                 name="gmp-download",
                 workdir="build",
                 mastersrc="scripts/sources/gmp-4.2.2.tar.bz2",
                 slavedest="gmp.tar.bz2")
    self.addStep(ShellCommand,
                 name="gmp-extract",
                 workdir="build/gcc",
                 command=["tar", "-xjvf", "../gmp.tar.bz2"],
                 description=["gmp extract"])
    self.addStep(ShellCommand,
                 name="gmp-move",
                 workdir="build/gcc",
                 command=["mv", "gmp-4.2.2", "gcc/gmp"],
                 description=["gmp move"])


    # Fix gmp (fails to find m4 for flex)
    self.addStep(ShellCommandConditional,
                 name="gmp-patch",
                 workdir="build/gcc",
                 description=["patch", "gmp"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ $( ls ../patches/gmp/*.patch ) ] ; then
                               for i in ../patches/gmp/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
    self.addStep(ShellCommand,
                 name="gmp-autoconf",
                 workdir="build/gcc/gcc/gmp",
                 command="autoconf",
                 description=["gmp", "autoconf"])

    # download mpfr
    #self.addStep(ShellCommand,
    #             name="mpfr-pull",
    #             workdir="build/gcc",
    #             command=["bash", "-c",
    #                      " ".join(["if [ ! -d gcc/mpfr ] ; then",
    #                                "rm -rfv gcc/mpfr &&",
    #                                "wget -O- http://www.mpfr.org/mpfr-current/mpfr-2.3.2.tar.bz2 | ",
    #                                "tar xjf - && ",
    #                                "mv mpfr-2.3.2 gcc/mpfr",
    #                                "; fi"])],
    #             description=["mpfr download"])
    self.addStep(FileDownload,
                 name="mpfr-download",
                 workdir="build",
                 mastersrc="scripts/sources/mpfr-2.3.2.tar.bz2",
                 slavedest="mpfr.tar.bz2")
    self.addStep(ShellCommand,
                 name="mpfr-extract",
                 workdir="build/gcc",
                 command=["tar", "-xjvf", "../mpfr.tar.bz2"],
                 description=["mpfr extract"])
    self.addStep(ShellCommand,
                 name="mpfr-move",
                 workdir="build/gcc",
                 command=["mv", "mpfr-2.3.2", "gcc/mpfr"],
                 description=["mpfr move"])
    self.addStep(ShellCommandConditional,
                 name="mpfr-patch",
                 workdir="build/gcc/mpfr",
                 description=["patch", "mpfr"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ $( ls ../../patches/mpfr/*.patch ) ] ; then
                               for i in ../../patches/mpfr/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download mingw-w64 crt and headers
    # always pull HEAD, because revision numbers on the waterfall is more useful for changing gcc version
    # unfortunately, buildbot's alwaysUseLatest flag only applies when you _don't_ give a revision
    self.addStep(ShellCommand,
                 name="mingw-pull",
                 workdir=".",
                 command=["svn", "checkout", "--non-interactive", "--no-auth-cache", "--revision", "HEAD",
                          "https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/trunk", "build/mingw"],
                 description=["mingw pull"])
    self.addStep(ShellCommandConditional,
                 name="mingw-patch",
                 workdir="build/mingw",
                 description=["patch", "mingw"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ $( ls ../patches/mingw/*.patch ) ] ; then
                               for i in ../patches/mingw/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 

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
                 descriptionDone=["binutils configure"],
                 workdir="build/binutils/obj",
                 command=["bash",
                            "../src/configure", 
                            "--target=%s" % self.target,
                            WithProperties("--prefix=%s/root", "basedir"),
                            WithProperties("--with-sysroot=%s/root", "basedir")])
    self.addStep(Compile,
                 name="binutils-compile",
                 description=["binutils compile"],
                 descriptionDone=["binutils compile"],
                 workdir="build/binutils/obj",
                 command=["make"])
    self.addStep(Compile,
                 name="binutils-install",
                 description=["binutils install"],
                 descriptionDone=["binutils install"],
                 workdir="build/binutils/obj",
                 command=["make", "install"])

    # Make bootstrap gcc
    self.addStep(Configure,
                 name="gcc-configure",
                 description=["gcc configure"],
                 descriptionDone=["gcc configure"],
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
                 descriptionDone=["bootstrap gcc compile"],
                 workdir="build/gcc/obj",
                 command=["make", "all-gcc"],
                 env={'found_asm': 'yes'})
    self.addStep(Compile,
                 name="gcc-bootstrap-install",
                 escription=["bootstrap gcc install"],
                 descriptionDone=["bootstrap gcc install"],
                 workdir="build/gcc/obj",
                 command=["make", "install-gcc"])

    # Compile CRT
    self.addStep(Configure,
                 name="crt-configure",
                 description=["CRT configure"],
                 descriptionDone=["CRT configure"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "../mingw-w64-crt/configure",
                            "--host=%s" % self.target,
                            WithProperties("--prefix=%s/root", "basedir"),
                            WithProperties("--with-sysroot=%s/root", "basedir")])
    self.addStep(Compile,
                 name="crt-compile",
                 description=["CRT compile"],
                 descriptionDone=["CRT compile"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make"])
    self.addStep(Compile,
                 name="crt-install",
                 description=["CRT install"],
                 descriptionDone=["CRT install"],
                 workdir="build/mingw/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make",
                            "install"])

    # Compile full gcc
#    self.addStep(Compile,
#                 name="gcc-clean-temp",
#                 workdir="build/gcc/obj/x86_64-pc-mingw32/libgcc",
#                 command=["make","-p","clean"])
    self.addStep(Compile,
                 name="gcc-compile",
                 description=["gcc compile"],
                 descriptionDone=["gcc compile"],
                 workdir="build/gcc/obj",
                 command=["bash",
                            "../../wrapped-exec.sh",
                            "root/bin",
                            "make"])
    self.addStep(Compile,
                 name="gcc-install",
                 description=["gcc install"],
                 descriptionDone=["gcc install"],
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
    self.addStep(SetProperty,
                 command=["echo", os.getcwd()],
                 property="masterdir")
    self.addStep(Trigger,
                 schedulerNames=["sourceforge-upload"],
                 waitForFinish=True,
                 set_properties={"masterdir": WithProperties("%(masterdir)s"),
                                 "filename": WithProperties("%(filename)s"),
                                 "destname": WithProperties("%(destname)s"),
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
                

class Mingw64LinuxFactory(Mingw64Factory):
  platform = "i686-linux"
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
