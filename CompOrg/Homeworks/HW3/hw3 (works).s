				.data
			
# Messages to print stuff #

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


# s0 -> return address of program
# s1 -> n
# s2 -> k
# s3 -> m
# s4 -> mat1 (n x k)
# s5 -> mat2 (k n m)
# s6 -> mat3 (n x m)
# t0 -> current matrix
# t1 -> current matrix size
# t2 -> i
# t3 -> j
# t4 -> k
# t5 -> if-condition & temp values
# t6 -> current matrix width
# t7 -> temp for mat1
# t8 -> temp for mat2
# t9 -> temp for sizes
# s7 & s9 -> temp of values of mat1 and mat2
# s8 -> temp for mat3 values




				.text
main:			move $s0, $ra		# store return address
				
				
				
				# load n, k, and m
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
				
				
				
				
				# allocate matrices
				mult $s1, $s2		# multiply n and k
				mflo $t1
				li $t2, 4
				mult $t1, $t2
				mflo $t1
				move $a0, $t1
				li $v0, 9
				syscall
				move $s4, $v0		# move result into mat1
				
				mult $s2, $s3		# multiply k and m
				mflo $t1
				li $t2, 4
				mult $t1, $t2
				mflo $t1
				move $a0, $t1
				li $v0, 9
				syscall
				move $s5, $v0		# move result into mat2
				
				mult $s1, $s3		# multiply n and m
				mflo $t1
				li $t2, 4
				mult $t1, $t2
				mflo $t1
				move $a0, $t1
				li $v0, 9
				syscall
				move $s6, $v0		# move result into mat3
				
				
				
				
				# get matrix A
				li $v0, 4
				la $a0, enter2
				syscall
				
				li $v0, 1
				move $a0, $s1
				syscall
				
				li $v0, 4
				la $a0, x
				syscall
				
				li $v0, 1
				move $a0, $s2
				syscall
				
				li $v0, 4
				la $a0, sadboi
				syscall
				
				
				move $t0, $s4		# load mat1 array into t0
				mult $s1, $s2
				mflo $t1
				li $t2, 0			# set i = 0
				jal get_mat
				
				
				
				
				# get matrix B
				li $v0, 4
				la $a0, enter3
				syscall
				
				li $v0, 1
				move $a0, $s2
				syscall
				
				li $v0, 4
				la $a0, x
				syscall
				
				li $v0, 1
				move $a0, $s3
				syscall
				
				li $v0, 4
				la $a0, sadboi
				syscall
				
				
				move $t0, $s5		# load mat2 array into t0
				mult $s2, $s3
				mflo $t1
				li $t2, 0			# set i = 0
				jal get_mat
				
				
				
				jal print_newline
				
				
				
				move $t0, $s4	# load mat1 array into t0
				mult $s1, $s2
				mflo $t1
				li $t2, 0		# i = 0
				li $t3, 0		# j = 0
				move $t6, $s2	# load columns into t6
				jal print_openb
				jal print_mat 
				jal print_tabby
				jal print_closeb
				jal print_newline
				
				
				li $v0, 4
				la $a0, multiplied
				syscall
				
				
				move $t0, $s5	# load mat2 array into t0
				mult $s2, $s3
				mflo $t1
				li $t2, 0		# i = 0
				li $t3, 0		# j = 0
				move $t6, $s3	# load columns into t6
				jal print_openb
				jal print_mat 
				jal print_tabby
				jal print_closeb
				jal print_newline
				
				
				li $v0, 4
				la $a0, equals
				syscall
				
				
				#move $t8, $s5		# load mat2 array into t8
				mult $s2, $s3
				mflo $s7
				li $t3, 0			# set j = 0
				
				#move $t7, $s4		# load mat1 array into t7
				mult $s1, $s2
				mflo $t9
				li $t4, 0			# set k = 0
				
				
				
				#move $t0, $s6		# load mat3 array into t0
				mult $s1, $s3
				mflo $t1
				li $t2, 0			# set i = 0
				
				li $t0, 0
				
				#jal i_loop
				
				# s6 is the final matrix
				# do the multiplication here
				# probably need to make some functions below to help
				
				
				
				
				
				
				
				
				move $t0, $s6	# load mat3 array into t0
				mult $s1, $s3
				mflo $t1
				li $t2, 0		# i = 0
				li $t3, 0		# j = 0
				move $t6, $s3	# load columns into t6
				jal print_openb
				jal print_mat 
				jal print_tabby
				jal print_closeb
				jal print_newline
				
				
				
				
				
				j exit
				
