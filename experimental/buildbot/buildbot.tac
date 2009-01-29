
from twisted.application import service
from buildbot.master import BuildMaster

basedir = r'/opt/buildbot/mingw-w64/master'
configfile = r'master.cfg'

application = service.Application('buildmaster')
BuildMaster(basedir, configfile).setServiceParent(application)

