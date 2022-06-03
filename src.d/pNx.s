%include "defs.s"

global ua_pgx
global ua_pwx
global ua_phx

;
		section		.text

;
ua_pgx:
		mov			rcx, 15
		call		ua_pNx
		ret

;
ua_pwx:
		mov			rcx, 7
		call		ua_pNx
		ret

;
ua_phx:
		mov			rcx, 3
		call		ua_pNx
		ret

;
ua_pNx:
		enter		0, 0

		push		r12
		push		r13

		lea			r13, [rdi + rcx]

		; out-buf[N + 1] = '\0'
		mov			byte [r13 + 1], 0x0

.loop:
		mov			r12, rsi

		; get last 8bit
		and			r12, 0xf

		; convert to char
		mov			al, _HEXCHARS[r12]

		; write to out-pos
		mov			byte [r13], al

		; check range
		cmp			r13, rdi
		je			.end

		; shift 4bit
		shr			rsi, 4

		; set out-pos + 1
		dec			r13

		jmp			.loop

.end:
		pop			r13
		pop			r12
		mov			rax, rdi

		leave
		ret