i_loop: beq $t2, $s1, i_end #End i_loop if i = rowsA
        nop
j_loop: beq $t3, $s3, j_end #End j_loop if j = colsB
        nop
k_loop: beq $t4, $s2, k_end #End k_loop if k = rowsB
        nop

        #loop body

        li $t7, 0
        li $t5, 0
        li $t6, 0
                            # i * M + k - 1
        mul $t7, $t2, $s1   #i * #col in matrixA
        add $t7, $t7, $t4   #t4 + k
		addi    $t7,$t7,-1              # t4 - 1
		sll     $t7,$t7,2               # convert index to byte offset
		addu    $t7,$t7,$s1	          # Now points to value at matrixA[i][k]
		lw      $t7,0($t7)              # Loads value at matrixA[i][k]

                    # k * M + j - 1
        mul $t5, $t4, $s2   #k * #col in matrixB
        add $t5, $t5, $t3   #t5 + j
        addi $t5, $t5, -1   #t5 -1
        sll  $t5,$t5,2      # convert index to byte offset
		addu $t5, $t5, $s1   #t5 now points to value at matrixB[k][j]
        lw $t5, 0($t5)      #t5 loads value at matrixB[k][j]

                    # i * M + j - 1
        mul $t6, $t2, $s3   #i * #col in result
        add $t6, $t6, $t3   #t6 + j
        addi $t6, $t6, -1   #t6 -1
        sll  $t6,$t6,2      # convert index to byte offset
		addu $t6, $t6, $s6   #t6 now points to value at result[i][j]
        lw $t6, 0($t6)      #t6 loads value at result[i][j]

        mul $t8, $t7, $t5   #t8 = matrixA[i][k]*matrixB[k][j]

        add $t9, $t8, $t9   #t9 = result[i][j] + matrixA[i][k]*matrixB[k][j]
        sw $t9, 0($t6)

        #end loop body

        addi $t4, $t4, 1    #k++
        j k_loop        #Return to start of k_loop
k_end:
        addi $t1, $t1, 1    #j++
        li $t4, 0       #Resets k counter to 0
		li $t9, 0
        j j_loop        #Return to start of j_loop
j_end:
        addi $t0, $t0, 1    #i++
        li $t3, 0       #Resets j counter to 0
        j i_loop        #Return to start of i_loop

i_end:      jr $ra			

			
get_mat:		li $v0, 5			# load read_int
				syscall
				
				sw $v0, 0($t0)
				
				addi $t0, $t0, 4	# mat = mat + 4
				addi $t2, $t2, 1	# i = i + 1
				
				slt $t5, $t2, $t1	# t5 = (i < matrix size)
				beq	$t5, 0, ret		# if t5 == 0 => break
				j get_mat
			
			
print_mat:		li $v0, 1				# load print_int
				lw $a0, 0($t0)			# load value of mat into a0
				syscall
				
				addi $t0, $t0, 4		# mat = mat + 4
				addi $t2, $t2, 1		# i = i + 1
				addi $t3, $t3, 1		# j = j + 1
				
				slt $t5, $t2, $t1		# t4 = (i < 16)
				beq	$t5, 0, ret			# if t4 == 0 => break
				
				beq $t3, $t6, print_line	# if j == width => print line
				j print_tab
			
			
ret:			jr $ra

exit:			li $v0 10
				syscall

print_openb:	li $v0, 4
				la $a0, openbracket
				syscall
				jr $ra
				
print_closeb:	li $v0, 4
				la $a0, closedbracket
				syscall
				jr $ra
				
print_newline:	li $v0, 4
				la $a0, newline
				syscall
				jr $ra
				
print_tabby:	li $v0, 4
				la $a0, tab
				syscall
				jr $ra

print_tab:		li $v0, 4			# load print_string
				la $a0, tab			# load tab character
				syscall				# print \t
				j print_mat			# jump back
			
print_line:		li $v0, 4
				la $a0, tab
				syscall
				li $v0, 4			# load print_string
				la $a0, closedbracket
				syscall
				li $v0, 4
				la $a0, newline		# load newline character
				syscall				# print \n
				li $t3, 0			# set j = 0
				li $v0, 4
				la $a0, openbracket
				syscall
				j print_mat			# jump back
			
			
print:			li $v0, 4	# load print_string
				syscall
				jal $ra	