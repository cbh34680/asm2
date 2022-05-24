%include "defs.s"

global _s_strchr

;
		section		.text

_s_strchr:
		lea			rax, [rdi]
		mov			rcx, rsi

.loop:
		cmp			byte [rax], 0x0
		je			.notf

		cmp			byte [rax], cl
		je			.end

		inc			rax
		jmp			.loop

.notf:
		xor			rax, rax

.end:
		ret
