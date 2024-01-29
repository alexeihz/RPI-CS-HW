	.data
b1:
	.asciiz "byte #1: "

	.data
b2:
	.asciiz "\nbyte #2: "

	.data
b3:
	.asciiz "\nbyte #3: "

	.data
b4:
	.asciiz "\nbyte #4: "

	.data
endl:
	.asciiz "\n"



	.text
main:
	.globl main
	li $a0, 0x4a889cf1 #given
	addi $t1, $a0, 0

#first

	#shift
	srl $t0, $t1, 24
	#print
	li $v0, 4
	la $a0, b1
	syscall
	li $v0, 1
	addi $a0, $t0, 0
	syscall

#second
	#shift
	li $t3, 0x00FFFFFF
	and $t0, $t1, $t3
	srl $t0, $t0, 16
	#print
	li $v0, 4
	la $a0, b2
	syscall
	li $v0, 1
	addi $a0, $t0, 0
	syscall

#third
	#shift
	li $t3 0x0000FFFF
	and $t0, $t1, $t3
	srl $t0, $t0, 8
	#print
	li $v0, 4
	la $a0, b3
	syscall
	li $v0, 1
	addi $a0, $t0, 0
	syscall

#fourth
	#shift
	li $t3 0x000000FF
	and $t0, $t1, $t3
	#print
	li $v0, 4
	la $a0, b4
	syscall
	li $v0, 1
	addi $a0, $t0, 0
	syscall

#conclusion:
	li $v0, 4
	la $a0, endl
	syscall
	jr $ra