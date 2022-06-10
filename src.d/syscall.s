%include "defs.s"

	section	.text
;
global syscall_read

syscall_read:
	mov		eax, 0
	syscall
	ret
;
global syscall_write

syscall_write:
	mov		eax, 1
	syscall
	ret
;
global syscall_open

syscall_open:
	mov		eax, 2
	syscall
	ret
;
global syscall_close

syscall_close:
	mov		eax, 3
	syscall
	ret
;
global syscall_brk

syscall_brk:
	mov		eax, 12
	syscall
	ret
;
global syscall_exit

syscall_exit:
	mov		eax, 60
	syscall
	ret
;
global syscall_time

syscall_time:
	mov		eax, 201
	syscall
	ret
;
