%include "defs.s"

global	_start

extern	uc_init
extern	syscall_exit

;
		section		.text

_start:
		; argc, argv, envp
		mov			rdi, [rsp]
		lea			rsi, rsp[8]
		lea			rdx, rsp[8 + rdi * 8 + 8]

		push		rsp
		mov			rbp, rsp

		xor			eax, eax
		call		uc_init

		mov			rdi, rax
		call		syscall_exit

