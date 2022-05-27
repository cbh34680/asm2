%include "defs.s"

	section	.text
;
%define SC_write 1
global _s_write

_s_write:
	mov		rax, SC_write
	syscall
	ret
;
%define SC_open 2
global _s_open

_s_open:
	mov		rax, SC_open
	syscall
	ret
;
%define SC_close 3
global _s_close

_s_close:
	mov		rax, SC_close
	syscall
	ret
;
%define SC_exit 60
global _s_exit

_s_exit:
	mov		rax, SC_exit
	syscall
	ret
;
