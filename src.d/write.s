%include "defs.s"

global _s_write

;
		section		.text

_s_write:
		mov			rax, SC_WRITE
		syscall
		ret
