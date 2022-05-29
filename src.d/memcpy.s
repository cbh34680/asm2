%include "defs.s"

global memcpy

;
		section		.text

;
memcpy:
		enter		0, 0

		mov			rcx, rdx
		cld

		rep movsb

		mov			rax, rdi
		sub			rax, rdx

		leave
		ret
