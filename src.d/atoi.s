%include "defs.s"

global atoi

;
		section		.text

atoi:
		enter		0, 0

		push		r12
		push		r13

		xor			eax, eax
		xor			ecx, ecx

		mov			r12, 10
		xor			r13, r13

.loop:
		; get char
		mov			cl, [rdi]

		; check sign
		cmp			cl, '-'
		je			.negchk

		; check over 9
		cmp			cl, '9'
		jg			.end

		; check less 0
		sub			cl, '0'
		js			.end

		; eax *= 10, eax += ecx
		mul			r12
		add			eax, ecx

		; next loop
		inc			rdi
		jmp			.loop

.negchk:
		; check sign once
		cmp			r13, 1
		je			.end

		mov			r13, 1
		inc			rdi
		jmp			.loop

.end:
		; neg if r13=ON
		test		r13, r13
		jz			.exit

		neg			eax

.exit:
		pop			r13
		pop			r12

		leave
		ret

