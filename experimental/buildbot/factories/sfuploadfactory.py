# -*- python -*-
# ex: set syntax=python:

# This is the config for just the MinGW-W64 build factory
# See master.cfg for the actual main script

import buildbot
from buildbot.process import factory
from buildbot.steps.source import CVS, SVN
from buildbot.steps.shell import Configure, Compile, ShellCommand, WithProperties, SetProperty
from buildbot.steps.transfer import FileDownload, FileUpload
from scripts.buildsteps import ShellCommandConditional

class SourceForgeUploadFactory(factory.BuildFactory):

  def __init__(self, **kwargs):

    factory.BuildFactory.__init__(self, **kwargs)

    # this assumes the following properties have been set:
    # masterdir - the path to the master configuration (has tarballs + scripts + passwords)
    # filename  - the name of the file to upload (relative to masterdir)
    # destname  - how to name the file on the server
    self.addStep(ShellCommandConditional,
                 condprop="is_nightly",
                 name="sfupload",
                 description=["uploading"],
                 descriptionDone=["upload"],
                 workdir=WithProperties("%(masterdir)s"),
                 command=["scripts/upload.py",
                          WithProperties("%(filename)s"),
                          WithProperties("%(destname)s"),
                          WithProperties("%(target-os:+--os)s"),
                          WithProperties("%(target-os:-)s"),
                          WithProperties("%(datestamp:+--datestamp)s"),
                          WithProperties("%(datestamp:-)s")],
                 haltOnFailure=True)

