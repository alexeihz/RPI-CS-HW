#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    char buf;
    int fd[2], count = 0;
    int pipe_it_up = pipe(fd);
    if ( pipe_it_up == -1 ){
        perror( "pipe() failed" );
        return EXIT_FAILURE;
    }
    int file = open("data.txt", O_RDONLY);
    //printf("%d\n", atoi(argv[1]));
    while(read(file,&buf,1) && count < atoi(argv[1])){
        write( fd[1], &buf , sizeof(char) );
        //printf("%c", buf);
        count++;
    }
    close(file);
    //printf("\n");
    pid_t pid = fork();

    if(pid == 0){
        int totalcount = 0;
        int digitcount = 0;
        while(totalcount < count){
            totalcount++;
            read( fd[0], &buf, sizeof(char) );
            //printf("%c", buf);
            if(isdigit(buf)){
                printf("%c", buf);
                digitcount++;
            }
        }
        printf("\n");
        if(totalcount == 1){
            if(digitcount == 1){
                printf("(filtered %d digit from %d byte)\n", digitcount, totalcount);
            }
            else{
                printf("(filtered %d digits from %d byte)\n", digitcount, totalcount);
            }
        }
        else if(digitcount == 1){
            printf("(filtered %d digit from %d bytes)\n", digitcount, totalcount);
        }
        else{
            printf("(filtered %d digits from %d bytes)\n", digitcount, totalcount);
        }
        
        return EXIT_SUCCESS;
    }

    else{
        waitpid(pid, NULL, 0 );
    }
    
    return EXIT_SUCCESS;
}