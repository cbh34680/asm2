set step-mode on
set confirm off
#set pagination off
set disable-randomization off
#set output-radix 16

set host-charset UTF-8
set charset UTF-8
set target-charset UTF-8
set target-wide-charset UTF-8

#set style enabled off

set backtrace past-entry
set backtrace past-main
set disassembly-flavor intel

set verbose on

tui enable

layout asm
#layout src
layout regs
#layout split

# https://stackoverflow.com/questions/38803783/how-to-automatically-refresh-gdb-in-tui-mode
define hook-next
  refresh
end

define hook-step
  refresh
end

define hook-run
  refresh
end

define hook-continue
  refresh
end

b _start
#b main
#b ua_test

run
d

