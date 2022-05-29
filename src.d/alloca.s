%include "defs.s"

%define ALIGN_SIZE	0x10

global alloca
global ua_getstack

;
		section		.text

; aligned-size = (request-size + (ALIGN_SIZE - 1)) & ~(ALIGN_SIZE - 1);

alloca:
		; immediate ver
		;mov			rax, rdi
		;add			rax, 0x7
		;and			rax, 0xfffffffffffffff8

		; rdi: request size
		; rax: alligned size
		mov			rax, rdi
		add			rax, ALIGN_SIZE - 1
		mov			rcx, ALIGN_SIZE - 1
		not			rcx
		and			rax, rcx

		; purge "call stack (return address)"
		add			rsp, 0x8

		; extend stack
		mov			rcx, rsp
		sub			rcx, rax
		xchg		rcx, rsp

		; !! DEBUG !!
		mov			byte [rsp], 0xcc
		mov			byte [rcx - 0x9], 0xbb

		; set ret-val
		mov			rax, rsp

		jmp			[rcx - 0x8]

ua_getstack:
		mov			rax, rsp
		add			rax, 0x8

		ret

