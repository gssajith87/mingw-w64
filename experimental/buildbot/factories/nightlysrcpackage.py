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
from scripts.buildsteps import M64CVS, M64NightlyRev, ShellCommandConditional, SubversionRevProperty

class NightlySrcPackageFactory(factory.BuildFactory):
  clobber = True
  target = "x86_64-pc-mingw32"
  gccConfigExtraArgs = ["--disable-multilib"]

  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # set properties about this builder
    self.addStep(SetProperty,
                 command=["echo", os.getcwd()],
                 property="masterdir")
    self.addStep(SetProperty,
                 command=["bash", "-c", "pwd"],
                 property="basedir")

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
    self.addStep(ShellCommand,
                 name="gmp-patch",
                 workdir="build/gcc",
                 description=["patch", "gmp"],
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
    self.addStep(FileDownload,
                 name="mpfr-download",
                 workdir="build",
                 mastersrc="scripts/sources/mpfr-2.4.0.tar.bz2",
                 slavedest="mpfr.tar.bz2")
    self.addStep(ShellCommand,
                 name="mpfr-extract",
                 workdir="build/gcc",
                 command=["tar", "-xjvf", "../mpfr.tar.bz2"],
                 description=["mpfr extract"])
    self.addStep(ShellCommand,
                 name="mpfr-move",
                 workdir="build/gcc",
                 command=["mv", "mpfr-2.4.0", "gcc/mpfr"],
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

    # update the build stamp
    self.addStep(SubversionRevProperty,
                 workdir="build/mingw",
                 prop_prefix="mingw_")
    self.addStep(ShellCommand,
                 name="mingw-datestamp",
                 workdir="build/mingw/mingw-w64-crt",
                 description=["writing", "buildstamp"],
                 descriptionDone=["buildstamp", "written"],
                 command=["bash", "-c", WithProperties(
                            """echo -e '/* generated by buildbot */\n"""
                            """#define __MINGW_W64_REV "%(mingw_revision)s"\n"""
                            """#define __MINGW_W64_REV_STAMP "%(mingw_datestamp)s"\n'"""
                            """ > revstamp.h """)])

    # Install mingw headers
    self.addStep(ShellCommand,
                 name="mingw-headers-install",
                 description=["mingw headers install"],
                 workdir="build/root/%s/include" % self.target,
                 command="tar cf - --exclude=.svn -C ../../../mingw/mingw-w64-headers/include . | tar xpvf -")

    # make the tarball
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-src.tar.bz2")],
                 property="filename")
    self.addStep(SetProperty,
                 command=["echo", WithProperties("mingw-w64-src%(datestamp:-)s.tar.bz2")],
                 property="destname")
    self.addStep(ShellCommand,
                 name="src-package",
                 description=["tarball", "package"],
                 workdir="build",
                 command=["tar",
                          "cjf",
                          WithProperties("../%(filename)s"),
                          "--owner", "0",
                          "--group", "0",
                          "--checkpoint",
                          "--exclude=.svn",
                          "."],
                 haltOnFailure=True)
    # upload the tarball to the master
    self.addStep(FileUpload,
                 name="src-upload",
                 slavesrc=WithProperties("../%(filename)s"),
                 masterdest=WithProperties("%(filename)s"))

    # trigger building
    self.addStep(Trigger,
                 name="start-build",
                 schedulerNames=["trigger-linux64", "trigger-linux32", "trigger-cygwin", "trigger-mingw"],
                 waitForFinish=False,
                 updateSourceStamp=True,
                 set_properties={'is_nightly': WithProperties("%(is_nightly:-)s"),
                                 'datestamp':  WithProperties("%(datestamp:-)s"),
                                 'masterdir':  WithProperties("%(masterdir)s")})
    # trigger upload
    self.addStep(Trigger,
                 name="src-publish",
                 schedulerNames=["sourceforge-upload"],
                 waitForFinish=False, # don't hang :D
                 set_properties={"masterdir":  WithProperties("%(masterdir)s"),
                                 "filename":   WithProperties("%(filename)s"),
                                 "destname":   WithProperties("%(destname)s"),
                                 "is_nightly": WithProperties("%(is_nightly:-)s")})

