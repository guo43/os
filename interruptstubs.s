
.section .text

.extern _ZN16InterruptManager15handleInterruptEhj

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26handleInterruptRequest\num\()Ev


int_bottom:
	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %esp
	push (interruptnumber)
	call _ZN16InterruptManager15handleInterruptEhj

	# addl %5, %esp
	movl %eax, %esp


	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

	iret


.data:
	interruptnumber: .byte 0