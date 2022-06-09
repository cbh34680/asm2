%include "comm.s"

;bits 64
global ua_test

;
		section		.text

_ua_test:
		;mov			eax, -11
.loop1:
		;mov			ebx, 10
		;mov			edx, 0
		;div			ebx
		;test		eax, eax
		;jnz			.loop1
		;call		ua_test.clear

		mov			eax, -11
.loop2:
		mov			ebx, 10
		cdq
		idiv		ebx
		test		eax, eax
		jnz			.loop2

		ret

ua_test:
		enter		0x1000, 0
		push		rax
		push		rbx
		push		rcx
		push		rdx
		push		rdi
		push		rsi
		push		r12
		push		r13
		push		r14
		push		r15

		call		.clear
		;

		call		_ua_test

		;
		pop			r15
		pop			r14
		pop			r13
		pop			r12
		pop			rsi
		pop			rdi
		pop			rdx
		pop			rcx
		pop			rbx
		pop			rax
		leave
		ret

.clear:
		xor			rax, rax
		xor			rbx, rbx
		xor			rcx, rcx
		xor			rdx, rdx
		xor			rdi, rdi
		xor			rsi, rsi
		xor			r12, r12
		xor			r13, r13
		xor			r14, r14
		xor			r15, r15

		ret

