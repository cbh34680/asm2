%include "defs.s"

global _s_memcpy

;
		section		.text

;
_s_memcpy:
		mov			rcx, rdx
		cld

		rep movsb

		mov			rax, rdi
		sub			rax, rdx

		ret
