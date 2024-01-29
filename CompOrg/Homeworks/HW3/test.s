
		.data
msg:	.asciiz "Hello world"
	
	
		.text
main:	li $v0, 4
		la $a0, msg
		syscall
		
		jr $ra