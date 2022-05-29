%include "defs.s"

global atoi

;
		section		.text

atoi:
		enter		0, 0

		push		r12

		xor			eax, eax
		xor			ecx, ecx

		mov			r12, 10

.loop:
		mov			cl, [rdi]

		cmp			cl, '0'
		jl			.end

		cmp			cl, '9'
		jg			.end

		sub			cl, '0'

		mul			r12
		add			eax, ecx

		inc			rdi
		jmp			.loop

.end:
		pop			r12

		leave
		ret

