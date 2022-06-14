%include "comm.s"

global	ua_getsp
global	ua_getip
global	ua_bt_caller

;
ua_getsp:
		mov			rax, rsp
		add			rax, 0x8

		ret

;
ua_getip:
		mov			rax, [rsp]
		ret

;
ua_bt_caller:
		enter		0, 0		; need make-frame

		mov			ecx, edi
		inc			ecx

		mov			rdi, rbp

.loop:
		; load return-address
		mov			rax, [rdi + 8]

		; rdi: upper frame bp
		mov			rdi, [rdi]

		; check guard (push zero at [start.s])
		test		rax, rax
		loopne		.loop

		test		rsi, rsi
		jz			.end

		; store bp
		mov			[rsi], rdi

.end:
		leave
		ret

; EOF

