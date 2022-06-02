%include "defs.s"

global strlen

;
		section		.text

strlen_1:
		xor			ecx, ecx

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
; http://hp.vector.co.jp/authors/VA014520/asmhsp/chap6.html
;
strlen:
		;enter		0, 0


		;mov			al, 0x0 ; '\0'
		xor			eax, eax

		mov			rcx, -1

		cld
		repne		scasb

		mov			rax, rcx
		add			rax, 2
		neg			rax

		;leave
		ret

