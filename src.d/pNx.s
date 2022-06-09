%include "comm.s"

global	ua_pgx
global	ua_pwx
global	ua_phx
global	ua_pbx

global	ua_pgx0
global	ua_pwx0
global	ua_phx0
global	ua_pbx0

;
		section		.text

;
; INPUT: 1byte(0xff) --> OUTPUT: charX2("ff")
;

; long (8byte)
ua_pgx:
		xor			eax, eax
		mov			ecx, 16
		call		ua_pNx
		ret

; int (4byte)
ua_pwx:
		xor			eax, eax
		mov			ecx, 8
		call		ua_pNx
		ret

; short (2byte)
ua_phx:
		xor			eax, eax
		mov			ecx, 4
		call		ua_pNx
		ret

; char (1byte)
ua_pbx:
		xor			eax, eax
		mov			ecx, 2
		call		ua_pNx
		ret

; ----------------- zero padding

; long (8byte)
ua_pgx0:
		mov			eax, ON
		mov			ecx, 16
		call		ua_pNx
		ret

; int (4byte)
ua_pwx0:
		mov			eax, ON
		mov			ecx, 8
		call		ua_pNx
		ret

; short (2byte)
ua_phx0:
		mov			eax, ON
		mov			ecx, 4
		call		ua_pNx
		ret

; char (1byte)
ua_pbx0:
		mov			eax, ON
		mov			ecx, 2
		call		ua_pNx
		ret

; ----------------- main
;
ua_pNx:
		;  -1, -23 ... make string
		; -24, -27 ... zero-flag
		enter		32, 0

		; backup
		push		rbx

		; mark stack-overflow
		REDZONE_MARK

		; save zero-flag
		mov			[rbp - 24], eax

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

		; check zero-flag
		mov			eax, [rbp - 24]
		test		eax, eax
		jz			.nopad

		; zero-padding
		loop		.loop

.nopad:
		; repeat (max)ecx times
		test		rsi, rsi
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

