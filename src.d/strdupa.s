%include "comm.s"

global strdupa

;
		section		.text

;
strdupa_1:
		xor			eax, eax

		; return NULL if strdupa(NULL)
		test		edi, edi
		jnz			.start

		ret

.start:
		; rdx: jump address
		mov			r9, [rsp]

		; backup rdi
		mov			r10, rdi

		; strlen
		mov			rcx, -1
		cld
		repne scasb
		add			rcx, 2
		neg			rcx

		; add '\0'
		inc			rcx

		; r11: strlen()+1
		mov			r11, rcx

		; purge return address
		add			rsp, 8

		; alloca
		mov			eax, STACK_ALIGN_SIZE - 1
		not			eax
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax
		sub			rsp, rcx

		; mark stack-overflow
		REDZONE_MARK

		; memcpy
		mov			rdi, rsp
		mov			rsi, r10
		mov			rcx, r11
		cld
		rep movsb

		; restore jump address
		mov			rax, rsp

		; check stack-overflow
		REDZONE_CHECK

		jmp			r9
;

strdupa:
		xor			eax, eax

		; return NULL if strdupa(NULL)
		test		edi, edi
		jnz			.start

		ret

.start:
		; rdx: return address
		mov			rdx, [rsp]

		; rsi: save arg addr (use memcpy)
		mov			rsi, rdi

		; strlen()
		mov			rcx, -1
		cld
		repne scasb
		add			rcx, 2
		neg			rcx

		; add '\0'
		inc			rcx

		; r11: strlen()+1
		mov			rdi, rcx

		; purge return address
		add			rsp, 8

		; alloca
		mov			eax, STACK_ALIGN_SIZE - 1
		not			eax
		add			rcx, STACK_ALIGN_SIZE - 1
		and			rcx, rax
		sub			rsp, rcx

		; mark stack-overflow
		REDZONE_MARK

		; memcpy
		mov			rcx, rdi
		mov			rdi, rsp
		cld
		rep movsb

		; restore jump address
		mov			rax, rsp

		; check stack-overflow
		REDZONE_CHECK

		jmp			rdx
;

