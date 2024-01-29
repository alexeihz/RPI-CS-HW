#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char** argv){ 
    int count = 1;
    int status;
    
    int* p = calloc(2,sizeof(int));   
                   

    int pipe_it_up = pipe( p );  

    if ( pipe_it_up == -1 )
    {
        perror( "pipe() failed" );
        return EXIT_FAILURE;
    }

    
    if(argc == 2){
        printf( "PARENT: Collecting counts for %d file and the sentinel...\n", argc - 1);
    }
    else{
        printf( "PARENT: Collecting counts for %d files and the sentinel...\n", argc - 1);
    }
    struct rlimit rl;
    /* lower the RLIMIT_NPROC to 20 */
    rl.rlim_cur = 20;
    setrlimit( RLIMIT_NPROC, &rl );

    printf("PARENT: Calling fork() to create child process for \"%s\"\n", *(argv+count));
    
    pid_t rc = fork();  /* fork() will copy the fd table to the child */

    if ( rc == -1 )
    {
        perror( "fork() failed" );
        return EXIT_FAILURE;
    }

    
    for(int i = 0; i< count; i++){
        if ( rc == 0 ){
            if(count == argc){
                //printf( "yerrrr\n");
                //waitpid( rc, &status, 0);
                continue;
            }

            //close(*(p));
            int bytes = 0, wordcount = 0, digitcount = 0, linecount = 0;
            struct stat stats;
            if(stat(*(argv+count), &stats) != 0){
                fprintf(stderr, "ERROR: Failed to process \"%s\"\n",(*(argv+count)));
            }
            else{
                int j = 0;
                FILE* file = fopen(*(argv+count), "r");
                if(file == NULL){
                    fprintf(stderr,"Error: File not found\n");
                    //exit(1);
                }
                printf("CHILD: Processing \"%s\"\n",*(argv+count));
                bytes = stats.st_size;
                char* word = calloc(128,sizeof(char));
                char character;
                wordcount = 0;
                digitcount = 0;
                linecount = 0;
                while(fscanf(file,"%c", &character) == 1){
                    if(isalpha(character)){
                        *(word + j) = character;
                        j++;
                    }
                    else{
                        if(strlen(word) > 0){
                            wordcount++;
                        }
                        if(isdigit(character)){
                            digitcount++;
                        }
                        if(character == '\n'){
                            linecount++;
                        }
                        j = 0;
                        free(word);
                        word = calloc(128,sizeof(char));
                    }
                    
                }
                fclose(file);
                free(word);
                printf("CHILD: Done Processing \"%s\"\n",*(argv+count));
                // int* data = calloc(4,sizeof(int));
                // *(data) = bytes;
                // *(data + 1) = wordcount;
                // *(data + 2) = linecount;
                // *(data + 3) = digitcount;
                //printf("%d bytes, %d words, %d lines, %d digits \n",bytes, wordcount, linecount, digitcount);
                write( *(p+1), &bytes , sizeof(int) );
                write( *(p+1), &wordcount , sizeof(int) );
                write( *(p+1), &linecount , sizeof(int) );
                write( *(p+1), &digitcount , sizeof(int) );
                
            }


            /* write data to the pipe */
            
        /******* context switch from the child process to the parent process *******/
            //printf( "CHILD: Wrote %d bytes to the pipe\n", bytes_written );
        }
        else{ /* rc > 0 */
            //close(*(p+1));
            /* read data from the pipe */
            waitpid( rc, &status, 0 );
            int buffer;
            read( *(p), &buffer, sizeof(int) );  /* BLOCKING CALL */
            printf( "PARENT: File \"%s\" -- %d bytes, ", *(argv+count), buffer);
            read( *(p), &buffer, sizeof(int) );  /* BLOCKING CALL */
            printf( "%d words, ", buffer );
            read( *(p), &buffer, sizeof(int) );  /* BLOCKING CALL */
            printf( "%d lines, ", buffer );
            read( *(p), &buffer, sizeof(int) );  /* BLOCKING CALL */
            printf( "%d digit\n", buffer );
            
            if(count != argc-1){
                count++;
                printf("PARENT: Calling fork() to create child process for \"%s\"\n", *(argv+count));
                rc = fork();
                continue;
            }
            else{
                //count++;
                printf("PARENT: Calling fork() to create child process for the sentinel\n");
                //rc = fork();
                //printf( "%d\n",count);
                // break;
            }
            while(waitpid( rc, &status, 0 ) != -1 || errno != ECHILD);
            if(count == argc - 1){
                printf( "PARENT: All done -- exiting...\n");
                free(p);
                
            }
            
            
            
        }
    }
    
    return EXIT_SUCCESS;
}
