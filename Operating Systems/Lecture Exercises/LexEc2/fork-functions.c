#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>


int lecex2_child(){
    FILE* file;
    char character; 
    int size = 1;
    file = fopen("data.txt", "r");
    if(file == NULL){
        fprintf(stderr, "data.txt does not exist.");
        abort();
    }
    while(fscanf(file,"%c", &character) == 1){
        if(size == 6){
            break;
        }
        size++;
    }
    if(size < 6){
        fprintf(stderr, "data.txt does not have a sixth char.");
        abort();
    }
    fclose(file);
    exit(character);
}


int lecex2_parent(){
    int status;
    waitpid( 0, &status, 0 );    /* BLOCKED */
    //wait(NULL);

    if ( WIFSIGNALED( status ) )   /* child process was terminated   */
    {                              /*  by a signal (e.g., seg fault) */
      printf( "PARENT: child process terminated abnormally\n" );
      return EXIT_FAILURE;  
    }
    else /* if ( WEXITED( status ) ) */
    {
      int exit_status = WEXITSTATUS( status );
      printf( "PARENT: child process reported \'%c\'\n", exit_status );
      return EXIT_SUCCESS;
    }
}