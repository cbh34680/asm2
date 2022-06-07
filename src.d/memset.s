%include "comm.s"

global memset

;
		section		.text

memset:
		mov			rax, rsi
		mov			rcx, rdx
		cld

		; save return address
		mov			rsi, rdi

		rep stosb

		mov			rax, rsi

		ret

