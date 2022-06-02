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

alloca_1:
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

alloca_2:
		; rax: aligned mask
		mov			rax, STACK_ALIGN_SIZE - 1
		not			rax

		; rdi: request size --> aligned size
		add			rdi, STACK_ALIGN_SIZE - 1
		and			rdi, rax

		; purge "call stack (return address)"
		add			rsp, 0x8

		; extend stack (aligned)
		mov			rax, rsp
		sub			rax, rdi
		xchg		rax, rsp

		; !! DEBUG !!
		;mov			byte [rsp], 0xcc
		;mov			byte [rax - 0x9], 0xbb

		jmp			[rax - 0x8]

alloca:
		; rax: aligned mask
		mov			rax, STACK_ALIGN_SIZE - 1
		not			rax

		; rdi: request size --> aligned size
		mov			rcx, rdi
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax

		; purge "call stack (return address)"
		add			rsp, 0x8

		; extend stack (aligned)
		mov			rax, rsp
		sub			rax, rcx
		xchg		rax, rsp

		; !! DEBUG !!
		;mov			byte [rsp], 0xcc
		;mov			byte [rax - 0x9], 0xbb

		jmp			[rax - 0x8]

