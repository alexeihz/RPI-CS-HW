#	int x = 0;
#	if ( x < 5 ){
#		x += 3;
#	}

       .data
msg:   .asciiz "($t0) equals "

       .text
       .globl main
main:  li $v0, 4       # syscall 4 (print_str)
	   li $t0, 8	   # store x
       la $a0, msg     # argument: string
       syscall         # print the string
       li $v0, 1		# syscall 1 (print int)
       li $t1, 0          #set for int
       li $t2, 5           #prepare to receive
       slt $t1, $t0, $t2    #check 
       add $t0, $t1, $t0           #
       add $t0, $t1, $t0           #
       add $t0, $t1, $t0           #
       li $a0, 0
       add $a0, $t0, $a0               #
       syscall              #

       jr $ra          # return to caller