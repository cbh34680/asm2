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


strdupa:
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


