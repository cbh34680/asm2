%include "defs.s"

global strlen

;
		section		.text

strlen_1:
		xor			rcx, rcx

		lea			rax, [rdi]

.loop:
		cmp			byte [rax], 0x0
		je			.end
		inc			rax
		jmp			.loop

.end:
		sub			rax, rdi

		ret

;
strlen:
		; http://hp.vector.co.jp/authors/VA014520/asmhsp/chap6.html

		mov			al, 0x0
		mov			rcx, -1

		cld
		repne		scasb
		mov			rax, rcx

		add			rax, 2
		neg			rax

		ret
