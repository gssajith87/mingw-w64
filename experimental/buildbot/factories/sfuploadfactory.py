# -*- python -*-
# ex: set syntax=python:

# This is the config for just the MinGW-W64 build factory
# See master.cfg for the actual main script

import buildbot
from buildbot.process import factory
from buildbot.process.properties import Property
from buildbot.steps.source import CVS, SVN
from buildbot.steps.shell import Configure, Compile, ShellCommand, WithProperties, SetProperty
from buildbot.steps.transfer import FileDownload, FileUpload

class SourceForgeUploadFactory(factory.BuildFactory):

  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    self.addStep(SetProperty(property="optionTargetOs",
                             doStepIf=lambda step: step.build.hasProperty("target-os"),
                             command=["echo", "--os", Property("target-os")] ))
    self.addStep(SetProperty(property="optionPath",
                             doStepIf=lambda step: step.build.hasProperty("path"),
                             command=["echo", "--path", Property("path")] ))
    self.addStep(SetProperty(property="optionDatestamp",
                             doStepIf=lambda step: step.build.hasProperty("datestamp"),
                             command=["echo", "--datestamp", Property("datestamp")] ))

    # this assumes the following properties have been set:
    # masterdir - the path to the master configuration (has tarballs + scripts + passwords)
    # filename  - the name of the file to upload (relative to masterdir)
    # destname  - how to name the file on the server
    self.addStep(ShellCommand(name="sfupload",
                              description=["uploading"],
                              descriptionDone=["upload"],
                              doStepIf=lambda step: (step.build.getProperty("is_nightly")),
                              workdir=Property("masterdir"),
                              command=["scripts/upload.py",
                                       Property("filename"),
                                       Property("destname"),
                                       Property("optionTargetOs", default=""),
                                       Property("optionPath", default=""),
                                       Property("optionDatestamp", default="")],
                              haltOnFailure=True))

    self.addStep(ShellCommand(name="uploadComplete",
                              description=["removing", "temporary", "file"],
                              descriptionDone=["temporary", "file", "removed"],
                              doStepIf=lambda step: (step.build.getProperty("is_nightly")),
                              workdir=Property("masterdir"),
                              command=["rm", "-fv", Property("filename")]))

