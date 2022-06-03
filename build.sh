#!/bin/bash

set -eux # -o pipefail +o posix
unalias -a

cd "$(dirname "$(readlink -f "${BASH_SOURCE:-$0}")")"

rm -rf obj.d/
[ -d obj.d/ ] || mkdir obj.d

gccopts=''
gccopts="${gccopts} -std=c11"
gccopts="${gccopts} -g -O0"
#gccopts="${gccopts} -fno-builtin"
#gccopts="${gccopts} -static"
gccopts="${gccopts} -ffreestanding"
gccopts="${gccopts} -fno-asynchronous-unwind-tables"
gccopts="${gccopts} -masm=intel"
gccopts="${gccopts} -mno-red-zone"
gccopts="${gccopts} -nostdlib"
gccopts="${gccopts} -nostdinc"
gccopts="${gccopts} -Wall -Wno-unused-variable -Wno-unused-but-set-variable"
gccopts="${gccopts} -I ${PWD}/inc.d"

gcc ${gccopts} -c src.d/abort.c -o obj.d/abort.o
gcc ${gccopts} -c src.d/brk.c -o obj.d/brk.o
gcc ${gccopts} -c src.d/init.c -o obj.d/init.o
gcc ${gccopts} -c src.d/log10.c -o obj.d/log10.o
gcc ${gccopts} -c src.d/malloc.c -o obj.d/malloc.o
gcc ${gccopts} -c src.d/print.c -o obj.d/print.o
gcc ${gccopts} -c src.d/strcmp.c -o obj.d/strcmp.o
gcc ${gccopts} -c src.d/strcpy.c -o obj.d/strcpy.o
gcc ${gccopts} -c src.d/strdup.c -o obj.d/strdup.o
gcc ${gccopts} -c app.c -o app.o
gcc ${gccopts} -c app.c -E -P -C -o app.pc

#gcc ${gccopts} -shared -fPIC libmy.c -o libmy.so

nasmopts=''
nasmopts="${nasmopts} -f elf64"
nasmopts="${nasmopts} -i ${PWD}/inc.d"

nasm ${nasmopts} src.d/alloca.s -o obj.d/alloca.o
nasm ${nasmopts} src.d/atoi.s -o obj.d/atoi.o
nasm ${nasmopts} src.d/data.s -o obj.d/data.o
nasm ${nasmopts} src.d/memchr.s -o obj.d/memchr.o
nasm ${nasmopts} src.d/memcmp.s -o obj.d/memcmp.o
nasm ${nasmopts} src.d/memcpy.s -o obj.d/memcpy.o
nasm ${nasmopts} src.d/memmove.s -o obj.d/memmove.o
nasm ${nasmopts} src.d/memset.s -o obj.d/memset.o
nasm ${nasmopts} src.d/stack.s -o obj.d/stack.o
nasm ${nasmopts} src.d/start.s -o obj.d/start.o
nasm ${nasmopts} src.d/strchr.s -o obj.d/strchr.o
nasm ${nasmopts} src.d/strdupa.s -o obj.d/strdupa.o
nasm ${nasmopts} src.d/strlen.s -o obj.d/strlen.o
nasm ${nasmopts} src.d/pNx.s -o obj.d/pNx.o

nasm ${nasmopts} src.d/syscall.s -o obj.d/syscall.o

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
obj.d/brk.o \
obj.d/data.o \
obj.d/init.o \
obj.d/log10.o \
obj.d/malloc.o \
obj.d/memchr.o \
obj.d/memcmp.o \
obj.d/memcpy.o \
obj.d/memmove.o \
obj.d/memset.o \
obj.d/pNx.o \
obj.d/print.o \
obj.d/stack.o \
obj.d/strchr.o \
obj.d/strcmp.o \
obj.d/strcpy.o \
obj.d/strdup.o \
obj.d/strdupa.o \
obj.d/strlen.o \
\
obj.d/syscall.o \
\
> app.ls

export LD_LIBRARY_PATH=.
./app.exe || echo $?

exit 0

