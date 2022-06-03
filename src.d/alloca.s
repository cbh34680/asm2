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
		; rax: aligned mask
		mov			rax, STACK_ALIGN_SIZE - 1
		not			rax

		; rdi: request size
		; rcx: aligned size
		mov			rcx, rdi
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax

		; rax: return-address
		mov			rax, [rsp]

		; purge "call stack (return-address)"
		add			rsp, 0x8

		; extend stack (aligned)
		sub			rsp, rcx

		; store return-address
		mov			[rsp], rax

		; set retval
		lea			rax, [rsp]

		jmp			[rax]

