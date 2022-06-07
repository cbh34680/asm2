%include "comm.s"

global	_start

extern	uc_init

;
		section		.text

_start:
		; argc, argv, envp
		mov			rdi, [rsp]
		lea			rsi, rsp[8]
		lea			rdx, rsp[8 + rdi * 8 + 8]

		; push guard (back trace)
		push		0x0

		; make frame
		push		rsp
		mov			rbp, rsp

		xor			eax, eax
		call		uc_init

		mov			rdi, rax
		call		syscall_exit

