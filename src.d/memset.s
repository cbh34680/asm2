%include "defs.s"

global _s_memset

;
		section		.text

_s_memset:
		mov			rax, rsi
		mov			rcx, rdx
		cld

		rep stosb

		ret

