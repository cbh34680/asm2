%include "defs.s"

global	ua_getsp
global	ua_bt_caller

;
		section		.text

;
ua_getsp:
		mov			rax, rsp
		add			rax, 0x8

		ret

ua_bt_caller:
		enter		0, 0

		mov			ecx, edi
		inc			ecx

		mov			rdi, rbp

.loop:
		; load return-address
		mov			rax, [rdi + 8]

		; rdi: upper frame bp
		mov			rdi, [rdi]

		; check guard (push zero at [start.s])
		;test		rax, rax
		;loopne		.loop

		loop		.loop

		; first sp:
		;mov			xxx, rdi + 16

		leave
		ret

