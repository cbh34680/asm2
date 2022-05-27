%include "defs.s"

global _a_xgx
global _a_xwx
global _a_xhx

;
		section		.text

;
_a_xgx:
		mov			rcx, 15
		call		_a_xNx
		ret

;
_a_xwx:
		mov			rcx, 7
		call		_a_xNx
		ret

;
_a_xhx:
		mov			rcx, 3
		call		_a_xNx
		ret

;
_a_xNx:
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

