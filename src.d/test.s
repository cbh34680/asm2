%include "comm.s"

;bits 64
global ua_test

;
		section		.text

ua_test:
		enter		0x100, 0

		mov			qword [rbp - 8], 0x2
		shl			qword [rbp - 8], 2
		add			qword [rbp - 8], 2

		cmp			qword [rbp - 8], 0

		;test		qword [rbp - 8], qword [rbp - 8]

		leave
		ret

