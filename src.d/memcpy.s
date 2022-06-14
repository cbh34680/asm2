%include "comm.s"

global memcpy

;
		section		.text

;
memcpy:
		mov			rcx, rdx

		cld
		rep movsb

		; rax: rdi - rdx
		;
		; lea rax, [rdi - rdx] ... NG Why?
		;
		mov			rax, rdi
		sub			rax, rdx

		ret
