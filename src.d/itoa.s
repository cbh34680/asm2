%include "comm.s"

global ua_itoa
extern _HEXCHARS

;
		section		.text

ua_itoa:
		enter		0x10, 0

		; backup
		push		rbx

		; mark stack-overflow
		REDZONE_MARK

		; ch: neg-flag
		; cl: temp char
		xor			ecx, ecx

		; input value
		mov			eax, edi

		; output buffer
		lea			rbx, [rbp - 1]
		mov			byte [rbx], 0x0

		; for div
		mov			edi, 10

		; check eax <0
		cmp			eax, 0
		jns			.loop

		; eax *= -1
		neg			eax

		; set neg-flag ON
		mov			ch, ON

.loop:
		; change write position
		dec			rbx

		; eax = eax / edi
		; edx = eax % edi
		;
		; cdq: segfault if eax=-2147483648
		cqo
		div			edi

		; write '0' - '9'
		mov			cl, _HEXCHARS[rdx]
		mov			[rbx], cl

		; check input >0
		test		eax, eax
		jnz			.loop

		; prepare memcpy (dest)
		mov			rdi, rsi

		; check neg-flag
		test		ch, ch
		jz			.copy

		; neg-flag is ON
		; --> write '-' to dest[0]
		mov			byte [rdi], '-'
		inc			rdi

.copy:
		; save addr
		mov			rax, rsi

		; prepare memcpy (src)
		mov			rsi, rbx

		; prepare memcpy (size)
		mov			rcx, rbp
		sub			rcx, rsi

		; do memcpy
		cld
		rep movsb

		; check stack-overflow
		REDZONE_CHECK

		pop			rbx
		leave
		ret

