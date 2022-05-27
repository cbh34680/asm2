%include "defs.s"

global _a_memmove

;
		section		.text

;
_a_memmove:
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
