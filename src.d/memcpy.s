%include "defs.s"

global _a_memcpy

;
		section		.text

;
_a_memcpy:
		mov			rcx, rdx
		cld

		rep movsb

		mov			rax, rdi
		sub			rax, rdx

		ret
