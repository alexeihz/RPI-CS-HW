#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t p;    /* process id (pid) */
  pid_t p2;    /* process id (pid) */

  /* create a new (child) process */
  printf( "PARENT: okay, start here.\n");
  fflush(stdout);
  p = fork();
  

  /* fork() will attempt to create a new process by
      duplicating/copying the existing running process */

  if ( p == -1){
    perror( "fork() failed" );
    return EXIT_FAILURE;
  }

  if ( p > 0){
    

    int status;
    int status2;
    waitpid( p, &status, 0 );    /* BLOCKED */
    
    p2 = fork();
    if ( p2 == -1){
      perror( "fork() failed" );
      return EXIT_FAILURE;
    }

    if(p2 == 0){
      printf( "CHILD B: and happy birthday to me!\n");
      printf( "CHILD B: see ya later....self-terminating!\n");
    }
    else{
      waitpid( p2, &status2, 0 );    /* BLOCKED */
      printf( "PARENT: both child processes terminated successfully.\n");
      printf( "PARENT: phew, i'm glad they're gone!\n");
    }
  }
  else if(p == 0){
    printf( "CHILD A: happy birthday to me!\n");
    printf( "CHILD A: i'm bored....self-terminating....good-bye!\n");

  }
  return EXIT_SUCCESS;
}