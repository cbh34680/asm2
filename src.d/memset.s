%include "defs.s"

global memset

;
		section		.text

memset:
		mov			rax, rsi
		mov			rcx, rdx
		cld

		rep stosb

		mov			rax, rdi

		ret

