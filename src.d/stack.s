%include "comm.s"

global	__stack_chk_fail
global	ua_getsp
global	ua_bt_caller
global	uc_fill_redzone

;
		section		.data

_STACK_CHKFAIL_MSG		db	'Stack Check Abort', 10, 0
_STACK_CHKFAIL_MSGLEN	equ	$ - _STACK_CHKFAIL_MSG

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
		test		rax, rax
		loopne		.loop

		test		rsi, rsi
		jz			.end

		; store bp
		mov			[rsi], rdi

.end:
		leave
		ret


;
; -fstack-protector ... but not work
;
__stack_chk_fail:
		mov			rdi, FD_STDERR
		mov			rsi, _STACK_CHKFAIL_MSG
		mov			rdx, _STACK_CHKFAIL_MSGLEN
		mov			eax, 1
		syscall

		mov			rdi, 0x40
		mov			eax, 60
		syscall

		ret

;
uc_fill_redzone:
		mov			r11, [rsp]

		mov			rax, rsp
		add			rsp, 120

.loop:
		mov			byte [rsp], '.'
		dec			rsp

		cmp			rsp, [rax + 8]
		jne			.loop

		jmp			r11

; EOF

