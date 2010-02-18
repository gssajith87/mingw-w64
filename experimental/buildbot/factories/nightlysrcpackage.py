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
from scripts.buildsteps import M64CVS, M64NightlyRev, ShellCommandConditional, SetPropertyConditional, SubversionRevProperty, TriggerBuilders, WithPropertiesRecursive

from ConfigParser import RawConfigParser as ConfigParser
gConfig = ConfigParser()
gConfig.read("config.ini")

class NightlySrcPackageFactory(factory.BuildFactory):
  clobber = True
  gccConfigExtraArgs = ["--disable-multilib"]

  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # set properties about this builder
    self.addStep(SetProperty(property="masterdir",
                             command=["echo", os.getcwd()]))
    self.addStep(SetProperty(property="basedir",
                             command=["bash", "-c", "builtin pwd"]))
    self.addStep(SetPropertyConditional(property="gmp_version",
                                        command=["echo", gConfig.get("libraries", "gmp")],
                                        condprop="gmp_version",
                                        condinvert=True))
    self.addStep(SetPropertyConditional(property="mpfr_version",
                                        command=["echo", gConfig.get("libraries", "mpfr")],
                                        condprop="mpfr_version",
                                        condinvert=True))
    self.addStep(SetPropertyConditional(property="mpc_version",
                                        command=["echo", gConfig.get("libraries", "mpc")],
                                        condprop="mpc_version",
                                        condinvert=True))
    self.addStep(SetProperty(property="binutils_branch",
                             command=["echo", WithProperties("%(binutils_branch:-trunk)s")]))
    self.addStep(SetProperty(property="gcc_branch",
                             command=["echo", WithProperties("%(gcc_branch:-trunk)s")]))
    self.addStep(SetProperty(property="mingw_branch",
                             command=["echo", WithProperties("%(mingw_branch:-trunk)s")]))
    self.addStep(SetProperty(property="filename",
                             command=["echo", WithProperties("%(src_archive:-mingw-w64-src.tar.bz2)s")]))
    #self.addStep(M64NightlyRev)

    self.addStep(SetPropertyConditional,
                 condprop="srcname_format",
                 condinvert=True,
                 command=["echo", "mingw-w64-src%(datestamp:-)s.tar.bz2"],
                 property="srcname_format")

    if self.clobber:
      self.addStep(ShellCommand(name="clobber",
                                command=["rm", "-rfv", "build", "src", WithProperties("%(filename)s")],
                                haltOnFailure=False,
                                description=["clobber all"],
                                descriptionDone=["clobbered"]))

    self.addStep(ShellCommand(name="makefile-checkout",
                              description=["makefile", "checkout"],
                              descriptionDone=["checked out", "makefile"],
                              command=["curl",
                                       "-o",
                                       "mingw-makefile",
                                       "https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/experimental/buildsystem/makebuildroot.mk"],
                              haltOnFailure=True))

    self.addStep(FileUpload(masterdest="mingw-makefile",
                            slavesrc="mingw-makefile",
                            maxsize=102400,
                            mode=0600))

    self.addStep(ShellCommand,
                 name="patch-pull",
                 command=["make", "-f", "mingw-makefile", "patch-pull"],
                 description=["patches", "pull"],
                 descriptionDone=["pulled", "patches"])

    # download binutils
    self.addStep(Compile(name="binutils-pull",
                         description=["binutils", "pull"],
                         descriptionDone=["pulled", "binutils"],
                         command=["make", "-f", "mingw-makefile", "binutils-pull"],
                         env={"BINUTILS_REVISION": WithProperties("%(binutils_revision:-head)s"),
                              "BINUTILS_BRANCH"  : WithProperties("%(binutils_branch)s")}))

    self.addStep(ShellCommandConditional,
                 name="binutils-patch",
                 workdir="build/src/binutils",
                 description=["patch", "binutils"],
                 descriptionDone=["binutils", "patched"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ -n "$( ls ../patches/binutils/*.patch )" ] ; then
                               for i in ../patches/binutils/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download gcc
    self.addStep(Compile(name="gcc-pull",
                         description=["gcc", "pull"],
                         descriptionDone=["pulled", "gcc"],
                         command=["make", "-f", "mingw-makefile", "gcc-pull"],
                         env={"GCC_REVISION": WithProperties("%(gcc_revision:-head)s"),
                              "GCC_BRANCH"  : WithProperties("%(gcc_branch)s")}))
    self.addStep(ShellCommandConditional,
                 name="gcc-patch",
                 workdir="build/src/gcc/gcc",
                 description=["patch", "gcc"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ -n "$( ls ../../patches/gcc/*.patch )" ] ; then
                               for i in ../../patches/gcc/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download gmp
    self.addStep(Compile(name="gmp-download",
                         description=["gmp", "download"],
                         descriptionDone=["downloaded", "gmp"],
                         command=["make", "-f", "mingw-makefile", "gmp-download"],
                         env={"GMP_VERSION": WithProperties("%(gmp_version)s")}))
    self.addStep(Compile(name="gmp-extract",
                         description=["gmp", "extract"],
                         descriptionDone=["extracted", "gmp"],
                         command=["make", "-f", "mingw-makefile", "gmp-extract"],
                         env={"GMP_VERSION": WithProperties("%(gmp_version)s")}))

    # Fix gmp (fails to find m4 for flex)
    self.addStep(ShellCommand,
                 name="gmp-patch",
                 workdir="build/src/gcc",
                 description=["patch", "gmp"],
                 command=["bash", "-c",
                          """if [ -n "$( ls ../patches/gmp/*.patch )" ] ; then
                               for i in ../patches/gmp/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
    self.addStep(Compile(name="gmp-autoconf",
                         description=["gmp", "autoconf"],
                         descriptionDone=["autoconf", "gmp"],
                         command=["make", "-f", "mingw-makefile", "gmp-autoconf"],
                         env={"GMP_VERSION": WithProperties("%(gmp_version)s")}))

    # download mpfr
    self.addStep(Compile(name="mpfr-download",
                         description=["mpfr", "download"],
                         descriptionDone=["downloaded", "mpfr"],
                         command=["make", "-f", "mingw-makefile", "mpfr-download"],
                         env={"MPFR_VERSION": WithProperties("%(mpfr_version)s")}))

    self.addStep(Compile(name="mpfr-extract",
                         description=["mpfr", "extract"],
                         descriptionDone=["extracted", "mpfr"],
                         command=["make", "-f", "mingw-makefile", "mpfr-extract"],
                         env={"MPFR_VERSION": WithProperties("%(mpfr_version)s")}))

    # download mpc
    self.addStep(Compile(name="mpc-download",
                         description=["mpc", "download"],
                         descriptionDone=["downloaded", "mpc"],
                         command=["make", "-f", "mingw-makefile", "mpc-download"],
                         env={"MPC_VERSION": WithProperties("%(mpc_version)s")}))

    self.addStep(Compile(name="mpc-extract",
                         description=["mpc", "extract"],
                         descriptionDone=["extracted", "mpc"],
                         command=["make", "-f", "mingw-makefile", "mpc-extract"],
                         env={"MPC_VERSION": WithProperties("%(mpc_version)s")}))

    self.addStep(ShellCommandConditional,
                 name="mpfr-patch",
                 workdir="build/src/gcc/gcc/mpfr",
                 description=["patch", "mpfr"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ -n "$( ls ../../../patches/mpfr/*.patch )" ] ; then
                               for i in ../../../patches/mpfr/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])
 
    # download mingw-w64 crt and headers
    self.addStep(Compile(name="mingw-pull",
                         description=["mingw", "pull"],
                         descriptionDone=["pulled", "mingw"],
                         command=["make", "-f", "mingw-makefile", "mingw-pull"],
                         env={"MINGW_REVISION": WithProperties("%(mingw_revision:-head)s"),
                              "MINGW_BRANCH"  : WithProperties("%(mingw_branch)s")}))

    self.addStep(ShellCommandConditional,
                 name="mingw-patch",
                 workdir="build/src/mingw",
                 description=["patch", "mingw"],
                 condprop="scheduler",
                 condvalue="try",
                 condinvert=True,
                 command=["bash", "-c",
                          """if [ -n "$( ls ../patches/mingw/*.patch )" ] ; then
                               for i in ../patches/mingw/*.patch ; do
                                 patch -p0 -f -i "$i" ;
                               done ;
                             fi""".replace("\n", " ")])

    # update the build stamp
    self.addStep(SubversionRevProperty(name="gcc-svnrev",
                                       workdir="build/src/gcc/gcc",
                                       prop_prefix="gcc_",
                                       config_dir=WithProperties("%(basedir:-.)s")))
    self.addStep(SubversionRevProperty(name="mingw-svnrev",
                                       workdir="build/src/mingw",
                                       prop_prefix="mingw_",
                                       config_dir=WithProperties("%(basedir:-.)s")))
    self.addStep(SetProperty(property="datestamp",
                             command=["date", "-u", "+_%Y%m%d"]))
    self.addStep(ShellCommand(name="mingw-datestamp",
                              workdir="build/src/mingw/mingw-w64-crt",
                              description=["writing", "buildstamp"],
                              descriptionDone=["buildstamp", "written"],
                              command=["bash", "-c", WithProperties(
                                         """echo -e '/* generated by buildbot */\n"""
                                         """#define __MINGW_W64_REV "%(mingw_revision)s"\n"""
                                         """#define __MINGW_W64_REV_STAMP "%(mingw_datestamp)s"\n'"""
                                         """ > revstamp.h """)]))

    # Set the gcc version strings if this is a formal release
    self.addStep(ShellCommandConditional,
                 name="release-information",
                 workdir="build/src/gcc/gcc/gcc",
                 description=["writing", "version", "string"],
                 descriptionDone=["version", "string", "written"],
                 condprop="release_build",
                 conddefault=False,
                 command=["bash", "-c", 
                          WithProperties("""echo '%(release_gcc_ver)s' > BASE_VER && echo > DEV-PHASE """)])
    # make the tarball
    self.addStep(SetProperty(property="destname",
                             command=["echo", WithPropertiesRecursive(WithProperties("%(srcname_format)s"))]))
    self.addStep(Compile(name="src-package",
                         description=["tarball", "package"],
                         descriptionDone=["packaged", "tarball"],
                         command=["make", "-f", "mingw-makefile", "src-archive"],
                         env={"SRC_ARCHIVE": WithProperties("%(filename)s")}))

    # upload the tarball to the master
    self.addStep(FileUpload(name="src-upload",
                            slavesrc=WithProperties("%(filename)s"),
                            masterdest=WithProperties("%(filename)s")))

    # trigger building
    self.addStep(TriggerBuilders
                  (name="start-build",
                   propertyName="builders",
                   schedulerNames=["trigger-linux-x86_64-x86_64",
                                   "trigger-linux-x86_64-x86",
                                   "trigger-linux-x86-x86_64",
                                   "trigger-linux-x86-x86",
                                   "trigger-cygwin-x86-x86_64",
                                   "trigger-cygwin-x86-x86",
                                   "trigger-mingw-x86-x86_64",
                                   "trigger-mingw-x86-x86",
                                   "trigger-darwin-x86-x86_64",
                                   "trigger-darwin-x86-x86"],
                   waitForFinish=False,
                   updateSourceStamp=True,
                   copy_properties=['is_nightly', 'datestamp',
                                    'binutils_branch', 'gcc_branch', 'mingw_branch',
                                    'binutils_config_args', 'gcc_config_args', 'mingw_config_args',
                                    'gcc_revision', 'mingw_revision',
                                    'destname_format',
                                    'masterdir', 'path'],
                   set_properties={"src_archive":          WithProperties("%(filename)s")}))
    # trigger upload
    self.addStep(Trigger(name="src-publish",
                         schedulerNames=["sourceforge-upload"],
                         waitForFinish=False, # don't hang :D
                         set_properties={"masterdir":  WithProperties("%(masterdir)s"),
                                         "filename":   WithProperties("%(filename)s"),
                                         "destname":   WithProperties("%(destname)s"),
                                         "datestamp":  WithProperties("%(datestamp:-)s"),
                                         "target-os":  "src",
                                         "path":       WithProperties("%(path:-)s"),
                                         "is_nightly": WithProperties("%(is_nightly:-)s")}))

