%include "defs.s"

global memchr

;
		section		.text

memchr:
		enter		0, 0

		mov			rax, rsi
		mov			rcx, rdx
		cld

		repne scasb
		jnz			.notf

		; found
		lea			rax, [rdi - 1]

		jmp			.end
.notf:
		; not found

		xor			eax, eax

.end:
		leave
		ret

