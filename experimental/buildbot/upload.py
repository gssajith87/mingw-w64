#!/usr/bin/env python

from ConfigParser import RawConfigParser as ConfigParser
import optparse, os, re, stat, subprocess, sys, datetime, getpass
import cookielib, urllib, urllib2

### random constants
LOGIN_URL = "https://sourceforge.net/account/login.php"
LOGIN_FAIL = '<form action="%s"' % (LOGIN_URL)
EDIT_URL = "https://sourceforge.net/project/admin/editreleases.php"

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
    value = "%s.%s=%s" % (kwargs["section"], kwargs["key"], value)
    configOptionCallback(option, "--config", value, parser, args)
  optparser.add_option("-u", "--user", action="callback", type="string",
                       help="specify sourceforge user name",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "user"})
  optparser.add_option("-p", "--password", action="store_true",
                       help="prompt for sourceforge login password")
  optparser.add_option("-k", "--key", action="callback", type="string",
                       help="specify sourceforge ssh key",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "sshkey"})
  optparser.add_option("-g", "--group-id", action="callback", type="string",
                       help="specify sourceforge group id",
                       callback=configOptionReplacement, callback_args=(config,),
                       callback_kwargs={"section": "sourceforge", "key": "group_id"})
  optparser.add_option("--package-id", "--pkg-id", action="store", type="string",
                       help="specify sourceforge package id", dest="package_id")
  optparser.add_option("-r", "--release-id", action="store", type="string",
                       help="specify sourceforge release id", dest="release_id")

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
  if opts.password:
    # prompt for the password
    delattr(opts, "password")
    prompt = "Password for %s@sourceforge: " % (config.get("sourceforge", "user"))
    password = getpass.getpass(prompt)
    if not config.has_section("sourceforge"):
      config.add_section("sourceforge")
    config.set("sourceforge", "password", password)

  if opts.package_id:
    # specify the package id, based on the given os
    config.set("sourceforge", "package-%s" % (opts.os), opts.package_id)
    delattr(opts, "package_id")

  if opts.release_id:
    # specify the release id, based on the given os
    config.set("sourceforge", "release-%s" % (opts.os), opts.release_id)
    delattr(opts, "release_id")

  ### check for sane arguments
  if opts.datestamp is not None:
    opts.datestamp = "_" + opts.datestamp.strip("_")
    assert re.match("""^_*\d{8}$""", opts.datestamp), \
      "datestamp must be of form yyyymmdd (with optional leading underscore)"

  assert filesize > 1048576, "%s is only %s bytes" %(srcfile, filesize)
  assert (-1 < srcfile.find(".tar.")) or (-1 < srcfile.find(".zip")), "%s is not a tarball" % (srcfile)

  ### argument processing complete, go do things
  upload(srcfile, destfile, config, opts)
  page = publish(destfile, config, opts)
  cleanup(destfile, config, opts, page)

def upload(srcfile, destfile, config, opts):
  if opts.verbose > 0:
    print "processing upload of %s to %s..." % (srcfile, destfile)
  command = ["rsync", "-avPc", "-e", "ssh -i %s -o UserKnownHostsFile=%s",
             srcfile, "%%s@frs.sourceforge.net:uploads/%s" % (destfile)]
  print " ".join(command)
  command[3] = command[3] % (config.get("sourceforge", "sshkey"), "ssh_known_hosts")
  command[5] = command[5] % (config.get("sourceforge", "user"))
  if opts.dry_run:
    print "(rsync skipped due to dry-run)"
  else:
    for attempt in range(0, 5):  # 5 tries
      rsync = subprocess.Popen(command, stderr=subprocess.STDOUT)
      rsync.communicate()
      if rsync.returncode == 0:
        return
    assert(rsync.returncode == 0)

def publish(filename, config, opts):
  if opts.verbose > 0:
    print "processing publish of %s..." % (filename)
  ### set up cookie management
  cookiejar = cookielib.CookieJar()
  opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookiejar))
  urllib2.install_opener(opener)

  ### login to sourceforge
  login_data = {"form_loginname": config.get("sourceforge", "user"),
                "form_pw": config.get("sourceforge", "password"),
                "ssl_status": 1,
                "form_securemode": "yes",
                "login": "Log in"}
  if opts.verbose > 0:
    for item in login_data:
      if item == "form_pw":
        print "%s = <*>" % (item)
      else:
        print "%s = %s" % (item, login_data[item])
  request = urllib2.Request(LOGIN_URL)
  request.add_data(urllib.urlencode(login_data))
  login_page = urllib2.urlopen(request)
  # sourceforge is being weird, we need to submit twice to pick up cookies
  login_page = urllib2.urlopen(request)

  # read the page and guess if we succeeded
  for line in login_page:
    if opts.verbose > 2:
      print line[:-1]
    assert (-1 == line.find(LOGIN_FAIL)), "sourceforge login error"

  ### publish files
  if not opts.dry_run:
    publish_data = {"group_id" : config.get("sourceforge", "group_id"),
                    "package_id": config.get("sourceforge", "package-" + opts.os),
                    "release_id": config.get("sourceforge", "release-" + opts.os),
                    "step2": 1,
                    "file_list[]": filename,
                    "submit": "Add Files and/or Refresh View"}
    publish_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(publish_data))
    print "%s published to sourceforge; editing metadata..." % (filename)
  else:
    publish_data = {"group_id" : config.get("sourceforge", "group_id"),
                    "package_id": config.get("sourceforge", "package-" + opts.os),
                    "release_id": config.get("sourceforge", "release-" + opts.os)}
    publish_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(publish_data))
    print "Skipping publish of %s due to dry-run..." % (filename)
  return publish_page

