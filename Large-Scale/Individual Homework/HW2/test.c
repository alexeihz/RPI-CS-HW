#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(){
    FILE *input;
    char input_line[256];
    
	input = fopen("hw1-input01.txt", "r");
    //checks if the file can be opened
	if (!input) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }
    char * needle = "color";
    while (fgets(input_line, 256, input) != NULL){
        char * found = strstr(input_line, needle);
        if(found != NULL){
            printf("%s", found);
        }
    }
    //char * haystack = "Hats off to you.";
    
    
    
}