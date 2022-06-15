%include "comm.s"

global	ua_ltoa
global	ua_ultoa

;
		section		.text

ua_ltoa:
		xor			edx, edx
		call		_ua_ltoa
		ret

ua_ultoa:
		mov			edx, ON
		call		_ua_ltoa
		ret

_ua_ltoa:
		enter		32, 0

		; backup
		push		rbx

		; mark stack-overflow
		REDZONE_MARK

		; ch: neg-flag
		; cl: temp char
		xor			ecx, ecx

		; input value
		mov			rax, rdi

		; output buffer
		lea			rbx, [rbp - 1]
		mov			byte [rbx], 0x0

		; for div
		mov			edi, 10

		; check unsigned-flag
		test		edx, edx
		jnz			.loop

		; check rax <0
		cmp			rax, 0
		jns			.loop

		; rax *= -1
		neg			rax

		; set neg-flag ON
		mov			ch, ON

.loop:
		; change write position
		dec			rbx

		; rax = rax / rdi
		; rdx = rax % rdi
		xor			edx, edx
		div			rdi

		; write '0' - '9'
		mov			cl, _HEXCHARS[edx]
		mov			[rbx], cl

		; check input >0
		test		rax, rax
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

