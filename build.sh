#!/bin/bash

set -eux # -o pipefail +o posix
unalias -a

cd "$(dirname "$(readlink -f "${BASH_SOURCE:-$0}")")"

rm -rf obj.d/
[ -d obj.d/ ] || mkdir obj.d

gccopts=''
gccopts="${gccopts} -std=c11"
gccopts="${gccopts} -g -O0"
#gccopts="${gccopts} -nostdlib"
#gccopts="${gccopts} -fno-builtin"
gccopts="${gccopts} -ffreestanding"
gccopts="${gccopts} -fno-asynchronous-unwind-tables"
gccopts="${gccopts} -mno-red-zone"
gccopts="${gccopts} -nostdinc"
gccopts="${gccopts} -I ${PWD}/inc.d"

gcc ${gccopts} -static -c src.d/init.c -o obj.d/init.o
gcc ${gccopts} -static -c src.d/log10.c -o obj.d/log10.o
gcc ${gccopts} -static -c src.d/puts.c -o obj.d/puts.o
gcc ${gccopts} -static -c src.d/strcpy.c -o obj.d/strcpy.o
gcc ${gccopts} -static -c app.c -o app.o

nasmopts=''
nasmopts="${nasmopts} -f elf64"
nasmopts="${nasmopts} -i ${PWD}/inc.d"

nasm ${nasmopts} src.d/start.s -o obj.d/start.o
nasm ${nasmopts} src.d/alloca.s -o obj.d/alloca.o
nasm ${nasmopts} src.d/memchr.s -o obj.d/memchr.o
nasm ${nasmopts} src.d/memcpy.s -o obj.d/memcpy.o
nasm ${nasmopts} src.d/memmove.s -o obj.d/memmove.o
nasm ${nasmopts} src.d/memset.s -o obj.d/memset.o
nasm ${nasmopts} src.d/strchr.s -o obj.d/strchr.o
nasm ${nasmopts} src.d/strlen.s -o obj.d/strlen.o
nasm ${nasmopts} src.d/syscall.s -o obj.d/syscall.o

#
ldopts=''
ldopts="${ldopts} -e _start"
ldopts="${ldopts} -Map app.map"

ld ${ldopts} -o app.exe \
\
obj.d/start.o \
app.o \
\
obj.d/init.o \
obj.d/log10.o \
obj.d/puts.o \
obj.d/strcpy.o \
\
obj.d/alloca.o \
obj.d/memchr.o \
obj.d/memcpy.o \
obj.d/memmove.o \
obj.d/memset.o \
obj.d/strchr.o \
obj.d/strlen.o \
obj.d/syscall.o \
#

./app.exe || echo $?

exit 0

