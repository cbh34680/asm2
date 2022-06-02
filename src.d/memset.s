%include "defs.s"

global memset

;
		section		.text

memset:
		;enter		0, 0

		mov			rax, rsi
		mov			rcx, rdx
		cld

		; save return address
		;lea			rsi, [rdi]
		mov			rsi, rdi

		rep stosb

		mov			rax, rsi

		;leave
		ret

