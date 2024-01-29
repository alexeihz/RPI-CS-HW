#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//checkpoint 1
/*
each four character sequence represents 2 bytes
744 bytes / 46.5 lines = 16 bytes per line / 8 sequences per line = 2 bytes per sequence
*/
int check1(){
	//reading	
	FILE * data;
	int * i = (int*)calloc(744/sizeof(int), sizeof(int));
	data = fopen("lab03-data.dat", "r");
	fread(i, sizeof(int), 744/sizeof(int), data);
	fclose(data);
	//printing
	for (int j=0; j<((744)/sizeof(int)); j++){
		printf("Data point # %d: %d\n",j, i[j]);
	}
	free(i);
	return 0;
}

//checkpoint 2
int check2(){
	//reading	
	FILE * data;
	unsigned long * i = (unsigned long*)calloc(744/sizeof(unsigned long), sizeof(unsigned long));
	data = fopen("lab03-data.dat", "r");
	fread(i, sizeof(unsigned long), 744/sizeof(unsigned long), data);
	fclose(data);
	//printing
	for (int j=0; j<((744)/sizeof(unsigned long)); j++){
		printf("Data point # %d: %ld\n",j, i[j]);
	}
	free(i);
	return 0;
}

//checkpoint 3
int check3(){
	//reading	
	FILE * data;
	data = fopen("book-1984.txt", "r");
	//printing
	for (int j=0; j<((744)/sizeof(int)); j++){
		char * line = (char*)calloc(128/sizeof(char), sizeof(char));
		char * base, * yardstick;
		base = yardstick = line;
		fgets(line, 128/sizeof(char), data);
				while (*(line)){
			if (isalnum(*(line)) && (char)(*line) != '\n'){
				printf("%c", *line);
			}
			else{
				yardstick++;
			}
			line++;
		}
		free(base);
		if ((line-yardstick)!=0) printf(" (%ld)\n", line-yardstick);
	}
	fclose(data);
	return 0;
}

int main(){
	check1();
	check2();
	check3();
	return EXIT_SUCCESS;
}