%include "comm.s"

;%define ALIGN_SIZE	0x10

global alloca

;
		section		.text

; aligned-size = (request-size + (ALIGN_SIZE - 1)) & ~(ALIGN_SIZE - 1);

alloca:
		; ret if alloc(0)
		test		edi, edi
		jnz			.start

		lea			rax, [rsp + 8]
		ret

.start:
		; rax: aligned mask
		mov			eax, STACK_ALIGN_SIZE - 1
		not			eax

		; rdi: request size
		; rcx: aligned size
		mov			rcx, rdi
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax

		; rdi: jump address
		mov			rdi, [rsp]

		; purge "call stack (return-address)"
		add			rsp, 0x8

		; extend stack (aligned)
		sub			rsp, rcx

		mov			rax, rsp

		; for DEBUG
		REDZONE_MARK

		jmp			rdi

