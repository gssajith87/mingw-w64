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
from scripts.buildsteps import M64CVS, M64NightlyRev, WithPropertiesRecursive
import re

class Mingw64Factory(factory.BuildFactory):
  clobber = True
  target = "x86_64-w64-mingw32"
  gccConfigExtraArgs = "--enable-fully-dynamic-string --disable-multilib"
  crtConfigExtraArgs = ""
  binutilsConfigExtraArgs = ""
  gmpConfigExtraArgs = ""
  mpfrConfigExtraArgs = ""
  mpcConfigExtraArgs = ""
  host_cpu = "unknown"
  host_os = "unknown"
  file_extension = "tar.bz2"
 
  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # set properties about this builder
    self.addStep(SetProperty(property="basedir",
                             command=["bash", "-c", """pwd | sed 's@\\\\\\\\@/@g; s@^\\\\(.\\\\):@/\\\\1@ '"""],
                             haltOnFailure=True))

    self.addStep(SetProperty(property="host_cpu",
                             command=["echo", self.host_cpu]))
    self.addStep(SetProperty(property="host_os",
                             command=["echo", self.host_os]))

    target_os = "unknown"
    for os_mask in [ { "expr": "x86_64", "value": "w64" },
                     { "expr": "i.86",   "value": "w32" } ]:
      if re.match(os_mask["expr"], self.target) is not None:
        target_os = os_mask["value"]
        break
    self.addStep(SetProperty(property="target-os",
                             command=["echo", target_os]))

    self.addStep(SetProperty(property="target_arch",
                             command=["echo", self.target]))

    self.addStep(SetProperty(property="gcc_config_args",
                             command=["echo", Property("gcc_config_args"), self.gccConfigExtraArgs]))
    self.addStep(SetProperty(property="mingw_config_args",
                             command=["echo", Property("mingw_config_args"), self.crtConfigExtraArgs]))
    self.addStep(SetProperty(property="binutils_config_args",
                             command=["echo", Property("binutils_config_args"), self.binutilsConfigExtraArgs]))
    self.addStep(SetProperty(property="gmp_config_args",
                             command=["echo", Property("gmp_config_args"), self.gmpConfigExtraArgs]))
    self.addStep(SetProperty(property="mpfr_config_args",
                             command=["echo", Property("mpfr_config_args"), self.mpfrConfigExtraArgs]))
    self.addStep(SetProperty(property="mpc_config_args",
                             command=["echo", Property("mpc_config_args", self.mpcConfigExtraArgs]))

    self.addStep(SetProperty(property="gcc_branch",
                             command=["echo", Property("gcc_branch", default="trunk")]))
    self.addStep(SetProperty(property="gcc_revision",
                             command=["echo", Property("gcc_revision", default="head")]))
    self.addStep(SetProperty(property="mingw_revision",
                             command=["echo", Property("mingw_revision", default="head")]))
    self.addStep(SetProperty(property="binutils_revision",
                             command=["echo", Property("binutils_revision", default="head")]))

    self.addStep(SetProperty(command=["echo", self.file_extension],
                             property="file_extension"))

    self._step_AdditionalProperties()

    self.addStep(SetProperty(property="filename_format",
                             command=["echo", "mingw-%(target-os)s-bin_%(host_cpu)s-%(host_os)s.%(file_extension)s"],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("filename_format")) ))
    self.addStep(SetProperty(property="filename",
                             command=["echo", WithPropertiesRecursive(WithProperties("%(filename_format)s"))],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("filename")) ))
    self.addStep(SetProperty(property="destname_format",
                             command=["echo", "mingw-%(target-os)s-bin_%(host_cpu)s-%(host_os)s%(host-extra:-)s%(datestamp:-)s.%(file_extension)s"],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("destname_format")) ))
    self.addStep(SetProperty(property="destname",
                             command=["echo", WithPropertiesRecursive(WithProperties("%(destname_format)s"))],
                             doStepIf=lambda step: (not step.build.getProperties().has_key("destname")) ))

    # dump info about this slave
    self.addStep(ShellCommand(name="sys-info",
                              workdir=".",
                              command=["bash", "-c", r"""true
                              ; echo -e "\n----------\nuname:\n----------"
                              ; uname -a
                              ; echo -e "\n----------\ndistro:\n----------"
                              ; cat /etc/issue
                              ; echo -e "\n----------\ncompiler version:\n----------"
                              ; gcc --version
                              ; echo -e "\n----------\nlinker version:\n----------"
                              ; ld --version
                              ; echo -e "\n----------\nassembler version:\n----------"
                              ; as --version
                              ; echo -e "\n----------\nflex version:\n----------"
                              ; flex --version
                              ; echo -e "\n----------\nbison version:\n----------"
                              ; bison --version
                              ; echo -e "\n----------\nmake version:\n----------"
                              ; make --version
                              ; true
                              """.replace("\n", "")],
                              haltOnFailure=False,
                              description=["system info"],
                              descriptionDone=["system info"]))

    # set up build root
    if self.clobber:
      self.addStep(ShellCommand(name="clobber",
                                workdir=".",
                                command=["bash", "-c", " ".join("""
                                          junction -d build/build/root/mingw || true ;
                                          rm -rfv build""".split())],
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

    self.addStep(FileDownload(name="src-download-script",
                              mastersrc="scripts/download-src.py",
                              slavedest="download-src.py",
                              maxsize=102400,
                              mode=0755,
                              haltOnFailure=True))

    self.addStep(ShellCommand(name="src-download-web",
                              description=["source", "download", "web"],
                              doStepIf=lambda step: ("src_url" in step.build.getProperties()) and
                                                    (step.getProperty("src_url") != ""),
                              command=["python", "download-src.py", WithProperties("%(src_url)s"), WithProperties("%(src_archive)s")],
                              haltOnFailure=True))

    self.addStep(FileDownload(name="src-download",
                              doStepIf=lambda step: (not ("src_url" in step.build.getProperties())) or
                                                    (step.getProperty("src_url") == ""),
                              mastersrc=WithProperties("%(src_archive)s"),
                              slavedest=WithProperties("%(src_archive)s"),
                              mode=0644,
                              haltOnFailure=True))

    self.addStep(Compile(name="src-extract",
                         description=["source", "extract"],
                         descriptionDone=["source", "extracted"],
                         command=["make", "-f", "mingw-makefile", "src-extract"],
                         env={"TARGET_ARCH": WithProperties("%(target_arch)s"),
                              "SRC_ARCHIVE": WithProperties("%(src_archive)s")}))

    # Install mingw headers
    self.addStep(Compile(name="mingw-headers-install",
                         description=["mingw headers","install"],
                         descriptionDone=["mingw headers", "installed"],
                         command=["make", "-f", "mingw-makefile", "headers-install"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Make binutils
    self.addStep(Configure(name="binutils-configure",
                           description=["binutils", "configure"],
                           descriptionDone=["binutils", "configured"],
                           command=["make", "-f", "mingw-makefile", "binutils-configure"],
                           env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                                "BINUTILS_CONFIG_EXTRA_ARGS": WithProperties("%(binutils_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="binutils-compile",
                         description=["binutils compile"],
                         descriptionDone=["binutils compiled"],
                         command=["make", "-f", "mingw-makefile", "binutils-compile"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="binutils-install",
                         description=["binutils install"],
                         descriptionDone=["binutils installed"],
                         command=["make", "-f", "mingw-makefile", "binutils-install"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Make bootstrap gcc
    self.addStep(Configure(name="gcc-configure",
                           description=["gcc configure"],
                           descriptionDone=["gcc configured"],
                           command=["make", "-f", "mingw-makefile", "gcc-configure"],
                           env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                                "GCC_CONFIG_EXTRA_ARGS": WithProperties("%(gcc_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-bootstrap-compile",
                         description=["bootstrap gcc compile"],
                         descriptionDone=["bootstrap gcc compiled"],
                         command=["make", "-f", "mingw-makefile", "gcc-bootstrap-compile"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-bootstrap-install",
                         description=["bootstrap gcc install"],
                         descriptionDone=["bootstrap gcc install"],
                         command=["make", "-f", "mingw-makefile", "gcc-bootstrap-install"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Compile CRT
    self.addStep(Configure(name="crt-configure",
                           description=["CRT configure"],
                           descriptionDone=["CRT configured"],
                           command=["make", "-f", "mingw-makefile", "crt-configure"],
                           env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                                "MINGW_CONFIG_EXTRA_ARGS": WithProperties("%(mingw_config_args)s"),
                                "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="crt-compile",
                         description=["CRT compile"],
                         descriptionDone=["CRT compiled"],
                         command=["make", "-f", "mingw-makefile", "crt-compile"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="crt-install",
                         description=["CRT install"],
                         descriptionDone=["CRT installed"],
                         command=["make", "-f", "mingw-makefile", "crt-install"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    # Compile full gcc
    self.addStep(Compile(name="gcc-compile",
                         description=["gcc compiled"],
                         descriptionDone=["gcc compile"],
                         command=["make", "-f", "mingw-makefile", "gcc-compile"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(Compile(name="gcc-install",
                         description=["gcc install"],
                         descriptionDone=["gcc installed"],
                         command=["make", "-f", "mingw-makefile", "gcc-install"],
                         env={"SRC_ARCHIVE": WithProperties("%(src_archive)s"),
                              "TARGET_ARCH": WithProperties("%(target_arch)s")}))

    self.addStep(SetProperty(property="filename",
                             command=["echo", WithPropertiesRecursive(WithProperties("%(filename_format)s"))]))

    # make the tarball
    self._step_Archive()

    # do a very simple test
    self.addStep(Compile(name="sanity-check",
                         description=["sanity check"],
                         descriptionDone=["sanity check", "completed"],
                         command=["bash", "-c",
                                  WithProperties("""echo "int main(){return 0;}" > test.c ;
                                                 %(basedir)s/build/root/bin/%(target_arch)s-gcc -o test test.c""")],
                         haltOnFailure=True))

    # upload the tarball (to the build master)
    self.addStep(FileUpload(slavesrc=WithProperties("%(filename)s"),
                            masterdest=WithProperties("%(filename)s"),
                            mode=0644,
                            haltOnFailure=True))

    # tell the master to upload the file to sourceforge
    self.addStep(Trigger(schedulerNames=["sourceforge-upload"],
                         waitForFinish=True,
                         set_properties={"masterdir":  WithProperties("%(masterdir)s"),
                                         "target-os":  WithProperties("%(target-os)s"),
                                         "filename":   WithProperties("%(filename)s"),
                                         "destname":   WithProperties("%(destname)s"),
                                         "datestamp":  WithProperties("%(datestamp:-)s"),
                                         "path":       WithProperties("%(path:-)s"),
                                         "is_nightly": WithProperties("%(is_nightly:-)s")}))

  def _step_AdditionalProperties(self):
    pass

  def _step_Archive(self):
    command=["tar",
      "cjf",
      WithProperties("../../%(filename)s"),
      "--owner", "0",
      "--group", "0",
      "--checkpoint",
      "--exclude=.svn",
      "."]
    # OSX Snow Leopard (10.6) has tar which is bsdtar
    # make it use gnutar, this is also availible on Leopard (10.5)
    if self.host_os == "darwin":
      command[0]="gnutar"
    # make the tarball
    self.addStep(ShellCommand(name="makedist",
                              description=["tarball", "package"],
                              workdir="build/build/root",
                              command=command,
                              haltOnFailure=True))

class Mingw64Linux32Factory(Mingw64Factory):
  host_cpu = "i686"
  host_os = "linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64Linux64Factory(Mingw64Factory):
  host_cpu = "x86_64"
  host_os = "linux"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

class Mingw64CygwinFactory(Mingw64Factory):
  host_cpu = "i686"
  host_os = "cygwin"
  gccConfigExtraArgs = "--disable-nls"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_AdditionalProperties(self):
    self.addStep(SetProperty(property="host-extra",
                             command=["bash", "-c",
                                      """cygcheck -c -d cygwin | perl -ne 'm/^cygwin\s+(\S+)/ and print "-$1"'"""]))
 
class Mingw64MingwFactory(Mingw64Factory):
  host_cpu = "i686"
  host_os = "mingw"
  file_extension = "zip"
  #gccConfigExtraArgs = "--enable-bootstrap"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

  def _step_Archive(self):
    # make the tarball
    self.addStep(ShellCommand(name="makedist",
                              description=["zipfile", "package"],
                              workdir="build/build/root",
                              command=["zip",
                                       "-r",
                                       "-9",
                                       "-v",
                                       WithProperties("../../%(filename)s"),
                                       ".",
                                       "-x", ".svn"],
                              haltOnFailure=True))

class Mingw64Darwin32Factory(Mingw64Factory):
  host_cpu = "i686"
  host_os = "darwin"
  def __init__(self, **kwargs):
    Mingw64Factory.__init__(self, **kwargs)

# factories that target i686-mingw

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
  gccConfigExtraArgs = "--disable-nls"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64CygwinFactory.__init__(self, **kwargs)

class Mingw32MingwFactory(Mingw64MingwFactory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64MingwFactory.__init__(self, **kwargs)

class Mingw32Darwin32Factory(Mingw64Darwin32Factory):
  target = "i686-w64-mingw32"
  crtConfigExtraArgs = "--enable-lib32 --disable-lib64"
  def __init__(self, **kwargs):
    Mingw64Darwin32Factory.__init__(self, **kwargs)

