#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int fib2(long x){
	if(x == 0){
		return 0;
	}
	if(x==1){
		return 1;
	}
	return fib2(x-1) + fib2(x-2);
}



int fib(long x, long * arr){
	if(x == 0){
		return 0;
	}
	if(x==1){
		return 1;
	}
	if(arr[x]!=-1){
		return arr[x];
	}
	return fib(x-1,arr) + fib(x-2,arr);
	
}

int main(int argc, char* argv[]){
	int i;
	int n;
	// for(i=1; i<argc; i++){
		// n = atoi(argv[i]);
		// printf("fib2(%d) is %d \n",n,fib2(n));
	// }
	
	printf("\n");
	long * arr = malloc(100 * sizeof(long));
	for(i = 0; i<100; i++){
		arr[i] = -1;
	}
	
	for(i=1; i<argc; i++){
		n = atoi(argv[i]);
		printf("fib(%d) is %d \n",n,fib(n,arr));
	}
	free(arr);
 }