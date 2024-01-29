   .data
matrixA:    .word 1,2,3,4,5,6   #Content of matrixA in array form
matrixB:    .word 5,6,7,8,9,10  #Content of matrixB in array form
sizeA:      .word 3,2       #Defines matrixA as being a 3x2 matrix
sizeB:      .word 2,3       #Defines matrixB as being a 2x3 matrix
result:     .word 0:9       #Initialize result as being an array of length 9 populated with 0
tab:        .asciiz "\t"
newLine:    .asciiz "\n"

enter1:			.asciiz "Please enter values for n, k, and m:\n"
enter2:			.asciiz "Please enter values for the first matrix ("
enter3:			.asciiz "Please enter values for the second matrix ("
multiplied:		.asciiz "multiplied by\n"
equals:			.asciiz "equals\n"

result:			.asciiz "Product A x B matrices:\n"
newline:		.asciiz "\n"
tab:			.asciiz "\t"
x:				.asciiz "x"
sadboi:			.asciiz "):\n"
openbracket:	.asciiz "["
closedbracket:	.asciiz "]"
            .globl _main

            .text
			
_main:  # load n, k, and m
		li $v0, 4
		la $a0, enter1
		syscall
		
		li $v0, 5		# load read_int
		syscall
		move $s1, $v0	# set n
		li $v0, 5		# load read_int
		syscall
		move $s2, $v0	# set k
		li $v0, 5		# load read_int
		syscall
		move $s3, $v0 	# set m



		# la $s0, matrixA     #s0 set to base address of matrixA
        # la $s1, matrixB     #s1 set to base address of matrixB
        # la $s2, sizeA       #s2 set to base address of sizeA
        # nop
        # lw $s3, 4($s2)      #s3 set to second val in sizeA (col #)
        # nop
        # lw $s2, 0($s2)      #s2 set to first val in sizeA (row #)
        # la $s4, sizeB       #s4 set to base address of sizeB
        # nop
        # lw $s5, 4($s4)      #s5 set to second val in sizeB (col #)
        # nop
        # lw $s4, 0($s4)      #s4 set to first val in sizeB (row #)
        # la $s6, result      #s6 set to base adress of result
        # add $s7, $s5, $zero #s7 set to col # in result matrix
        # add $t0, $zero, $zero   #Set t0 to zero. i = 0
        # add $t1, $zero, $zero   #Set t1 to zero. j = 0
        # add $t2, $zero, $zero   #Set t2 to zero. k = 0
        li $t3, 0       #Result position set to zero
i_loop: beq $t0, $s2, i_end #End i_loop if i = rowsA
        nop
j_loop: beq $t1, $s5, j_end #End j_loop if j = colsB
        nop
k_loop: beq $t2, $s4, k_end #End k_loop if k = rowsB
        nop

        #loop body

        # li $t4, 0
        # li $t5, 0
        # li $t6, 0
                            i * M + k - 1
        # mul $t4, $t0, $s3   #i * #col in matrixA
        # add $t4, $t4, $t2   #t4 + k
		# addi    $t4,$t4,-1              # t4 - 1
		# sll     $t4,$t4,2               # convert index to byte offset
		# addu    $t4,$t4,$s0             # Now points to value at matrixA[i][k]
		# lw      $t4,0($t4)              # Loads value at matrixA[i][k]

                    k * M + j - 1
        # mul $t5, $t2, $s5   #k * #col in matrixB
        # add $t5, $t5, $t1   #t5 + j
        # addi $t5, $t5, -1   #t5 -1
        # sll  $t5,$t5,2      # convert index to byte offset
		# addu $t5, $t5, $s1   #t5 now points to value at matrixB[k][j]
        # lw $t5, 0($t5)      #t5 loads value at matrixB[k][j]

                    i * M + j - 1
        # mul $t6, $t0, $s7   #i * #col in result
        # add $t6, $t6, $t1   #t6 + j
        # addi $t6, $t6, -1   #t6 -1
        # sll  $t6,$t6,2      # convert index to byte offset
		# addu $t6, $t6, $s6   #t6 now points to value at result[i][j]
        # lw $t8, 0($t6)      #t6 loads value at result[i][j]

        # mul $t7, $t4, $t5   #t7 = matrixA[i][k]*matrixB[k][j]

        # add $t9, $t8, $t7   #t8 = result[i][j] + matrixA[i][k]*matrixB[k][j]
        # sw $t9, 0($t6)

        ##end loop body

        # addi $t2, $t2, 1    #k++
        # j k_loop        #Return to start of k_loop
k_end:
        addi $t1, $t1, 1    #j++
        li $t2, 0       #Resets k counter to 0
        j j_loop        #Return to start of j_loop
j_end:
        addi $t0, $t0, 1    #i++
        li $t1, 0       #Resets j counter to 0
        j i_loop        #Return to start of i_loop

i_end:      #print