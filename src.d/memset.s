%include "defs.s"

global memset

;
		section		.text

memset:
		enter		0, 0

		mov			rax, rsi
		mov			rcx, rdx
		cld

		rep stosb

		mov			rax, rdi

		leave
		ret

