%include "defs.s"

%define ON			1

global ua_itoa
extern _HEXCHARS

;
		section		.text

ua_itoa:
		enter		16, 0

		; backup
		push		rbx
		push		r12

		; flags
		xor			ebx, ebx

		; input value
		mov			eax, edi

		; output buffer
		lea			r12, [rbp - 16]
		mov			byte [r12], 0x0

		; for div
		mov			edi, 10

		; 4294967295
		; 1000000000
		; max loop count
		mov			rcx, 10

		; check eax <0
		cmp			eax, 0
		jns			.loop

		; eax *= -1
		neg			eax

		; set neg-flag ON
		mov			bh, ON

.loop:
		; change write position
		dec			r12

		; eax = eax / edi
		; edx = eax % edi
		cdq
		idiv		edi

		; write '0' - '9'
		mov			bl, _HEXCHARS[edx]
		mov			[r12], bl

		; check input >0
		test		eax, eax
		loopnz		.loop

		; prepare memcpy (dest)
		mov			rdi, rsi

		; check neg-flag
		test		bh, bh
		jz			.copy

		; neg-flag is ON
		; --> write '-' to dest[0]
		mov			byte [rdi], '-'
		inc			rdi

.copy:
		; prepare memcpy (size)
		sub			rcx, 10
		neg			rcx
		inc			rcx

		; prepare memcpy (src)
		mov			rax, rsi
		mov			rsi, r12

		; do memcpy
		cld
		rep movsb

		pop			r12
		pop			rbx
		leave
		ret

