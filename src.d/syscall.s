%include "defs.s"

; ausyscall --exact open
%define SC_write        1
%define SC_open         2
%define SC_close        3
%define SC_exit         60

global _s_write
global _s_open
global _s_close
global _s_exit

;
		section		.text

;
_s_write:
		mov			rax, SC_write
		syscall
		ret

_s_open:
		mov			rax, SC_open
		syscall
		ret

_s_close:
		mov			rax, SC_close
		syscall
		ret

_s_exit:
		mov			rax, SC_exit
		syscall
		ret

