%include "defs.s"

global _s_memchr

;
		section		.text

_s_memchr:
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

		xor			rax, rax

.end:
		ret

