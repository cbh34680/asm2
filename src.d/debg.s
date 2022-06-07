%include "defs.s"
%include "sysc.s"

global	__stack_chk_fail
global	ua_mark_redzone

;
		section		.data

_STACK_CHKFAIL_MSG		db	'Stack Check Abort', 10, 0
_STACK_CHKFAIL_MSGLEN	equ	$ - _STACK_CHKFAIL_MSG

;
		section		.text

ua_mark_redzone:
		; 24 + sizeof(return address) => '.' X 32
		; [rsp - 1] ... [rsp - 32]
		sub			rsp, 24

		; save return address
		push		rdi
		mov			rdi, [rsp + 32]

		; save registers
		push		rdi
		push		rax
		push		rcx

		; do memset
		lea			rdi, [rsp + 32]
		mov			al, '.'
		mov			rcx, 32
		cld
		rep stosb

		; restore registers
		mov			rsp, rdi
		mov			rdi, [rsp - 40]
		mov			rax, [rsp - 56]
		mov			rcx, [rsp - 64]

		; return caller
		jmp			[rsp - 48]


;
; -fstack-protector ... but not work
;
__stack_chk_fail:
		mov			rdi, FD_STDERR
		mov			rsi, _STACK_CHKFAIL_MSG
		mov			rdx, _STACK_CHKFAIL_MSGLEN
		;mov			eax, 1
		;syscall
		call		syscall_write

		mov			rdi, 0x40
		;mov			eax, 60
		;syscall
		call		syscall_exit

		ret

; EOF

