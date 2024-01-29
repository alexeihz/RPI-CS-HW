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
				# mult $s1, $s2		# multiply n and k
				# mflo $t1
				# li $t2, 4
				# mult $t1, $t2
				# mflo $t1
				# move $a0, $t1
				# li $v0, 9
				# syscall
				# move $s4, $v0		# move result into mat1
				
				# mult $s2, $s3		# multiply k and m
				# mflo $t1
				# li $t2, 4
				# mult $t1, $t2
				# mflo $t1
				# move $a0, $t1
				# li $v0, 9
				# syscall
				# move $s5, $v0		# move result into mat2
				
				# mult $s1, $s3		# multiply n and m
				# mflo $t1
				# li $t2, 4
				# mult $t1, $t2
				# mflo $t1
				# move $a0, $t1
				# li $v0, 9
				# syscall
				# move $s6, $v0		# move result into mat3
				
				
				
				
				
				## get matrix A
				# li $v0, 4
				# la $a0, enter2
				# syscall
				
				# li $v0, 1
				# move $a0, $s1
				# syscall
				
				# li $v0, 4
				# la $a0, x
				# syscall
				
				# li $v0, 1
				# move $a0, $s2
				# syscall
				
				# li $v0, 4
				# la $a0, sadboi
				# syscall
				
				
				# move $t0, $s4		# load mat1 array into t0
				# mult $s1, $s2
				# mflo $t1
				# li $t2, 0			# set i = 0
				# jal get_mat
				
				
				
				
				##get matrix B
				# li $v0, 4
				# la $a0, enter3
				# syscall
				
				# li $v0, 1
				# move $a0, $s2
				# syscall
				
				# li $v0, 4
				# la $a0, x
				# syscall
				
				# li $v0, 1
				# move $a0, $s3
				# syscall
				
				# li $v0, 4
				# la $a0, sadboi
				# syscall
				
				
				# move $t0, $s5		# load mat2 array into t0
				# mult $s2, $s3
				# mflo $t1
				# li $t2, 0			# set i = 0
				# jal get_mat
				
				
				
				# jal print_newline
				
				
				
				
# get_mat:		li $v0, 5			# load read_int
				# syscall
				
				# sw $v0, 0($t0)
				
				# addi $t0, $t0, 4	# mat = mat + 4
				# addi $t2, $t2, 1	# i = i + 1
				
				# slt $t5, $t2, $t1	# t5 = (i < matrix size)
				# beq	$t5, 0, ret		# if t5 == 0 => break
				# j get_mat

				