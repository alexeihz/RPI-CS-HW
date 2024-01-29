#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int hash(char* str, int size){
    int len = strlen( str );
    int total = 0;
    for ( int i = 0 ; i < len ; i++ ){
        total += (int) *(str + i);
    }
    return total % size;
}

void print(char** cache, int size){
    for(int i = 0; i<size; i++){
        if(strlen(*(cache + i)) > 0){
            printf("Cache index %d ==> \"%s\"\n",i,*(cache + i));
        }
    }
}

int main(int argc, char** argv){    
    for(int i = 0; i<strlen(*(argv+1));i++){
        if(!isdigit(*(*(argv+1)+i))){
            fprintf(stderr,"Error: Invalid cache size\n");
            exit(1);
        }
    }
    int size = atoi(*(argv+1));
    int i, j = 0, hashed;
    FILE* file;
    char* word = calloc(128,sizeof(char));
    char character;
    char** cache = calloc(size,sizeof(char*));  

    for (i = 0 ; i < size ; i++ ){
       *(cache+i) = calloc(1,sizeof(char)+1); 
    }
    
    for(i = 2; i<argc; i++){
        file = fopen(*(argv+i), "r");
        if(file == NULL){
            fprintf(stderr,"Error: File not found\n");
            exit(1);
        }
        while(fscanf(file,"%c", &character) == 1){
            if(isalpha(character)){
                *(word + j) = character;
                j++;
            }
            else{
                if(strlen(word) < 3){
                    j = 0;
                    free(word);
                    word = calloc(128,sizeof(char));
                    continue;
                }
                hashed = hash(word,size);
                if(strlen(*(cache + hashed)) == 0){
                    *(cache + hashed) = realloc(*(cache + hashed),sizeof(char)*strlen(word)+1);
                    strcpy(*(cache + hashed), word);
                    printf("Word \"%s\" ==> %d (calloc)\n", word, hashed);
                }
                else{
                    *(cache + hashed) = realloc(*(cache + hashed),sizeof(char)*strlen(word)+1);
                    strcpy(*(cache + hashed),word);
                    printf("Word \"%s\" ==> %d (realloc)\n", word, hashed);
                }
                j = 0;
                free(word);
                word = calloc(128,sizeof(char));
            }
        }
        fclose(file);
    }
    free(word);
    print(cache,size);
    for (i = 0 ; i < size ; i++ ){
       free(*(cache+i)); 
    }
    free(cache);
}