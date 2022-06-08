%include "comm.s"

;%define ALIGN_SIZE	0x10

global alloca

;
		section		.text

; aligned-size = (request-size + (ALIGN_SIZE - 1)) & ~(ALIGN_SIZE - 1);

alloca_1:
		; rax: aligned mask
		mov			rax, STACK_ALIGN_SIZE - 1
		not			rax

		; rdi: request size
		; rcx: aligned size
		mov			rcx, rdi
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax

		; purge "call stack (return-address)"
		add			rsp, 0x8

		; rax: return-address
		lea			rax, [rsp]

		; extend stack (aligned)
		sub			rsp, rcx

		; for DEBUG
		REDZONE_MARK

		jmp			[rax - 0x8]

alloca:
		; save rcx
		push		rcx

		; rax: aligned mask
		mov			rax, STACK_ALIGN_SIZE - 1
		not			rax

		; rdi: request size
		; rcx: aligned size
		mov			rcx, rdi
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax

		; purge "call stack (return-address)"
		add			rsp, 0x10

		; rax: return-address
		lea			rax, [rsp]

		; extend stack (aligned)
		sub			rsp, rcx

		; restore rcx
		mov			rcx, [rax - 0x10]

		; for DEBUG
		REDZONE_MARK

		jmp			[rax - 0x8]


