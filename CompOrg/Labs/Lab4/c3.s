#	int x = 0;
#	if ( x < 5 ){
#		x += 3;
#	}

       .data
msg:   .asciiz "GCD( "

       .data
msg2:  .asciiz ", "

       .data
msg3:  .asciiz " ) is " 

       .text
       .globl main
main:  


       li $t0, 54
       li $t1, 45     #set x, y 


       li $v0, 4       # syscall 4 (print_str)
       la $a0, msg     # argument: string
       syscall         # print the string
       li $v0, 1
       li $a0, 0
       add $a0, $a0, $t0
       syscall
       li $v0, 4
       la $a0, msg2
       syscall
       li $v0, 1
       li $a0, 0
       add $a0, $a0, $t1
       syscall
       li $v0, 4
       la $a0, msg3
       syscall

gcd:
       beq $t0, $t1, gcd_0 #def gcd(a, b):
                            #2 if a == b:
                             #3 return a
       bgt $t0, $t1, gcd_1 #4 if a > b:
                            #5 gcd(a - b, b)
       sub $t1, $t1, $t0
       j gcd
       gcd_1:
              sub $t0, $t0, $t1
              j gcd
       gcd_0:
              li $v0, 1
              li $a0, 0
              add $a0, $a0, $t0
              syscall
              jr $ra  # return to caller