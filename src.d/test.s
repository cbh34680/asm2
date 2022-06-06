%include "defs.s"

;bits 64
global ua_test

;
		section		.text

ua_test:
		enter		128, 0
		;push		rbp
		;mov			rbp, rsp
		;sub			rsp, 0x20

		mov			qword [rbp - 8], 0x0abcdef012345678
		mov			rax, qword [rbp - 8]


		leave
		ret

