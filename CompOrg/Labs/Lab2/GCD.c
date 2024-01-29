#include <stdio.h>
#include <math.h>

int GCD(int A, int B){
	if(A==0){
		return B;
	}
	if(B==0){
		return A;
	}
	A = B*(A/B)+(A%B);
	//printf("%d \n",A%B);
	return GCD(B,A%B);
}

int main(void){
	printf("%d \n",GCD(105,252));
}