%include "defs.s"

global memcpy

;
		section		.text

;
memcpy:
		mov			rcx, rdx
		cld

		rep movsb

		mov			rax, rdi
		sub			rax, rdx

		ret
