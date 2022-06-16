%include "comm.s"

global	ua_pgb
global	ua_pwb
global	ua_phb
global	ua_pbb

global	ua_pgb0
global	ua_pwb0
global	ua_phb0
global	ua_pbb0

;
		section		.text

;
; INPUT: 1byte(0xff) --> OUTPUT: charX8("0b11111111")
;

; long (8byte)
ua_pgb:
		xor			eax, eax
		mov			ecx, 64
		call		ua_pNb
		ret

; int (4byte)
ua_pwb:
		xor			eax, eax
		mov			ecx, 32
		call		ua_pNb
		ret

; short (2byte)
ua_phb:
		xor			eax, eax
		mov			ecx, 16
		call		ua_pNb
		ret

; char (1byte)
ua_pbb:
		xor			eax, eax
		mov			ecx, 8
		call		ua_pNb
		ret

; ----------------- zero padding

; long (8byte)
ua_pgb0:
		mov			eax, ON
		mov			ecx, 64
		call		ua_pNb
		ret

; int (4byte)
ua_pwb0:
		mov			eax, ON
		mov			ecx, 32
		call		ua_pNb
		ret

; short (2byte)
ua_phb0:
		mov			eax, ON
		mov			ecx, 16
		call		ua_pNb
		ret

; char (1byte)
ua_pbb0:
		mov			eax, ON
		mov			ecx, 8
		call		ua_pNb
		ret

; ----------------- main
;
ua_pNb:
		; -96, -92 ... -----------
		; -92, -88 ... arg ecx
		; -88, -84 ... zero-flag
		; -84,   0 ... make string (64 + 15 + 1 = max 80)
		enter		96, 0

		; mark stack-overflow
		REDZONE_MARK

		; save zero-flag
		mov			[rbp - 88], eax

		; rdx = &outbuf[N] (0 origin)
		lea			rdx, [rbp - 1]

		; outbuf[N + 1] = '\0'
		mov			byte [rdx], 0x0

		; save original ecx
		mov			dword [rbp - 92], ecx
		jmp			.nosep

.loop:
		; separate every 4 byte
		mov			eax, [rbp - 92]
		sub			eax, ecx
		and			eax, 0x3
		jnz			.nosep

		dec			rdx
		mov			al, ' '
		mov			[rdx], al
.nosep:

		; outpos--
		dec			rdx

		; rax: input
		mov			rax, rsi

		; last 8bit
		and			eax, 0x1

		; load char
		mov			al, _HEXCHARS[eax]

		; store
		mov			[rdx], al

		; rsi: input = input >> 4
		shr			rsi, 1

		; check zero-flag
		cmp			dword [rbp - 88], 0
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
		mov			rsi, rdx

		; prepare memcpy (size)
		mov			rcx, rbp
		sub			rcx, rdx

		; do memcpy
		cld
		rep movsb

		; check stack-overflow
		REDZONE_CHECK

		leave
		ret

