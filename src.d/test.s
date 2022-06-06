%include "defs.s"

global ua_test

;
		section		.text

ua_test:
		enter		128, 0

		mov			rax, rdi

		cmp			rax, 0

		cmp			eax, 0

		leave
		ret

