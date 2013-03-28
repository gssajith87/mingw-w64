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
from scripts.buildsteps import M64CVS, M64NightlyRev, SubversionRevProperty, TriggerBuilders, WithPropertiesRecursive

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
    self.addStep(SetProperty(property="gmp_version",
                             command=["echo", gConfig.get("libraries", "gmp")],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("gmp_version")) ))
    self.addStep(SetProperty(property="mpfr_version",
                             command=["echo", gConfig.get("libraries", "mpfr")],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("mpfr_version")) ))
    self.addStep(SetProperty(property="mpc_version",
                             command=["echo", gConfig.get("libraries", "mpc")],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("mpc_version")) ))
    self.addStep(SetProperty(property="binutils_branch",
                             command=["echo", Property("binutils_branch", default="trunk")]))
    self.addStep(SetProperty(property="gcc_branch",
                             command=["echo", Property("gcc_branch", default="trunk")]))
    self.addStep(SetProperty(property="mingw_branch",
                             command=["echo", Property("mingw_branch", default="trunk")]))
    self.addStep(SetProperty(property="filename",
                             command=["echo", Property("src_archive", default="mingw-w64-src.tar.bz2")]))
    self.addStep(SetProperty(property="srcname_format",
                             command=["echo", "mingw-w64-src%(datestamp:-)s.tar.bz2"],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("srcname_format")) ))
    #self.addStep(M64NightlyRev)

    if self.clobber:
      self.addStep(ShellCommand(name="clobber",
                                command=["rm", "-rfv", "build", "src", Property("filename")],
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

#    self.addStep(SVN(mode="export",
#                     svnurl="https://mingw-w64.svn.sourceforge.net/svnroot/mingw-w64/experimental/buildsystem",
#                     extra_args=["--trust-server-cert"]))

    self.addStep(FileUpload(masterdest="mingw-makefile",
                            slavesrc="mingw-makefile",
                            maxsize=102400,
                            mode=0600))

    self.addStep(ShellCommand(name="patch-pull",
                              command=["make", "-f", "mingw-makefile", "patch-pull"],
                              description=["patches", "pull"],
                              descriptionDone=["pulled", "patches"]))

    # download binutils
    self.addStep(Compile(name="binutils-pull",
                         description=["binutils", "pull"],
                         descriptionDone=["pulled", "binutils"],
                         command=["make", "-f", "mingw-makefile", "binutils-pull"],
                         env={"BINUTILS_REVISION": Property("binutils_revision", default="head"),
                              "BINUTILS_BRANCH"  : Property("binutils_branch")}))

    self.addStep(ShellCommand(name="binutils-patch",
                              description=["patch", "binutils"],
                              descriptionDone=["binutils", "patched"],
                              doStepIf=lambda step: (step.getProperty("scheduler") != "try"),
                              workdir="build/src/binutils",
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../patches/binutils/*.patch )" ] ; then
                                            for i in ../patches/binutils/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                            done ;
                                          fi""".replace("\n", " ")]))

    # download gcc
    self.addStep(Compile(name="gcc-pull",
                         description=["gcc", "pull"],
                         descriptionDone=["pulled", "gcc"],
                         command=["make", "-f", "mingw-makefile", "gcc-pull"],
                         env={"GCC_REVISION": Property("gcc_revision", default="head"),
                              "GCC_BRANCH"  : Property("gcc_branch")}))
    self.addStep(ShellCommand(name="gcc-patch",
                              description=["patch", "gcc"],
                              descriptionDone=["gcc", "patched"],
                              doStepIf=lambda step: (step.getProperty("scheduler") != "try"),
                              workdir="build/src/gcc/src",
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../../patches/gcc/*.patch )" ] ; then
                                            for i in ../../patches/gcc/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                            done ;
                                          fi""".replace("\n", " ")]))
 
    # download gmp
    self.addStep(Compile(name="gmp-download",
                         description=["gmp", "download"],
                         descriptionDone=["downloaded", "gmp"],
                         command=["make", "-f", "mingw-makefile", "gmp-download"],
                         env={"GMP_VERSION": Property("gmp_version")}))
    self.addStep(Compile(name="gmp-extract",
                         description=["gmp", "extract"],
                         descriptionDone=["extracted", "gmp"],
                         command=["make", "-f", "mingw-makefile", "gmp-extract"],
                         env={"GMP_VERSION": Property("gmp_version")}))

    # Fix gmp (fails to find m4 for flex)
    self.addStep(ShellCommand(name="gmp-patch",
                              workdir="build/src/gcc/src/gmp",
                              description=["patch", "gmp"],
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../../../patches/gmp/*.patch )" ] ; then
                                            for i in ../../../patches/gmp/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                            done ;
                                          fi""".replace("\n", " ")]))

    # download mpfr
    self.addStep(Compile(name="mpfr-download",
                         description=["mpfr", "download"],
                         descriptionDone=["downloaded", "mpfr"],
                         command=["make", "-f", "mingw-makefile", "mpfr-download"],
                         env={"MPFR_VERSION": Property("mpfr_version")}))

    self.addStep(Compile(name="mpfr-extract",
                         description=["mpfr", "extract"],
                         descriptionDone=["extracted", "mpfr"],
                         command=["make", "-f", "mingw-makefile", "mpfr-extract"],
                         env={"MPFR_VERSION": Property("mpfr_version")}))

    self.addStep(ShellCommand(name="mpfr-patch",
                              description=["patch", "mpfr"],
                              descriptionDone=["patched", "mpfr"],
                              doStepIf=lambda step: (step.getProperty("scheduler") != "try"),
                              workdir="build/src/gcc/src/mpfr",
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../../../patches/mpfr/*.patch )" ] ; then
                                            for i in ../../../patches/mpfr/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                                         done ;
                                          fi""".replace("\n", " ")]))

    # download mpc
    self.addStep(Compile(name="mpc-download",
                         description=["mpc", "download"],
                         descriptionDone=["downloaded", "mpc"],
                         command=["make", "-f", "mingw-makefile", "mpc-download"],
                         env={"MPC_VERSION": Property("mpc_version")}))

    self.addStep(Compile(name="mpc-extract",
                         description=["mpc", "extract"],
                         descriptionDone=["extracted", "mpc"],
                         command=["make", "-f", "mingw-makefile", "mpc-extract"],
                         env={"MPC_VERSION": Property("mpc_version")}))

    self.addStep(ShellCommand(name="mpc-patch",
                              description=["patch", "mpc"],
                              descriptionDone=["patched", "mpc"],
                              doStepIf=lambda step: (step.getProperty("scheduler") != "try"),
                              workdir="build/src/gcc/src/mpc",
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../../../patches/mpc/*.patch )" ] ; then
                                            for i in ../../../patches/mpc/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                            done ;
                                          fi""".replace("\n", " ")]))

    # download mingw-w64 crt and headers
    self.addStep(Compile(name="mingw-pull",
                         description=["mingw", "pull"],
                         descriptionDone=["pulled", "mingw"],
                         command=["make", "-f", "mingw-makefile", "mingw-pull"],
                         env={"MINGW_REVISION": Property("mingw_revision", default="head"),
                              "MINGW_BRANCH"  : Property("mingw_branch")}))

    self.addStep(ShellCommand(name="mingw-patch",
                              description=["patch", "mingw"],
                              descriptionDone=["patched", "mingw"],
                              workdir="build/src/mingw",
                              doStepIf=lambda step: (step.getProperty("scheduler") != "try"),
                              command=["bash", "-c",
                                       """if [ -n "$( ls ../patches/mingw/*.patch )" ] ; then
                                            for i in ../patches/mingw/*.patch ; do
                                              patch -p1 -f -i "$i" ;
                                            done ;
                                          fi""".replace("\n", " ")]))

    # update the build stamp
    self.addStep(SubversionRevProperty(name="gcc-svnrev",
                                       workdir="build/src/gcc/src",
                                       prop_prefix="gcc_",
                                       config_dir=WithProperties("%(basedir:-.)s")))
    self.addStep(SubversionRevProperty(name="mingw-svnrev",
                                       workdir="build/src/mingw",
                                       prop_prefix="mingw_",
                                       config_dir=WithProperties("%(basedir:-.)s")))
    self.addStep(SetProperty(property="datestamp",
                             command=["date", "-u", "+_%Y%m%d"],
                             doStepIf=lambda step: ("datestamp" not in step.build.getProperties()) or
                                                   (step.getProperty("datestamp") == "")))
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
    self.addStep(ShellCommand(name="release-information",
                              workdir="build/src/gcc/src/gcc",
                              description=["writing", "version", "string"],
                              descriptionDone=["version", "string", "written"],
                              doStepIf=lambda step: ( (step.build.getProperties().has_key("release_build")) and (step.getProperty("release_build")) ),
                              command=["bash", "-c", WithProperties("""echo '%(release_gcc_ver:-)s' > BASE-VER && echo > DEV-PHASE """)]))
    # make the tarball
    self.addStep(SetProperty(property="destname",
                             command=["echo", WithPropertiesRecursive(WithProperties("%(srcname_format)s"))]))
    self.addStep(Compile(name="src-package",
                         description=["tarball", "package"],
                         descriptionDone=["packaged", "tarball"],
                         command=["make", "-f", "mingw-makefile", "src-archive"],
                         env={"SRC_ARCHIVE": Property("filename")}))

    # upload the tarball to the master
    self.addStep(FileUpload(name="src-upload",
                            slavesrc=Property("filename"),
                            masterdest=Property("filename")))

    # trigger upload
    self.addStep(Trigger(name="src-publish",
                         doStepIf=lambda step: ("is_nightly" in step.build.getProperties()) and
                                               step.build.getProperty("is_nightly"),
                         schedulerNames=["sourceforge-upload"],
                         waitForFinish=True, # needed for the builders
                         set_properties={"masterdir":  WithProperties("%(masterdir)s"),
                                         "filename":   WithProperties("%(filename)s"),
                                         "destname":   WithProperties("%(destname)s"),
                                         "datestamp":  WithProperties("%(datestamp:-)s"),
                                         "target-os":  "src",
                                         "path":       WithProperties("%(path:-)s"),
                                         "is_nightly": WithProperties("%(is_nightly:-)s")}))

    # set the path that the build will be uploaded to (so the other slaves can
    # go ahead and download the source tarballs from sourceforge rather than
    # over the buildbot connection).  Note that if the "path" property is set,
    # we use that as an override instead.
    self.addStep(SetProperty(property="src_url",
                             doStepIf=lambda step: ("is_nightly" in step.build.getProperties()) and
                                                   step.build.getProperty("is_nightly"),
                             command=["echo",
                                      WithProperties("http://downloads.sourceforge.net/project/%s/%%(path:-%s)s/%%(destname)s" %
                                                      (gConfig.get("sourceforge", "group_id"),
                                                       gConfig.get("sourceforge", "path-src")))]))

    # trigger building
    self.addStep(Trigger(name="start-build",
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
                         set_properties={"is_nightly":           Property("is_nightly"),
                                         "datestamp":            Property("datestamp"),
                                         "binutils_branch":      Property("binutils_branch"),
                                         "gcc_branch":           Property("gcc_branch"),
                                         "mingw_branch":         Property("mingw_branch"),
                                         "binutils_config_args": Property("binutils_config_args"),
                                         "gcc_config_args":      Property("gcc_config_args"),
                                         "mingw_config_args":    Property("mingw_config_args"),
                                         "gcc_revision":         Property("gcc_revision"),
                                         "mingw_revision":       Property("mingw_revision"),
                                         "masterdir":            Property("masterdir"),
                                         "path":                 Property("path"),
                                         "src_archive":          Property("filename"),
                                         "src_url":              Property("src_url", default="")}))

