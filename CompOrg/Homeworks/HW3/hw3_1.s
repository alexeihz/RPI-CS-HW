# hw3.s
# NAME: Alexei Hazell

        .data
newline:.asciiz "\n"
tab:    .asciiz "\t"
l_brckt:.asciiz "["
r_brckt:.asciiz "]"

        # global parameters n, k, and m (e.g., 4x3 multiply by 3x4),
        # which the user inputs in the matrix_size procedure
n:      .word 4
k:      .word 3
m:      .word 4

txt1:   .asciiz "Please enter values for n, k, and m:\n"
txt2:   .asciiz "Please enter values for the first matrix ("
txt3:   .asciiz "Please enter values for the second matrix ("
txt4:   .asciiz "x"
txt5:   .asciiz "):\n"

################################################################################

        .text
        .globl main
        .globl matrix_multiply
        .globl matrix_print
        .globl matrix_ask
        .globl matrix_sizes

################################################################################

matrix_sizes:
        # Ask the user for the matrix sizes, i.e., n, k, and m,
        # which correspond to multiplying an nxk matrix by a kxm matrix
		
        
		li $v0, 4
		la $a0, txt1
		syscall
		
		li $v0, 5
		syscall
		move $t0, $v0
		sw $t0, n
		
		li $v0, 5
		syscall
		move $t0, $v0
		sw $v0, k
		
		
		li $v0, 5
		syscall
		move $t0, $v0
		sw $v0, m
		
        jr $ra

################################################################################

matrix_ask:
        # Ask the user for the matrix values to store in
        # the memory address indicated by the $a0 register
       
	   
		li $v0, 5			# load read_int
		syscall
		
		sw $v0, 0($t7)
		
		addi $t7, $t7, 4	# mat = mat + 4
		addi $t4, $t4, 1	# i = i + 1		
		
		blt $t4, $t3, matrix_ask	# t5 = (i < matrix size)
		# beq	$t5, 0, ret		# if t5 == 0 => break
		# j get_matrix
		jr $ra

################################################################################

matrix_ask2:
        # Ask the user for the matrix values to store in
        # the memory address indicated by the $a0 register
       
		li $v0, 4
		la $a0, txt3
		syscall
	   
		lw $t1, k
		li $v0, 1
		move $a0, $t1
		syscall
		
		li $v0, 4
		la $a0, txt4
		syscall
		
		li $v0, 1
		move $a0, $t2
		syscall
	   
		li $v0, 4
		la $a0, txt5
		syscall
		
		# mul $t3, $t0, $t1
		#sll $t3, $t3, 2	
		# addi $t4, $t4, 0
		# jal get_matrix
	   
        jr $ra

################################################################################

main:
        # Initialize stack as necessary

        # Obtain user input values n, k, and m
        jal matrix_sizes

        # Allocate space for matrices
		
		lw $t0, n
		lw $t1, k
		lw $t2, m
		
		mul $t3, $t0, $t1
		sll $t3, $t3, 2
		
		# mult $s0, $s1		# multiply n and k
		# mflo $t1
		# li $t2, 4
		# mult $t1, $t2
		# mflo $t1
		move $a0, $t3
		li $v0, 9
		syscall
		move $s0, $v0		# move result into mat1
		
		
		li $v0, 4
		la $a0, txt2
		syscall
	   
		li $v0, 1
		move $a0, $t0
		syscall
		
		li $v0, 4
		la $a0, txt4
		syscall
		
		li $v0, 1
		move $a0, $t1
		syscall
	   
		li $v0, 4
		la $a0, txt5
		syscall
		
		mult $t0, $t1
		mflo $t3
		move $t4, $zero
		move $t7, $s0
		
        # Get input for matrix A
        jal matrix_ask

		#move $a1, $s0
		
		mul $t3, $t1, $t2
		sll $t3, $t3, 2
		# mult $s1, $s2		# multiply k and m
		# mflo $t1
		# li $t2, 4
		# mult $t1, $t2
		# mflo $t1
		#addi $t4, $t3, 0
		move $a0, $t3
		li $v0, 9
		syscall
		move $s1, $v0		# move result into mat2

	
		li $v0, 4
		la $a0, txt3
		syscall
	   
		lw $t1, k
		li $v0, 1
		move $a0, $t1
		syscall
		
		li $v0, 4
		la $a0, txt4
		syscall
		
		li $v0, 1
		move $a0, $t2
		syscall
	   
		li $v0, 4
		la $a0, txt5
		syscall
		
		mult $t1, $t2
		mflo $t3
		move $t4, $zero
		move $t7, $s1
	
        # Get input for matrix B
        jal matrix_ask
		
		#move $a2, $s1
		
		mul $t3, $t0, $t2
		sll $t3, $t3, 2
		
		# mult $s0, $s2		# multiply n and m
		# mflo $t1
		# li $t2, 4
		# mult $t1, $t2
		# mflo $t1
		# addi $t6, $t3, 0
		move $a0, $t3
		li $v0, 9
		syscall
		move $s2, $v0		# move result into mat3
		
		
		li $t0, $zero   #i = 0
		li $t1, $zero	#j = 0
		li $t2, $zero	#k = 0
		
		lw $s3, n
		lw $s4, k
		lw $s5, m
		
		li $t6, 0
        # Perform multiplication to get matrix C
        jal matrix_multiply

        # Output result
        jal matrix_print

        # Cleanup stack and return

        jr $ra


################################################################################

matrix_multiply:
        # multiply matrix A (address $a0) by  matrix B (address $a1),
        # storing the result in matrix C (address $a2)
		
		beq $t0, $s3, end
j_loop:	
		beq $t1, $s5, j_end
k_loop:	
		beq $t2, $s4, k_end
		
		#loop body

        

        #end loop body

        addi $t2, $t2, 1    #k++
        j k_loop        #Return to start of k_loop
		
		
k_end:	
		addi $t1, $t1, 1    #j++
        li $t2, 0       #Resets k counter to 0
		
		# Set the starting point at the first matrix
		#move $s0, $a1
		mul $t9, $t2, $s1
		sll $t9, $t9, 2
		add $s3, $s3, $t9
		# Set the starting point at the second matrix
		#move $s1, $a2
		add $t3, $zero, $t0
		sll $t3, $t3, 2
		add $s4, $s4, $t3
		
        j j_loop 
		
j_end:
        addi $t0, $t0, 1    #i++
        li $t1, 0       #Resets j counter to 0
		
		# Set the starting point at the first matrix
		move $s3, $a1
		mul $t9, $t2, $s1
		sll $t9, $t9, 2
		add $s3, $s3, $t9
		# Set the starting point at the second matrix
		move $s4, $a2
		add $t3, $zero, $t0
		sll $t3, $t3, 2
		add $s4, $s4, $t3
		
        j matrix_multiply		
	
end:
		jr $ra

################################################################################

matrix_print:
        # print matrix (address $a0)
	
        jr $ra
		
################################################################################		
