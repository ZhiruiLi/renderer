#!/usr/bin/env bash

# let script exit if a command fails
set -o errexit
# let script exit if an unsed variable is used
set -o nounset
# catch mysqldump fails in e.g. mysqldump | gzip.
# The exit status of the last command that threw a non-zero exit code is returned.
set -o pipefail
# trace what gets executed. Useful for debugging.
# set -o xtrace

# Set magic variables for current file, basename, and directory at the top of your script for convenience.
__dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
__file="${__dir}/$(basename "${BASH_SOURCE[0]}")"
__base="$(basename ${__file} .sh)"
__root="$(cd "$(dirname "${__dir}")" && pwd)" # <-- change this as it depends on your app

# if [[ $# -ne 1 ]] ; then
#   echo "usage:" $0 "<ARG>"
#   exit 1
# fi

arg1="${1:-}"

git submodule update --init --recursive
[ -d build ] || mkdir build
cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

