%include "comm.s"

%define ON			1

global atoi

;
		section		.text

atoi:
		enter		0, 0

		push		rbx
		push		r10

		xor			eax, eax
		xor			ebx, ebx
		xor			ecx, ecx

		mov			r10, 10

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
		mul			r10
		add			eax, ecx

		; next loop
		inc			rdi
		jmp			.loop

.negchk:
		; check sign once
		cmp			ebx, ON
		je			.end

		; first neg sign
		mov			ebx, ON
		inc			rdi
		jmp			.loop

.end:
		; neg if ebx=ON
		test		ebx, ebx
		jz			.exit

		neg			eax

.exit:
		pop			r10
		pop			rbx

		leave
		ret

