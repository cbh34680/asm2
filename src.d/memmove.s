%include "defs.s"

global _s_memmove

;
		section		.text

;
_s_memmove:
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
