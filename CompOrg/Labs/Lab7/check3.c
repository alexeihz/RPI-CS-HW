/* adder.c */

#include <stdio.h>
#include <stdlib.h>

/* Use inputs d0, d1, and carry_in to compute both the sum
 * (which is returned) and the carry_out (passed by reference)
 *
 * Note that carry_out could be NULL, indicating that we do
 * not want to determine carry_out (i.e., only return the sum)
 */
int add_two_bits(int d0, int d1, int carry_in, int *carry_out)
{
  /* FILL IN CODE HERE! */
	int xor = d0 ^ d1;
	int ret = carry_in ^ xor;
	if (carry_out){
		*carry_out = (carry_in & xor) | (d0 & d1);
	}
	return ret;
}

int main()
{
	int i, carry_true;
	carry_true = 0;
	char arr[4];
	int c_in = 0;
	for(i=4;i>0; i--){
	  int d0, d1, sum, c_out;
		
	  printf( "Enter binary digit 0: " );
	  scanf( "%d", &d0 );

	  /* Clean the user-generated input */
	  d0 = !!d0;

	  printf( "Enter binary digit 1: " );
	  scanf( "%d", &d1 );

	  /* Clean the user-generated input */
	  d1 = !!d1;

	  sum = add_two_bits( d0, d1, c_in, &c_out );
		
		if(sum == 0 && carry_true == 1){
			arr[i] = '1';
			c_in = c_out = 1;
		}
		else if(sum == 0 && carry_true == 0){
			arr[i] = '0';
			c_in = c_out = 0;
		}
		else if(sum == 1 && carry_true == 1){
			arr[i] = '0';
			c_in = c_out = 1;;
		}
		else if(sum == 1 && carry_true == 0){
			arr[i] = '1';
			c_in = c_out = 0;
		}
		
	  // if ( c_out )
	  // {
		// printf( "%d + %d = %d with a carry\n", d0, d1, add_two_bits( d0, d1, 0, NULL ) );
		// carry_true = 1;
	  // }
	  // else{
		  // carry_true =0;
		  
		// printf( "%d + %d = %d without a carry\n", d0, d1, add_two_bits( d0, d1, 0, NULL ) );
	  // }
	  // printf( "%s", arr );
	}
		
	for(i = 4; i>0; i--){
		printf("%c\n",arr[i]);
	}
	
  return EXIT_SUCCESS;
}