#!/usr/bin/env python

from ConfigParser import RawConfigParser as ConfigParser
import optparse, os, re, stat, subprocess, sys, datetime
import cookielib, urllib, urllib2

def main(argv):
  config = ConfigParser()
  config.read("config.ini")

  ### get arguments
  optparser = optparse.OptionParser(
    usage="%prog [options] <srcfile> <destfile>",
    description="Uploads a file to SourceForge and publishes it for mingw-w64")
  optparser.enable_interspersed_args()

  optparser.add_option("-d", "--datestamp", action="store", dest="datestamp",
                       help="date stamp to add to the file name")
  optparser.add_option("-n", "--dry-run", action="store_true", dest="dry_run")
  optparser.add_option("-o", "--os", action="store", dest="os")
  optparser.add_option("-v", "--verbose", action="count", dest="verbose")
  optparser.add_option("--debug", action="store_true", dest="debug")

  optparser.set_default("datestamp", None)
  optparser.set_default("os", "w64")
  optparser.set_default("dry_run", False)
  optparser.set_default("verbose", 0)
  optparser.set_default("debug", False)

  def configOptionCallback(option, opt_str, value, parser, *args):
    """ an option parser callback to put things into the ini parser """
    try:
      section = value[:value.index(".")]
      value = value[len(section) + 1:]
      key = value[:value.index("=")]
      value = value[len(key) + 1:]
    except ValueError,e:
      raise optparse.OptionValueError(
        "invalid configuration value:\n  %s\nformat is <section>.<key>=<value>" % (value))
    if not args[0].has_section(section):
      args[0].add_section(section)
    args[0].set(section, key, value)

  optparser.add_option("-c", "--config", action="callback", type="string",
                       help="set a configuration value section.key=value",
                       callback=configOptionCallback, callback_args=(config,))

  def configOptionReplacement(option, opt_str, value, parser, args, **kwargs):
    """ an option parser for a shorthand for a configOptionCallback """
    if value is not None and value is not "":
      value = "%s.%s=%s" % (kwargs["section"], kwargs["key"], value)
      configOptionCallback(option, "--config", value, parser, args)
  optparser.add_option("-u", "--user", action="callback", type="string",
                       help="specify sourceforge user name",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "user"})
  optparser.add_option("-k", "--key", action="callback", type="string",
                       help="specify sourceforge ssh key",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "sshkey"})
  optparser.add_option("-g", "--group-id", action="callback", type="string",
                       help="specify sourceforge group id",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "group_id"})
  optparser.add_option("-p", "--path", action="store", type="string",
                       help="specify upload path", dest="path")

  (opts, args) = optparser.parse_args(args=argv)
  while "" == args[-1]:
    # remove any trailing empty parameters
    args.pop()
  if (len(args) != 3):
    optparser.print_help()
    sys.exit(1)
  srcfile = args[1]
  destfile = args[2]
  filesize = os.stat(srcfile)[stat.ST_SIZE]

  ### deal with arguments that depended on other arguments
  if opts.path:
    config.set("sourceforge", "path-%s" % (opts.os), opts.path)
    delattr(opts, "path")

  ### check for sane arguments
  if opts.datestamp is not None:
    opts.datestamp = "_" + opts.datestamp.strip("_")
    assert re.match("""^_*\d{8}$""", opts.datestamp), \
      "datestamp must be of form yyyymmdd (with optional leading underscore)"

  assert filesize > 1048576, "%s is only %s bytes" %(srcfile, filesize)
  assert (-1 < srcfile.find(".tar.")) or (-1 < srcfile.find(".zip")), "%s is not a tarball" % (srcfile)

  ### argument processing complete, go do things
  temppath = upload(srcfile, destfile, config, opts)
  assert(temppath is not None)
  destpath = publish(temppath, destfile, config, opts)
  assert(destpath is not None)

  cleanup(destpath, destfile, config, opts)

def upload(srcfile, destfile, config, opts):
  group_id = config.get("sourceforge", "group_id")

  assert destfile.find("/") == -1, "destination file name cannot contain path separators!"
  assert destfile.find(" ") == -1, "destination file name cannot contain spaces!"

  if opts.verbose > 0:
    print "processing upload of %s to OldFiles/%s..." % (srcfile, destfile)
  temppath = "/home/frs/project/%s/%s/%s/OldFiles/%s" % (
             group_id[0], group_id[0:2], group_id, destfile)
  command = ["rsync", "-zvtPc", "-e", "ssh -i %s -o UserKnownHostsFile=%s", srcfile,
             "%%s,%s@frs.sourceforge.net:%s" % (group_id, temppath)]
  print " ".join(command)
  command[3] = command[3] % (config.get("sourceforge", "sshkey"), "ssh_known_hosts")
  command[5] = command[5] % (config.get("sourceforge", "user"))
  if opts.dry_run:
    print "(rsync skipped due to dry-run)"
    return temppath
  else:
    for attempt in range(0, 5):  # 5 tries
      rsync = subprocess.Popen(command, stderr=subprocess.STDOUT)
      rsync.communicate()
      if rsync.returncode == 0:
        return temppath
    assert(rsync.returncode == 0)
  return None

