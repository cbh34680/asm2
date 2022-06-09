#!/bin/bash

set -eux # -o pipefail +o posix
unalias -a

cd "$(dirname "$(readlink -f "${BASH_SOURCE:-$0}")")"

rm -rf obj.d/
[ -d obj.d/ ] || mkdir obj.d

##
## cc
##

cc='gcc'
#cc='clang-11'

ccopts=''

ccopts="${ccopts} -I ${PWD}/inc.d"

ccopts="${ccopts} -std=c11"
ccopts="${ccopts} -g -O0"
#ccopts="${ccopts} -static"

ccopts="${ccopts} -ffreestanding"
ccopts="${ccopts} -fno-builtin"
ccopts="${ccopts} -fno-asynchronous-unwind-tables"
ccopts="${ccopts} -fno-pic"
ccopts="${ccopts} -fno-pie"

#ccopts="${ccopts} -fstack-protector"
ccopts="${ccopts} -fno-stack-protector"
#ccopts="${ccopts} -fstack-protector-strong"
#ccopts="${ccopts} -fstack-protector-all"

ccopts="${ccopts} -m64"
ccopts="${ccopts} -masm=intel"
ccopts="${ccopts} -mno-red-zone"

#ccopts="${ccopts} -mpreferred-stack-boundary=3"
##ccopts="${ccopts} -mincoming-stack-boundary=3"
##ccopts="${ccopts} -mstackrealign"

ccopts="${ccopts} -nostdlib"
ccopts="${ccopts} -nostdinc"
ccopts="${ccopts} -Wall"
ccopts="${ccopts} -Wno-unused-variable"
ccopts="${ccopts} -Wno-unused-but-set-variable"


$cc ${ccopts} -c src.d/abort.c -o obj.d/abort.o
$cc ${ccopts} -c src.d/brk.c -o obj.d/brk.o
$cc ${ccopts} -c src.d/init.c -o obj.d/init.o
$cc ${ccopts} -c src.d/log10.c -o obj.d/log10.o
$cc ${ccopts} -c src.d/malloc.c -o obj.d/malloc.o
$cc ${ccopts} -c src.d/print.c -o obj.d/print.o
$cc ${ccopts} -c src.d/sprint.c -o obj.d/sprint.o
$cc ${ccopts} -c src.d/str.c -o obj.d/str.o
#$cc ${ccopts} -c src.d/va.c -o obj.d/va.o

$cc ${ccopts} -c app.c -o app.o -v
$cc ${ccopts} -c app.c -E -P -C -o app.pc

#$cc ${ccopts} -shared -fPIC libmy.c -o libmy.so

##
## nasm
##

nasmopts=''
nasmopts="${nasmopts} -f elf64"
nasmopts="${nasmopts} -i ${PWD}/inc.d"

nasm ${nasmopts} src.d/alloca.s -o obj.d/alloca.o
nasm ${nasmopts} src.d/atoi.s -o obj.d/atoi.o
nasm ${nasmopts} src.d/atoul.s -o obj.d/atoul.o
nasm ${nasmopts} src.d/data.s -o obj.d/data.o
nasm ${nasmopts} src.d/debg.s -o obj.d/debg.o
nasm ${nasmopts} src.d/itoa.s -o obj.d/itoa.o
nasm ${nasmopts} src.d/ltoa.s -o obj.d/ltoa.o
nasm ${nasmopts} src.d/memchr.s -o obj.d/memchr.o
nasm ${nasmopts} src.d/memcmp.s -o obj.d/memcmp.o
nasm ${nasmopts} src.d/memcpy.s -o obj.d/memcpy.o
nasm ${nasmopts} src.d/memmove.s -o obj.d/memmove.o
nasm ${nasmopts} src.d/memset.s -o obj.d/memset.o
nasm ${nasmopts} src.d/pNx.s -o obj.d/pNx.o
nasm ${nasmopts} src.d/stack.s -o obj.d/stack.o
nasm ${nasmopts} src.d/start.s -o obj.d/start.o
nasm ${nasmopts} src.d/strchr.s -o obj.d/strchr.o
nasm ${nasmopts} src.d/strdupa.s -o obj.d/strdupa.o
nasm ${nasmopts} src.d/strlen.s -o obj.d/strlen.o
nasm ${nasmopts} src.d/test.s -o obj.d/test.o

nasm ${nasmopts} src.d/syscall.s -o obj.d/syscall.o

##
## ld
##

#
ldopts=''
ldopts="${ldopts} --verbose"
ldopts="${ldopts} -e _start"
ldopts="${ldopts} -Map app.map"
#ldopts="${ldopts} -L. -lmy"

ld ${ldopts} -o app.exe \
\
app.o \
\
obj.d/start.o \
\
obj.d/abort.o \
obj.d/alloca.o \
obj.d/atoi.o \
obj.d/atoul.o \
obj.d/brk.o \
obj.d/data.o \
obj.d/debg.o \
obj.d/init.o \
obj.d/itoa.o \
obj.d/ltoa.o \
obj.d/log10.o \
obj.d/malloc.o \
obj.d/memchr.o \
obj.d/memcmp.o \
obj.d/memcpy.o \
obj.d/memmove.o \
obj.d/memset.o \
obj.d/pNx.o \
obj.d/print.o \
obj.d/sprint.o \
obj.d/stack.o \
obj.d/strchr.o \
obj.d/str.o \
obj.d/strdupa.o \
obj.d/strlen.o \
obj.d/syscall.o \
obj.d/test.o \
\
> app.ls


export LD_LIBRARY_PATH=.
./app.exe || echo $?

exit 0

