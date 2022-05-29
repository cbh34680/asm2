%include "defs.s"

global	_start

extern	_c_init
extern	exit

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
		call		_c_init

		mov			rdi, rax
		call		exit

