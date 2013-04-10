#!/usr/bin/env python
# -*- python coding: utf-8 -*-

"""
download-src.py

Simple wget-like thing to grab a source tarball from SourceForge

It would be much better to just replace this script with wget, but that isn't
guaranteed to exist on all build slaves (in particular, the Darwin ones).

Has only the features required to grab a url and dump it to a file, following
any redirects necessary.  Will wait for up to *30* minutes and retry once per
minute if the download attempt results in a HTTP 404 (because the SourceForge
mirrors may not have updated yet).  This script does not have useful progress
reporting.  Instead, it prints a character once every fifteen seconds to make
sure buildbot will not kill it while waiting.  The download will be attempted
five times starting with the first response which was not a HTTP 404, at five
minute intervals.

Usage:
  %s <url> <destination>

Note that the destination is a file, and not a directory.  Any existing files
will be overwritten.
"""

###
# program parameters
# TODO: command line argument parsing

PROGRESS_INTERVAL = 15 # number of seconds between progress indicator display
RETRIES_404 = 30       # number of attempts for 404 errors
DELAY_404 = 60         # number of seconds to wait between retries due to 404
RETRIES_OTHER = 5      # number of attempts for other errors
DELAY_OTHER = 5 * 60   # number of seconds between retries of non-404 reasons

import os
import re
import sys
import threading
import time
#import urllib
try:
  from urllib.request import FancyURLopener
except ImportError:
  from urllib import FancyURLopener

class ProgressReporter(threading.Thread):
  """Dumb progress reporter; just keeps printing once a second to prevent
     anything from timing out on the buildbot."""
  def __init__(self, interval=15, *args, **kwargs):
    threading.Thread.__init__(self, *args, **kwargs)
    self.daemon = True
    self.interval = interval
    self.stop = False

  def run(self):
    while not self.stop:
      sys.stdout.flush()
      sys.stdout.write('#')
      sys.stdout.flush()
      time.sleep(self.interval)

class CustomURLopener(FancyURLopener):
  def __init__(self, not_found_tries=30, not_found_delay=60,
                     *args, **kwargs):
    FancyURLopener.__init__(self, *args, **kwargs)
    self.tries = 0
    self.total_tries = not_found_tries
    self.not_found_delay = not_found_delay
    self.found = False # ever had anything not 404

  def prompt_user_passwd(self, host, realm):
    # never prompt for password; if we need one, bail
    return (None, None)

  def http_error(self, url, fp, errcode, errmsg, headers, data=None):
    if (errcode != 404):
      self.found = True
    return FancyURLopener.http_error(self, url, fp, errcode, errmsg, headers, data)

  def http_error_404(self, url, fp, errcode, errmsg, headers, data=None):
    if self.found:
      return None
    self.tries = self.tries + 1
    if self.tries >= self.total_tries:
      # we've run out of retries
      print("HTTP 404: http:%s [try %d of %d]" % (url, self.tries, self.total_tries))
      return None
    print("HTTP 404: http:%s [try %d of %d - retrying]" % (url, self.tries, self.total_tries))
    time.sleep(self.not_found_delay)
    # retry
    void = fp.read()
    fp.close()
    return self.open("http:" + url)

  def http_error_default(self, url, fp, errcode, errmsg, headers):
    # don't deal with 404 here; however, _do_ raise an exception, so we can be
    # caught and dealt with in main()
    request.URLopener.http_error_default(self, url, fp, errcode, errmsg, headers)

def main(argv):
  retry_count = RETRIES_OTHER
  retry_delay = DELAY_OTHER

  if len(argv) != 3:
    sys.stderr.write("Unexpect number of arguments\n")
    print(__doc__ % (argv[0]))
    return -1

  url = sys.argv[1].replace(" ", "%20")
  dest = sys.argv[2]
  if not re.match("(?:https?|ftp)://", url):
    msg = "URL %s does not use a whitelisted protocol" % (url)
    print(msg)
    raise RuntimeError(msg)

  thread = ProgressReporter(interval=PROGRESS_INTERVAL)
  thread.start()
  try:
    for attempt in range(1, retry_count + 1):
      try:
        opener = CustomURLopener(not_found_tries=RETRIES_404, not_found_delay=DELAY_404)
        (filename, headers) = opener.retrieve(url, dest)
        if 'Content-Length' in headers:
          remote_size = int(headers['Content-Length'])
          if os.path.exists(filename):
            local_size = os.path.getsize(filename)
          else:
            local_size = 0
          if remote_size != local_size:
            raise IOError("download incomplete (%s/%s bytes)" % (local_size, remote_size))
        print("...Done")
        return 0
        break
      except IOError as error:
        if error.args[0] == 'http error' and error.args[1] == 404:
          # the fact that we got 404 means we shouldn't continue
          break
        else:
          retry = "[try %d of %d%s]" % (attempt,
                                        retry_count,
                                        attempt < retry_count and " - retrying" or "")
          if error.args[0] == 'http error':
            print("HTTP Error %d: %s %s" % (error.args[1], error.args[2], retry))
          else: 
            print("IO error: %s %s" % (str(error), retry))
          sys.stdout.flush()
          if attempt < retry_count:
            time.sleep(retry_delay)
    return 1 # for loop finished, meaning we errored out
  finally:
    thread.stop = True
    if not thread.daemon:
      thread.join()

if __name__ == "__main__":
  sys.exit(main(sys.argv))

