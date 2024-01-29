	.data
list: 
	.word 12, 100, 102, 5, 123456879, 18

	.text
main:
	.globl main
	li $v0, 1 


	la $t0, list #load list address
	li $t1, 0 #loop counter
	li $t2, 0 #odd counter
	li $t3, 6 #number of elements
	li $t4, 2 #the number '2'


	loop:

	lw $a0, 0($t0) #load value from list address
	addi $t0, $t0, 4 #increment address
	addi $t1, $t1, 1 #increment loop counter
	#divide by 2, then multiply by 2
	div $t5, $a0, $t4
	mult $t5, $t4
	mflo $t5
	beq $t5, $a0, skip #if even, skip the next block
	addi $t2, $t2, 1 #increment odd counter
	skip:
	beq $t3, $t1, end #jump to end if loop counter == number of elements

	j loop


	end:
	#print number of odds (for fun)
	li $a0, 0
	ori $a0, $t2, 0
	syscall
	jr $ra

#NOTE
#for some reason, print_all_regs will always display register v0 as containing a value of 10.
#for this reason, i am storing my output in t2. i'm also using a different register for word size
#because i felt like it. this note is here to remind me in case a TA asks about it, which i hope 
#they don't because i want to go home.