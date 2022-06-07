%include "comm.s"

global ua_pgx
global ua_pwx
global ua_phx
global ua_pbx

;
		section		.text

;
; INPUT: 1byte(0xff) --> OUTPUT: charX2("ff")
;

; long (8byte)
ua_pgx:
		mov			rcx, 16
		call		ua_pNx
		ret

; int (4byte)
ua_pwx:
		mov			rcx, 8
		call		ua_pNx
		ret

; short (2byte)
ua_phx:
		mov			rcx, 4
		call		ua_pNx
		ret

; char (1byte)
ua_pbx:
		mov			rcx, 2
		call		ua_pNx
		ret

;
ua_pNx_:
		push		rbx

		; rbx = &outbuf[N] (0 origin)
		lea			rbx, [rdi + rcx]

		; outbuf[N + 1] = '\0'
		mov			byte [rbx], 0x0

.loop:
		; rax: input
		mov			rax, rsi

		; last 8bit
		and			eax, 0xf

		; load char
		mov			al, _HEXCHARS[rax]

		; outpos--
		dec			rbx

		; store
		mov			byte [rbx], al

		; rax: input = input >> 4
		shr			rsi, 4

		; repeat rcx times
		loop		.loop

.end:
		mov			rax, rdi

		pop			rbx
		ret

;
ua_pNx:
		enter		0x20, 0

		; backup
		push		rbx

		; mark stack-overflow
		REDZONE_MARK

		; rbx = &outbuf[N] (0 origin)
		lea			rbx, [rbp - 1]

		; outbuf[N + 1] = '\0'
		mov			byte [rbx], 0x0

.loop:
		; outpos--
		dec			rbx

		; rax: input
		mov			rax, rsi

		; last 8bit
		and			eax, 0xf

		; load char
		mov			al, _HEXCHARS[rax]

		; store
		mov			[rbx], al

		; rax: input = input >> 4
		shr			rsi, 4

		; repeat (max)rcx times
		loopnz		.loop

.copy:
		; save addr
		mov			rax, rdi

		; prepare memcpy (src)
		mov			rsi, rbx

		; prepare memcpy (size)
		mov			rcx, rbp
		sub			rcx, rbx

		; do memcpy
		cld
		rep movsb

		; check stack-overflow
		REDZONE_CHECK

		pop			rbx

		leave
		ret

