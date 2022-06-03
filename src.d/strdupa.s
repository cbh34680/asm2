%include "defs.s"

global strdupa

extern alloca
extern strlen
extern memcpy

;
		section		.text

strdupa_1:
		; r11: save return address
		mov			r11, [rsp]

		; rsi: use at memcpy()
		mov			rsi, rdi

		; rdi: orig string
		call		strlen

		; rdx: strlen() + 1
		mov			rdx, rax
		inc			rdx

		; extend stack
		mov			rdi, rdx
		call		alloca

		; purge "call stack (return address)"
		add			rsp, 0x8

		; rdi: copy dest
		mov			rdi, rsp
		call		memcpy

		jmp			r11


strdupa_2:
		; r11: save return address
		mov			r11, [rsp]

		; rsi: use at memcpy()
		mov			rsi, rdi

		; rdi: orig string
		call		strlen

		; rdi: strlen() + 1
		mov			rdi, rax
		inc			rdi

		; extend stack
		call		alloca

		; purge "call stack (return address)"
		add			rsp, 0x8

		; rdi: copy dest
		; rdx: size
		mov			rdx, rdi
		mov			rdi, rsp
		call		memcpy

		; DEBUG
		;mov			byte [rax], '@'

		jmp			r11

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
		mov			rdx, rdi
		lea			rdi, [rsp + 0x8]
		call		memcpy

		;
		mov			rdx, [rsp]

		; DEBUG
		;mov			byte [rax], '@'

		lea			rdx, [rax - 8]
		mov			rdx, [rdx]

		; purge "call stack (return address)"
		add			rsp, 0x8

		jmp			rdx


