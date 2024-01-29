			.data
			
# Messages to print stuff #

enter1:			.asciiz "Enter positive integer:\n"
enter2:			.asciiz "For $"

quarters_str:		.asciiz " quarters\n"
dimes_str:			.asciiz " dimes\n"
nickels_str:		.asciiz " nickels\n"
pennies_str:		.asciiz " pennies\n"

#s0 -> initial money
#s1 -> quarter amount
#s2 -> dime amount
#s3 -> nickels amount
#s4 -> penny amount
#t0 -> number of quarters
#t1 -> remainder 1
#t2 -> set less than if statement 1 
#t3 -> number of dimes
#t4 -> remainder 2
#t5 -> number of nickels
#t6 -> remainder 3
#t7 -> number of pennies
#t8 -> remainder 4
#t9 -> set less than if statement 2

				.text
main:			move $s0, $ra		# store return address

				li $v0, 4
				la $a0, enter1
				syscall
				
				li $v0, 5		# load read_int
				syscall
				move $s0, $v0	# set money
				
				li $v0, 1
				move $a0, $s0
				li $t4, 25		# set quarter amount
				li $t5, 10		# set dime amount
				li $t6, 5		# set nickel amount
				li $t7, 1		# set penny amount
				
quarters:		addi $t4, $t4, -1
				slt $t9, $t4, $s0
				addi $t4, $t4, 1
				beq	$t9, 0, dimes
				divu $s0, $t4
				mflo $t0
				mfhi $t1
				
				li $v0, 1
				move $a0, $t0
				syscall
				li $v0, 4
				la $a0, quarters_str
				syscall
				
				
dimes:			slt $t9, $t1, $t5
				beq	$t9, 1, nickels
				divu $t1, $t5
				mflo $t0
				mfhi $t3
				
				li $v0, 1
				move $a0, $t0
				syscall
				li $v0, 4
				la $a0, dimes_str
				syscall
				
				
nickels:		slt $t9, $t3, $t6
				beq	$t9, 1, pennies
				divu $t3, $t6
				mflo $t0
				mfhi $t3
				
				li $v0, 1
				move $a0, $t0
				syscall
				li $v0, 4
				la $a0, nickels_str
				syscall
				
				
pennies:	
				li $v0, 1
				move $a0, $t3
				syscall
				li $v0, 4
				la $a0, pennies_str
				syscall
				
				li $v0, 10
				syscall
				
				