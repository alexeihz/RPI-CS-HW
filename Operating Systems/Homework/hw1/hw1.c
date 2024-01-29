#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        if(strlen(*(cache + i)) != 0){
            printf("Cache index %d ==> \"%s\"\n",i,*(cache + i));
        }
    }
}

void checkpunc(char* str){
    for(int i = 0; i<strlen(str); i++){
        if(isalpha(*(str+i)) == 0){
            for(int j = i; j<strlen(str); j++){
                *(str + j) = *(str+j+1);
            }
            i--;
        }
    }
}

int main(int argc, char** argv){
     if(argc < 2){
        fprintf(stderr,"Error: Not enough arguments\n");
        exit(1);
    }
    
   for(int i = 0; i<strlen(*(argv+1));i++){
        if(!isdigit(*(*(argv+1)+i))){
            fprintf(stderr,"Error: Invalid cache size\n");
            exit(1);
        }
    }
    int size = atoi(*(argv+1));
    int i, hashed;
    FILE* file;
    char* word = calloc(128,sizeof(char*));
    char** cache = calloc(size,sizeof(char*));

    for (i = 0 ; i < size ; i++ ){
       *(cache+i) = calloc(128,sizeof(char)); 
    }
    
    for(i = 2; i<argc; i++){
        file = fopen(*(argv+i), "r");
        if(file == NULL){
            fprintf(stderr,"Error: File not found\n");
            exit(1);
        }
        while(fscanf(file,"%s", word) == 1){
            checkpunc(word);
            if(strlen(word) < 3){
                continue;
            }
            hashed = hash(word,size);
            if(strlen(*(cache + hashed)) == 0){
                strcpy(*(cache + hashed), word);
                printf("Word \"%s\" ==> %d (calloc)\n", word, hashed);
            }
            else{
                *(cache + hashed) = realloc(*(cache + hashed),sizeof(sizeof(char*))+1);
                strcpy(*(cache + hashed),word);
                printf("Word \"%s\" ==> %d (realloc)\n", word, hashed);
            }
            
        }
        fclose(file);
    }
    print(cache,size);
    free(word);
    for (i = 0 ; i < size ; i++ ){
       free(*(cache+i)); 
    }
    free(cache);
}