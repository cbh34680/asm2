%include "defs.s"

global	ua_mark_redzone

		section		.text

;
ua_mark_redzone:
		mov			r11, [rsp]

		mov			rax, rsp
		add			rsp, 24

.loop:
		mov			byte [rsp], '.'
		dec			rsp

		cmp			rsp, [rax + 8]
		jne			.loop

		jmp			r11

; EOF

