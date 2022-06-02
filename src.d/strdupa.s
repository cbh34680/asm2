%include "defs.s"

global strdupa

extern alloca
extern strlen
extern memcpy

;
		section		.text

strdupa:
		; r11: save current stack
		mov			r11, rsp

		; rsi: use at memcpy
		mov			rsi, rdi

		; rdi: orig string
		call		strlen
		inc			rax

		; extend stack
		mov			rdi, rax
		call		alloca

		; purge "call stack (return address)"
		add			rsp, 0x8

		; purge "call stack (return address)"
		mov			rax, r11
		add			rax, 0x8

		jmp			[r11]

