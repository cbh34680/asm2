set step-mode on
set confirm off
#set pagination off
set disable-randomization off
#set output-radix 16

set backtrace past-entry
set backtrace past-main
set disassembly-flavor intel

set verbose on

tui enable

#layout asm
layout src
layout regs
#layout split

# https://stackoverflow.com/questions/38803783/how-to-automatically-refresh-gdb-in-tui-mode
define hook-next
  refresh
end

#b _start
b main
run
d

