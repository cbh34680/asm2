%include "comm.s"

global memcmp

;
		section		.text

memcmp:
		enter		0, 0

		xor			eax, eax

		mov			rcx, rdx
		cld
		repe cmpsb

		; same data
		jz			.end

		; check last char
		mov			cl, [rdi - 1]
		cmp			cl, [rsi - 1]
		js			.lt

							; ">" +1
		inc			eax
		jmp			.end

.lt:
							; "<" -1
		dec			eax
		jmp			.end

.end:
		leave
		ret

