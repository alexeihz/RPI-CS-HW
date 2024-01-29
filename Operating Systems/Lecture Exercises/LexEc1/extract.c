#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    int file, count;
    char buf; 
    file = open(argv[1], O_RDONLY);
    count = 0;
    if(file == -1){
        exit(1);
    }
    while(read(file,&buf,1)){
        if((count+1)%7 == 0){
            
            lseek(file,6,SEEK_CUR);
            printf("%c",buf);
            count = count + 7;
        }
        else{
            count++;
        }
        
    }
	printf("\n");
    close(file);
}