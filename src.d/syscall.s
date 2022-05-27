%include "defs.s"

	section	.text
;
global write

write:
	mov		rax, 1
	syscall
	ret
;
global open

open:
	mov		rax, 2
	syscall
	ret
;
global close

close:
	mov		rax, 3
	syscall
	ret
;
global mmap

mmap:
	mov		rax, 9
	syscall
	ret
;
global munmap

munmap:
	mov		rax, 11
	syscall
	ret
;
global exit

exit:
	mov		rax, 60
	syscall
	ret
;
