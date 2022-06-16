%include "comm.s"

global	setjmp
global	longjmp

;
		section		.text

setjmp:
		; rbx, rbp, r12, r13, r14, r15, rsp, return-address

		mov			[rdi + 0x00], rbx
		mov			[rdi + 0x08], rbp
		mov			[rdi + 0x10], r12
		mov			[rdi + 0x18], r13
		mov			[rdi + 0x20], r14
		mov			[rdi + 0x28], r15
		mov			[rdi + 0x30], rsp

		; store return-address
		mov			rax, [rsp]
		mov			[rdi + 0x38], rax

		xor			eax, eax

		ret

;
longjmp:
		mov			rax, rsi

		mov			rbx, [rdi + 0x00]
		mov			rbp, [rdi + 0x08]
		mov			r12, [rdi + 0x10]
		mov			r13, [rdi + 0x18]
		mov			r14, [rdi + 0x20]
		mov			r15, [rdi + 0x28]
		mov			rsp, [rdi + 0x30]
		mov			rsi, [rdi + 0x38]

		; for "call setjmp" return address stack
		add			rsp, 8

		jmp			rsi
;