def cleanup(filename, config, opts, page_data):
  if opts.verbose > 0:
    print "processing cleanup of %s..." % (filename)
  items = []
  item_data = {}

  # figure out the desired file characteristics
  processor = "Other"
  if re.search(r'i.86', filename):
    processor = 'i386'
  if re.search(r'x86.64', filename):
    processor = 'AMD64'
  extension = filename[filename.rindex("."):]
  if opts.datestamp is not None and filename.find(opts.datestamp) != -1:
    prefix = filename[:filename.find(opts.datestamp)]
  else:
    prefix = None

  if opts.debug:
    print "prefix = %s" % (prefix)

  ### scrape through the page to look for files we know about
  r_name = re.compile('<td nowrap><font size="-1">([^<]+)</td>', re.IGNORECASE)
  r_value = re.compile('name="([^"]+)"\s+value="([^"]+)"', re.IGNORECASE)
  r_select = re.compile('<select NAME="(\w+)" >', re.IGNORECASE)
  r_option = re.compile('<OPTION VALUE="(\d+)"[^>]*>([^<]+)</OPTION>', re.IGNORECASE)
  in_form = False
  in_select = None
  for line in page_data.readlines():
    if opts.verbose > 2:
      print line[:-1]
    if line.find('<form action="/project/admin/editreleases.php" method="post">') != -1:
      # new file
      item_data = {}
      in_form = True
    elif in_form and line.find('<input type="hidden" name="') != -1:
      match = r_value.search(line)
      item_data[match.group(1)] = match.group(2)
    elif in_form and line.find('<select NAME="') != -1:
      in_select = r_select.search(line).group(1)
      item_data[in_select] = {}
    elif in_form and in_select is not None and line.find('<OPTION VALUE=') != -1:
      match = r_option.search(line)
      item_data[in_select][match.group(2)] = match.group(1)
    elif in_form and in_select is not None and line.find('</select>') != -1:
      in_select = None
    elif in_form and line.find('</form>') != -1:
      in_form = False
      if "file_id" in item_data and "file_name" in item_data:
        if prefix is not None:
          # calculate the date of the file
          match = re.match("_*(\d{8})", item_data["file_name"][len(prefix):])
          if match is not None:
            datestring = match.group(1)
            datestamp = datetime.date(int(datestring[0:4]), int(datestring[4:6]), int(datestring[6:8]))
            item_data["datestamp"] = datestamp
            items += [item_data]
          else:
            if opts.verbose > 0:
              print "item %s doesn't look like the right type" % (item_data["file_name"])
        else:
          item_data["datestamp"] = datetime.date(datetime.MAXYEAR, 12, 31)
          items += [item_data]
    elif in_form and r_name.search(line):
      item_data["file_name"] = r_name.search(line).group(1)

  items.sort(cmp=lambda x,y:cmp(x["datestamp"], y["datestamp"]), reverse=False)

  skipped_items = 0
  days_to_keep = 7
  if config.has_option("sourceforge", "history"):
    days_to_keep = config.getint("sourceforge", "history")

  for item in items:
    if item["file_name"] == filename:
      edit_data = {"group_id" : config.get("sourceforge", "group_id"),
                   "package_id": config.get("sourceforge", "package-" + opts.os),
                   "release_id": config.get("sourceforge", "release-" + opts.os),
                   "new_release_id": config.get("sourceforge", "release-" + opts.os),
                   "file_id": item["file_id"],
                   "step3": 1,
                   "processor_id": item["processor_id"][processor],
                   "type_id": item["type_id"][filename[filename.rfind("."):]],
                   "submit": "Update/Refresh"}
      if opts.dry_run:
        print "editing item %s (processor %s) skipped due to dry-run" % (
                filename, processor)
      else:
        edit_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(edit_data))
        print "item %s edited (processor %s)" % (filename, processor)

    elif prefix is not None and item["file_name"].startswith(prefix):
      if skipped_items + 1 < days_to_keep:
        if opts.verbose > 0:
          print "keeping item %s" % (item["file_name"])
        skipped_items = skipped_items + 1
      else:
        # should delete this old item
        edit_data = {"group_id" : config.get("sourceforge", "group_id"),
                     "package_id": config.get("sourceforge", "package-" + opts.os),
                     "release_id": config.get("sourceforge", "release-" + opts.os),
                     "file_id": item["file_id"],
                     "im_sure": 1,
                     "step3": "Delete File"}
        if opts.dry_run:
          print "deleting item %s skipped due to dry-run" % (item["file_name"])
        else:
          urllib2.urlopen(EDIT_URL, urllib.urlencode(edit_data))
          print "item %s deleted" % (item["file_name"])
  print "Done"

if __name__ == "__main__":
  main(sys.argv)
