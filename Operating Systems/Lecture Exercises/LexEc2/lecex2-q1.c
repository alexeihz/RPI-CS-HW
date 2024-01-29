#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t p;    /* process id (pid) */

  printf( "PARENT: okay, start here.\n");
  /* create a new (child) process */
  fflush(stdout);
  p = fork();

  /* fork() will attempt to create a new process by
      duplicating/copying the existing running process */

  if ( p == -1 ){
    perror( "fork() failed" );
    return EXIT_FAILURE;
  }

  if ( p > 0 ){
    int status;
    waitpid( p, &status, 0 );    /* BLOCKED */
    
    printf( "PARENT: child process terminated successfully.\n");
    printf( "PARENT: sigh, i'm gonna miss that little child process.\n");

    
  }
  else{
    printf( "CHILD: happy birthday to me!\n" );
    printf( "CHILD: i'm bored....self-terminating....good-bye!\n");

  }

  return EXIT_SUCCESS;
}