%include "defs.s"

;%define ALIGN_SIZE	0x10

global ua_getstack
global alloca

;
		section		.text

ua_getstack:
		mov			rax, rsp
		add			rax, 0x8

		ret

; aligned-size = (request-size + (ALIGN_SIZE - 1)) & ~(ALIGN_SIZE - 1);

alloca:
		; rcx: aligned mask
		mov			rcx, STACK_ALIGN_SIZE - 1
		not			rcx

		; rdi: request size
		; rax: aligned size
		mov			rax, rdi
		add			rax, STACK_ALIGN_SIZE - 1
		and			rax, rcx

		; purge "call stack (return address)"
		add			rsp, 0x8

		; extend stack (aligned)
		mov			rcx, rsp
		sub			rcx, rax
		xchg		rcx, rsp

		; !! DEBUG !!
		;mov			byte [rsp], 0xcc
		;mov			byte [rcx - 0x9], 0xbb

		; set ret-val
		mov			rax, rsp

		jmp			[rcx - 0x8]