def publish(temppath, filename, config, opts):
  group_id = config.get("sourceforge", "group_id")
  try:
    destpath = config.get("sourceforge", "path-%s" % (opts.os))
  except:
    destpath = "OldFiles/Automated Uploads"
  destpath = "/home/frs/project/%s/%s/%s/%s/%s" % (
    group_id[0], group_id[0:2], group_id, destpath, filename)
  if opts.verbose > 0:
    print 'renaming file "%s" to "%s"...' % (temppath, destpath)
  command = ["sftp", "-b", "-", "-o", "IdentityFile=%s", "%%s,%s@frs.sourceforge.net" % (group_id)]
  batch = 'rename "%s" "%s"' % (temppath, destpath)
  print "%s | %s" % (batch, " ".join(command))
  command[4] = command[4] % (config.get("sourceforge", "sshkey"))
  command[5] = command[5] % (config.get("sourceforge", "user"))
  if opts.dry_run:
    print "(publish skipped due to dry-run)"
    return destpath
  else:
    for attempt in range(0, 5):  # 5 tries
      sftp = subprocess.Popen(command, stdin=subprocess.PIPE, stderr=subprocess.STDOUT)
      sftp.communicate(batch)
      if sftp.returncode == 0:
        return destpath
    assert(sftp.returncode == 0)
  return None

def cleanup(destpath, filename, config, opts):
  group_id = config.get("sourceforge", "group_id")
  if opts.verbose > 0:
    print "processing cleanup of %s..." % (filename)

  if opts.datestamp is not None and filename.find(opts.datestamp) != -1:
    prefix = filename[:filename.find(opts.datestamp)]
  else:
    # we don't have enough information to clean anything up
    if opts.verbose > 0:
      print "no datestamp given or not found in file %s" % (filename)
    return

  command = ["sftp", "-b", "-", "-o", "IdentityFile=%s", "%%s,%s@frs.sourceforge.net" % (group_id)]

  dir = "/".join(destpath.split("/")[:-1])
  list_batch = "\n".join([
    'cd "%s"' % (dir),
    'ls %s*' % (prefix)])

  print "%s | %s" % (list_batch, " ".join(command))
  command[4] = command[4] % (config.get("sourceforge", "sshkey"))
  command[5] = command[5] % (config.get("sourceforge", "user"))

  sftp = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  (stdout, stderr) = sftp.communicate(list_batch)
  print stderr
  assert sftp.returncode == 0, "failed to get list of existing files"

  items = []
  for line in stdout.split("\n"):
    if line.startswith("sftp>"):
      # echoing input
      continue
    if line == "":
      # empty?
      continue
    filename = line.strip()
    if not filename.startswith(prefix):
      if opts.verbose > 0:
        print 'item "%s" does not start with the correct prefix "%s"' % (filename, prefix)
      continue
    if filename.find('"') != -1:
      if opts.verbose > 0:
        print 'deletion of item "%s" skipped due to unsafe characters' % (filename)
      continue
    match = re.match("_*(\d{8})", filename[len(prefix):])
    if match is not None:
      datestring = match.group(1)
      datestamp = datetime.date(int(datestring[0:4]), int(datestring[4:6]), int(datestring[6:8]))
      items.append({"datestamp": datestamp,
                    "file_name": filename})
    else:
      if opts.verbose > 0:
        print "file %s does not seem to have a date" % (filename)
      continue

  items.sort(None, lambda x:x["datestamp"])

  days_to_keep = 7
  if config.has_option("sourceforge", "history"):
    days_to_keep = config.getint("sourceforge", "history")

  for item in items[:-days_to_keep]:
    file_to_delete = "%s/%s" % (dir, item["file_name"])
    if opts.dry_run:
      print 'deleting item "%s" skipped due to dry-run' % (file_to_delete)
    else:
      delete_batch = 'rm "%s"' % (file_to_delete)
      sftp =  subprocess.Popen(command, stdin=subprocess.PIPE, stderr=subprocess.STDOUT)
      sftp.communicate(delete_batch)
      assert sftp.returncode == 0, "failed to delete file %s" % (file_to_delete)
      print "item %s deleted" % (file_to_delete)

  print "Done"

if __name__ == "__main__":
  main(sys.argv)
