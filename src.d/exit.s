%include "defs.s"

global _s_exit

;
		section		.text

_s_exit:
		mov			rax, SC_EXIT
		syscall

		hlt
