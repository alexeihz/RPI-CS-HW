#include <stdio.h>
#include <math.h>

void tri(int x){
	int i;
	int j;
	//int height = (x/2) + 1;
	int stars=1;
	// char star[x];
	// int count = 1;
	
	for(j=0;j<x;j++){
		for(i=0;i<stars;i++){
			printf("%c",'*');
		}
		printf("%c",'\n');
		stars = stars +2;
	}
	
	//float hypo = sqrt((x^2) + (stars^2));
	
	// printf("What is n? ");
	// scanf("%d",&x);
	// for (j = 0; j<x; j++){
		// if(j==(x/2)){
			// star[j] = '*';
		// }
		// else{
			// star[j] = ' ';
		// }
	// }
	
	// for(i=0;i<height;i++){
		// printf("%s",star);
		// star[(x/2)+count] = '*';
		// star[(x/2)-count] = '*';
		// count++;
		// printf("%c",'\n');
	// }
	
}
 
 
long fib(long x){
	if(x == 0){
		return 0;
	}
	if(x==1){
		return 1;
	}
	return fib(x-1) + fib(x-2);
}

int main(void){
	int x;
	// int i;
	// int j;
	// int k;
	// int spaces;
	printf("What is n? ");
	scanf("%d",&x);
	//printf("%d",x);
	//spaces = (x/2);
	// for(i=0;i<x;i++){
		//printf("%d",height);
		// for(k = spaces; k>0;k--){
			// printf("%c",' ');
		// }
		
		// spaces--;
		// i++;
		// for(j=0;j<i;j++){
			
			// printf("%c",'*');
		// }
		// printf("%c",'\n');
	// }
	
	tri(x);
	int n;
	printf("What is n? ");
	scanf("%d",&n);
	printf("%d \n",fib(n));
}