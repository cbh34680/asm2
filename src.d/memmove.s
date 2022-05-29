%include "defs.s"

global memmove

;
		section		.text

;
memmove:
		add			rdi, rdx
		dec			rdi

		test		rdx, rdx
		jz			.end

		add			rsi, rdx
		dec			rsi
		mov			rcx, rdx
		std

		rep movsb

.end:
		mov			rax, rdi
		inc			rax

		ret
