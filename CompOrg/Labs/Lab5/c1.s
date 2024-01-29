		.data
msg1:	.asciiz "EVEN\n"
		
		.data
msg2:	.asciiz "ODD\n"

       .text
main:  .globl main
	   li $v0, 1
	   li $a0, 31
       li $t0, 2


       div $t1, $a0, $t0
       mult $t1, $t0
       mflo $t1


       li $v0, 4
       beq $a0, $t1, even
       j odd


even:  la $a0, msg1     
	   j end

odd:   la $a0, msg2   
	   j end

end:   syscall
	   jr $ra