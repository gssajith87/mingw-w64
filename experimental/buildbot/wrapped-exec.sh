#!/bin/bash
# Wrapper script to launch make with a fixed path
# Usage: $0 <relative path> <command> <args>
export PATH=$(cd $(dirname $0) && pwd)/$1:$PATH
shift
exec $@
