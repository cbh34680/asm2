%include "defs.s"

global	_start

extern	_s_exit
extern	_c_init

;
		section		.text

_start:
		mov			rdi, [rsp]
		lea			rsi, rsp[8]
		lea			rdx, rsp[8 + rdi * 8 + 8]

		push		rsp
		mov			rbp, rsp

		xor			rax, rax
		call		_c_init

		mov			rdi, rax
		call		_s_exit

		hlt

