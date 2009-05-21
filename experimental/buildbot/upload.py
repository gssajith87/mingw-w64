#!/usr/bin/env python

from ConfigParser import RawConfigParser as ConfigParser
import getopt, os, re, stat, subprocess, sys, datetime
import cookielib, urllib, urllib2

### random constants
LOGIN_URL = "https://sourceforge.net/account/login.php"
LOGIN_FAIL = '<form action="%s"' % (LOGIN_URL)
EDIT_URL = "https://sourceforge.net/project/admin/editreleases.php"

def main(argv):
  config = ConfigParser()
  config.read("config.ini")

  # check that the file exists
  (optparse, args) = getopt.gnu_getopt(argv, 'd:o:nv', ['datestamp=', 'os=', 'dry-run', 'verbose'])
  while "" == args[-1]:
    # remove any trailing empty parameters
    args.pop()
  assert len(args) == 3
  srcfile = args[1]
  destfile = args[2]
  filesize = os.stat(srcfile)[stat.ST_SIZE]

  opts = {
    "datestamp": None,
    "os": "w64",
    "dry-run": False,
    "verbose": False
  }
  for o,a in optparse:
    if o in ("-d", "--datestamp"):
      assert re.match("""^_*\d{8}$""", a), \
             "datestamp must be of form yyyymmdd (with optional leading underscore)"
      opts["datestamp"] = "_" + a.strip("_")
    elif o in ("-n", "--dry-run"):
      opts["dry-run"] = True
    elif o in ("-o", "--os"):
      opts["os"] = a
    elif o in ("-v", "--verbose"):
      opts["verbose"] = True
  assert filesize > 1048576, "%s is only %s bytes" %(srcfile, filesize)
  assert (-1 < srcfile.find(".tar.")) or (-1 < srcfile.find(".zip")), "%s is not a tarball" % (srcfile)

  upload(srcfile, destfile, config, opts)
  page = publish(destfile, config, opts)
  cleanup(destfile, config, opts, page)

def upload(srcfile, destfile, config, opts):
  command = ["rsync", "-avPc", "-e", "ssh -i %s -o UserKnownHostsFile=%s",
             srcfile, "%%s@frs.sourceforge.net:uploads/%s" % (destfile)]
  print " ".join(command)
  command[3] = command[3] % (config.get("sourceforge", "sshkey"), "ssh_known_hosts")
  command[5] = command[5] % (config.get("sourceforge", "user"))
  if opts["dry-run"]:
    print "(rsync skipped due to dry-run)"
  else:
    for attempt in range(0, 5):  # 5 tries
      rsync = subprocess.Popen(command, stderr=subprocess.STDOUT)
      rsync.communicate()
      if rsync.returncode == 0:
        return
    assert(rsync.returncode == 0)

def publish(filename, config, opts):
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
  if opts["verbose"]:
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
    if opts["verbose"]:
      print line[:-1]
    assert (-1 == line.find(LOGIN_FAIL)), "sourceforge login error"

  ### publish files
  if not opts["dry-run"]:
    publish_data = {"group_id" : config.get("sourceforge", "group_id"),
                    "package_id": config.get("sourceforge", "package-" + opts["os"]),
                    "release_id": config.get("sourceforge", "release-" + opts["os"]),
                    "step2": 1,
                    "file_list[]": filename,
                    "submit": "Add Files and/or Refresh View"}
    publish_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(publish_data))
    print "%s published to sourceforge; editing metadata..." % (filename)
  else:
    publish_data = {"group_id" : config.get("sourceforge", "group_id"),
                    "package_id": config.get("sourceforge", "package-" + opts["os"]),
                    "release_id": config.get("sourceforge", "release-" + opts["os"])}
    publish_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(publish_data))
    print "Skipping publish of %s due to dry-run..." % (filename)
  return publish_page

def cleanup(filename, config, opts, page_data):
  items = []
  item_data = {}

  ### scrape through the page to look for files we know about
  r_name = re.compile('<td nowrap><font size="-1">([^<]+)</td>', re.IGNORECASE)
  r_value = re.compile('name="([^"]+)"\s+value="([^"]+)"', re.IGNORECASE)
  r_select = re.compile('<select NAME="(\w+)" >', re.IGNORECASE)
  r_option = re.compile('<OPTION VALUE="(\d+)"[^>]*>([^<]+)</OPTION>', re.IGNORECASE)
  in_form = False
  in_select = None
  for line in page_data.readlines():
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
        items += [item_data]
    elif in_form and r_name.search(line):
      item_data["file_name"] = r_name.search(line).group(1)

  # figure out the desired file characteristics
  processor = "Other"
  if re.search(r'i.86', filename):
    processor = 'i386'
  if re.search(r'x86.64', filename):
    processor = 'AMD64'
  extension = filename[filename.rindex("."):]
  if opts["datestamp"] is not None and filename.find(opts["datestamp"]) != -1:
    prefix = filename[:filename.find(opts["datestamp"])]
    cutoff = datetime.date(int(opts["datestamp"][1:5]),
                           int(opts["datestamp"][5:7]),
                           int(opts["datestamp"][7:9]))
    cutoff -= datetime.timedelta(7)
  else:
    prefix = None

  for item in items:
    if item["file_name"] == filename:
      edit_data = {"group_id" : config.get("sourceforge", "group_id"),
                   "package_id": config.get("sourceforge", "package-" + opts["os"]),
                   "release_id": config.get("sourceforge", "release-" + opts["os"]),
                   "new_release_id": config.get("sourceforge", "release-" + opts["os"]),
                   "file_id": item["file_id"],
                   "step3": 1,
                   "processor_id": item["processor_id"][processor],
                   "type_id": item["type_id"][filename[filename.rfind("."):]],
                   "submit": "Update/Refresh"}
      if opts["dry-run"]:
        print "editing item %s (processor %s) skipped due to dry-run" % (
                filename, processor)
      else:
        edit_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(edit_data))
        print "item %s edited (processor %s)" % (filename, processor)
    elif prefix is not None and item["file_name"].startswith(prefix):
      match = re.match("_*(\d{8})", item["file_name"][len(prefix):])
      if match is not None:
        datestring = match.group(1)
        datestamp = datetime.date(int(datestring[0:4]), int(datestring[4:6]), int(datestring[6:8]))
        if datestamp < cutoff:
          edit_data = {"group_id" : config.get("sourceforge", "group_id"),
                       "package_id": config.get("sourceforge", "package-" + opts["os"]),
                       "release_id": config.get("sourceforge", "release-" + opts["os"]),
                       "file_id": item["file_id"],
                       "im_sure": 1,
                       "step3": "Delete File"}
          if opts["dry-run"]:
            print "deleting item %s skipped due to dry-run" % (item["file_name"])
          else:
            urllib2.urlopen(EDIT_URL, urllib.urlencode(edit_data))
            print "item %s deleted" % (item["file_name"])
  return
  print "Done"

if __name__ == "__main__":
  main(sys.argv)
