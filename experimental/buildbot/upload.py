#!/usr/bin/env python

from ConfigParser import RawConfigParser as ConfigParser
import os, re, stat, subprocess, sys
import cookielib, urllib, urllib2

def main(argv):
  config = ConfigParser()
  config.read("password.ini")

  # check that the file exists
  assert len(argv) == 3
  srcfile = argv[1]
  destfile = argv[2]
  filesize = os.stat(srcfile)[stat.ST_SIZE]
  assert filesize > 1048576, "%s is only %s bytes" %(srcfile, filesize)
  assert (-1 < srcfile.find(".tar.")) or (-1 < srcfile.find(".zip")), "%s is not a tarball" % (srcfile)

  upload(srcfile, destfile, config)
  publish(destfile, config)

def upload(srcfile, destfile, config):
  command = ["rsync", "-avPc", "-e", "ssh -i %s", 
             srcfile, "%%s@frs.sourceforge.net:uploads/%s" % (destfile)]
  print " ".join(command)
  command[3] = command[3] % (config.get("sourceforge", "sshkey"))
  command[5] = command[5] % (config.get("sourceforge", "user"))
  for attempt in range(0, 5):  # 5 tries
    rsync = subprocess.Popen(command)
    rsync.communicate()
    if rsync.returncode == 0:
      return
  assert(rsync.returncode == 0)

def publish(filename, config):
  ### random constants
  LOGIN_URL = "https://sourceforge.net/account/login.php"
  LOGIN_FAIL = '<form action="%s"' % (LOGIN_URL)
  EDIT_URL = "https://sourceforge.net/project/admin/editreleases.php"

  ### set up cookie management
  cookiejar = cookielib.CookieJar()
  opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookiejar))
  urllib2.install_opener(opener)

  ### login to sourceforge
  login_data = {"form_loginname": config.get("sourceforge", "user"),
                "form_pw": config.get("sourceforge", "password"),
                "ssl_status": 1,
                "login": "Log in"}
  #print urllib.urlencode(login_data)
  login_page = urllib2.urlopen(LOGIN_URL, urllib.urlencode(login_data))

  # read the page and guess if we succeeded
  for line in login_page:
    assert (-1 == line.find(LOGIN_FAIL)), "sourceforge login error"

  ### publish files
  publish_data = {"group_id" : config.get("sourceforge", "group_id"),
                  "package_id": config.get("sourceforge", "package_id"),
                  "release_id": config.get("sourceforge", "release_id"),
                  "step2": 1,
                  "file_list[]": filename,
                  "submit": "Add Files and/or Refresh View"}
  publish_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(publish_data))
  print "%s published to sourceforge; editing metadata..." % (filename)

  ### edit file attributes
  # figure out the file characteristics
  processor = "Other"
  if re.search(r'i.86', filename):
    processor = 'i386'
  if re.search(r'x86.64', filename):
    processor = 'AMD64'
  extension = filename[filename.rindex("."):]
  r_processor = re.compile(r'<OPTION VALUE="(\d+)"[^>]*>%s</OPTION>' % processor, re.IGNORECASE)
  r_type = re.compile(r'<OPTION VALUE="(\d+)"[^>]*>%s</OPTION>' % extension, re.IGNORECASE)

  # look throught the page about this file
  edit_lines = publish_page.readlines()
  line_state = 0
  for line in edit_lines:
    if line.find('<form action="/project/admin/editreleases.php"') != -1:
      line_state = 1
      continue
    if line_state is 1 and line.find('<input type="hidden" name="file_id"') != -1:
      file_id = line.split('"')[5] # value=
      line_state = 2
      continue
    if line_state is 2 and line.find(">%s<" % (filename)) != -1:
      line_state = 3
      continue
    if line_state is 3:
      match = r_processor.search(line)
      if match is not None:
        processor_id = match.group(1)
        line_state = 4
        continue
    if line_state is 4:
      match = r_type.search(line)
      if match is not None:
        type_id = match.group(1)
        line_state = 5
        break
    if line.find("</form") != -1:
      line_state = 0
  assert(line_state is 5, "failed to find information for file editing")

  edit_data = {"group_id" : config.get("sourceforge", "group_id"),
               "package_id": config.get("sourceforge", "package_id"),
               "release_id": config.get("sourceforge", "release_id"),
               "new_release_id": config.get("sourceforge", "release_id"),
               "file_id": file_id,
               "step3": 1,
               "processor_id": processor_id,
               "type_id": type_id,
               "submit": "Update/Refresh"}
  edit_page = urllib2.urlopen(EDIT_URL, urllib.urlencode(edit_data))
  print "%s is a %s %s" % (filename, processor, extension)
  print "Done"

if __name__ == "__main__":
  main(sys.argv)
