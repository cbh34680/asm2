%include "defs.s"

global strchr

;
		section		.text

strchr:
		enter		0, 0

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
		xor			eax, eax

.end:
		leave
		ret
