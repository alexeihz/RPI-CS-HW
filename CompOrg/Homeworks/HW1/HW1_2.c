 /*HW1.c */
/* NAME: Alexei Hazell */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//function that counts the maximum number of digits in a number
int countDigit(int n) { 
    int count = 0;
	if(n==0){
		return 1;
	}
    while (n != 0) { 
        n = n / 10; 
        ++count; 
    } 
    return count; 
}

//function that preforms matrix multiplication
void multiply(int row, int col, int** matrix1, int row2, int col2, int**matrix2){
	int ** matrix;
	int * max_digits;
	matrix = (int**)malloc(row * sizeof(int*));
	int i,j,k,h;
	//int min_row, min_col;
	int num;
	num = 0;
	max_digits = calloc(col,sizeof(int));
	//finds the smallest row in length and smallest column in length
	// if(row2 <= row){
		// min_row = row2;
	// }
	// else{
		// min_row = row;
	// }
	// if(col2 <= col){
		// min_col = col2;
	// }
	// else{
		// min_col = col;
	// }
	for(i = 0;i<row;i++){
		matrix[i] = (int*)malloc(col2);
	}
	
	//matrix multiplication
	
	//if(col<row && row2<col2){
		for(k=0; k<row; k++){
			for(h=0; h<col2; h++){
				for(i=0,j=0; i<col && j<row2; i++,j++){
					num += (matrix1[k][j] * matrix2[j][h]);
					//printf("%d %d %d %d \n", j, k,  i, h);
					//printf("%d \n", num);
				}
				//printf("again %d \n", num);
				if(k==0){
					max_digits[h] = countDigit(num);
				}
				else if(countDigit(num) > max_digits[h]){
					max_digits[h] = countDigit(num);
				}
				matrix[k][h] = num;
				//printf("%d \n",matrix[0][0]);
				//printf("%d %d \n", k, h);
				num = 0;
				//printf("%d \n", num);
			}
		}
	//}
	
	// else{
		// for(k=0; k<col; k++){
			// for(h=0; h<row2; h++){
				// for(i=0,j=0; i<col2 && j<row; i++,j++){
					// num += (matrix1[k][j] * matrix2[i][h]);
				// }
				// if(k==0){
					// max_digits[h] = countDigit(num);
				// }
				// else if(countDigit(num) > max_digits[h]){
					// max_digits[h] = countDigit(num);
				// }
				// matrix[k][h] = num;
				// num = 0;
			// }
			
		// }
	// }
	//prints multiplied matrix
	
	for(i = 0; i<row; i++){
		printf("[");
		for(j=0;j<col2; j++){
			for(k = countDigit(matrix[i][j]); k<max_digits[j]; k++){
				printf(" ");
			}
			printf("%d",matrix[i][j]);
			if(j!=col2-1){
				printf(" ");
			}
		}
		printf("]");
		printf("\n");
	}
}


int main( int argc, char * argv[] ){
/* Ensure we have the correct number of command-line arguments */
	if ( argc != 5 ){
		fprintf( stderr, "ERROR: Invalid inputs!\n" );
		return EXIT_FAILURE;
	}
	if(atoi(argv[2]) != atoi(argv[3])){
		fprintf( stderr, "ERROR: Invalid inputs!\n" );
		return EXIT_FAILURE;
	}
	//variable declaration 
	int i,j,k,x;
	int row,col,row2,col2;
	int ** matrix1;
	int ** matrix2;
	int * max_digits1;
	int * max_digits2;


	printf("Please enter the values for the first matrix (%dx%d):\n",atoi(argv[1]),atoi(argv[2]));
	row = atoi(argv[1]);
	col = atoi(argv[2]);
	//allocates space for the first 2 dimentional matrix
	matrix1 = (int**)malloc(row * sizeof(int*));
	for(i = 0;i<row;i++){
		matrix1[i] = (int*)malloc(col);
	}
	//allocates space for an array that holds the max digits in each column
	max_digits1 = calloc(col,sizeof(int));
	for(i =0; i<row; i++){
		for(j=0; j<col; j++){
			scanf("%d", &x);
			matrix1[i][j] = x;
			if(i==0){
				max_digits1[j] = countDigit(x);
			}
			else if(countDigit(x) > max_digits1[j]){
				max_digits1[j] = countDigit(x);
			}
		}
	}

	printf("Please enter the values for the second matrix (%dx%d):\n",atoi(argv[3]),atoi(argv[4]));
	row2 = atoi(argv[3]);
	col2 = atoi(argv[4]);
	//allocates space for the second 2 dimentional matrix
	matrix2 = (int**)malloc(row2 * sizeof(int*));
	for(i = 0;i<row2;i++){
		matrix2[i] = (int*)malloc(col2);
	}
	//allocates space for an array that holds the max digits in each column	
	max_digits2 = calloc(col2,sizeof(int));
	for(i =0; i<row2; i++){
		for(j=0; j<col2; j++){
			scanf("%d", &x);
			matrix2[i][j] = x;
			if(i==0){
				max_digits2[j] = countDigit(x);
			}
			else if(countDigit(x) > max_digits2[j]){
				max_digits2[j] = countDigit(x);
			}
		}
	}
	printf("\n");
	//prints matrix1
	for(i = 0; i<row; i++){
		printf("[");
		for(j=0;j<col; j++){
			if(row !=1){
				for(k = countDigit(matrix1[i][j]); k<max_digits1[j]; k++){
					printf(" ");
				}
			}
			printf("%d",matrix1[i][j]);
			if(j!=col-1){
				printf(" ");
			}
		}
		printf("]");
		printf("\n");
	}
	printf("multiplied by\n");
	//prints matrix2
	for(i = 0; i<row2; i++){
		printf("[");
		for(j=0;j<col2; j++){
			if(row2!=1){
				for(k = countDigit(matrix2[i][j]); k<max_digits2[j]; k++){
					printf(" ");
				}
			}
			printf("%d",matrix2[i][j]);
			if(j!=col2-1){
				printf(" ");
			}
		}
		printf("]");
		printf("\n");
	}
	printf("equals\n");
	//multiply the matrices
	multiply(row,col,matrix1,row2,col2,matrix2);
	return EXIT_SUCCESS;
}


