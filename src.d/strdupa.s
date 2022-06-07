%include "comm.s"

global strdupa

extern alloca
extern strlen
extern memcpy

;
		section		.text

strdupa:
		; rsi: use at memcpy()
		mov			rsi, rdi

		; rdi: orig string
		call		strlen

		; rdi: strlen() + 1
		mov			rdi, rax
		inc			rdi

		; rdx: save return address
		mov			rdx, [rsp]

		; extend stack
		call		alloca

		; store return address
		mov			[rsp], rdx		

		; rdi: copy dest
		; rdx: size
		lea			rdx, [rsp + 0x8]
		xchg		rdx, rdi
		call		memcpy

		; load return address
		mov			rdx, [rsp]

		; purge "call stack (return address)"
		add			rsp, 0x8

		jmp			rdx

