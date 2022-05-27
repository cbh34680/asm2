#!/bin/bash

set -eu # -o pipefail +o posix
unalias -a

cd "$(dirname "$(readlink -f "${BASH_SOURCE:-$0}")")"

valgrind --leak-check=full ./app.exe

exit 0

