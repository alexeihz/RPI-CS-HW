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
    int count2 = 0;
    int status;
    int pipe_it_up;
    
    int** fd = calloc(argc,sizeof(int*));  
    for (int i = 0 ; i < argc ; i++ ){
       *(fd+i) = calloc(2,sizeof(int)); 
    }             
    
    for(int i = 0; i< argc; i++){
        pipe_it_up = pipe( *(fd+i) );
        if ( pipe_it_up == -1 ){
            perror( "pipe() failed" );
            return EXIT_FAILURE;
        }
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
    fflush(stdout);
    int rc = fork();

    if ( rc == -1 ){
        perror( "fork() failed" );
        return EXIT_FAILURE;
    }

    
    for(int i = 0; i< argc-1; i++){
        if (rc == 0){
            int bytes = 0, wordcount = 0, digitcount = 0, linecount = 0;
            struct stat stats;
            printf("CHILD: Processing \"%s\"\n",*(argv+count));
            if(stat(*(argv+count), &stats) != 0){
                fprintf(stderr, "ERROR: stat() failed: No such file or directory\n");
                printf("CHILD: Failed to process \"%s\"\n",*(argv+count));
                count++;
                count2++;
                exit(EXIT_FAILURE);
            }
            else{
                int j = 0;
                FILE* file = fopen(*(argv+count), "r");
                if(file == NULL){
                    fprintf(stderr,"Error: File not found\n");
                    exit(EXIT_FAILURE);
                }
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
                
                write( (*(*(fd+count2)+1)), &bytes , sizeof(int) );
                write( (*(*(fd+count2)+1)), &wordcount , sizeof(int) );
                write( (*(*(fd+count2)+1)), &linecount , sizeof(int) );
                write( (*(*(fd+count2)+1)), &digitcount , sizeof(int) );
                printf("CHILD: Done processing \"%s\"\n",*(argv+count));
               

            }

            close((*(*(fd+count2)+1)));
            return 0;
        }
        else{ /* rc > 0 */
           

            waitpid(rc, &status, 0 );
            if(status == 1){
                count++;
                count2++;
            }
            else{

            
                int buffer;
                fflush(stdout);
                read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
                if(buffer == 1){
                    printf( "PARENT: File \"%s\" -- %d byte, ", *(argv+count), buffer);
                }
                else{
                    printf( "PARENT: File \"%s\" -- %d bytes, ", *(argv+count), buffer);
                }
                read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
                if(buffer == 1){
                    printf( "%d word, ", buffer );
                }
                else{
                    printf( "%d words, ", buffer );
                }
                read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
                if(buffer == 1){
                    printf( "%d line, ", buffer );
                }
                else{
                    printf( "%d lines, ", buffer );
                }
               
                read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
                
                if(buffer == 1){
                    printf( "%d digit\n", buffer );
                }
                else{
                    printf( "%d digits\n", buffer );
                }
                
                close((*(*(fd+count2))));
                
                
                if(count != argc-1){
                    count++;
                    count2++;
                    printf("PARENT: Calling fork() to create child process for \"%s\"\n", *(argv+count));
                    
                    fflush(stdout);
                    rc = fork();
                    
                }
                else{
                    count2++;
                    printf("PARENT: Calling fork() to create child process for the sentinel\n");
                    
                }   
            }
        }
    }
    
    fflush(stdout);
    rc = fork();
    if(rc == 0){
        char* str = calloc(3,sizeof(char)); 
        printf("CHILD: Calling execl() to execute sentinel.out...\n");
        fflush(stdout);
        sprintf(str, "%d", (*(*(fd+count2)+1)));
        execl("./sentinel.out", "./sentinel.out", str, NULL);
    }
    else{
        waitpid(rc, &status, 0 );
        int buffer;
        read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
        if(buffer == 1){
            printf( "PARENT: Sentinel -- %d byte, ", buffer);
        }
        else{
            printf( "PARENT: Sentinel -- %d bytes, ", buffer);
        }
        read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
        if(buffer == 1){
            printf( "%d word, ", buffer );
        }
        else{
            printf( "%d words, ", buffer );
        }
        read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
        if(buffer == 1){
            printf( "%d line, ", buffer );
        }
        else{
            printf( "%d lines, ", buffer );
        }
        
        read( (*(*(fd+count2))), &buffer, sizeof(int) );  /* BLOCKING CALL */
        
        if(buffer == 1){
            printf( "%d digit\n", buffer );
        }
        else{
            printf( "%d digits\n", buffer );
        }

        printf( "PARENT: All done -- exiting...\n");
        for (int j = 0 ; j < argc ; j++ ){
            free(*(fd+j)); 
        }
        free(fd);
    }

    //setvbuf( stdout, NULL, _IONBF, 0 );
    // printf( "PARENT: All done -- exiting...\n");
    // for (int j = 0 ; j < argc ; j++ ){
    //     free(*(fd+j)); 
    // }
    // free(fd);    
    
    return EXIT_SUCCESS;
}
