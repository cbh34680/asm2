%include "defs.s"

global _a_memset

;
		section		.text

_a_memset:
		mov			rax, rsi
		mov			rcx, rdx
		cld

		rep stosb

		ret

