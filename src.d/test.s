%include "comm.s"

;bits 64
global ua_test

;
		section		.text

ua_test:
		mov eax, -2
		cdqe

		mov rdx, 0
		mov rax, -2
		cqo

		ret

