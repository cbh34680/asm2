%include "comm.s"

extern	memcpy
global	memmove

;
		section		.text

;
memmove:
		; copy-size is zero
		test		rdx, rdx
		jz			.end

		; src < dst
		cmp			rdi, rsi
		jg			.main

		; src == dst
		je			.end


		; dst < src
		call		memcpy
		ret

.main:
		lea			rdi, rdi[rdx - 1]
		lea			rsi, rsi[rdx - 1]
		mov			rcx, rdx

		std
		rep movsb
		inc			rdi

.end:
		mov			rax, rdi

		ret
