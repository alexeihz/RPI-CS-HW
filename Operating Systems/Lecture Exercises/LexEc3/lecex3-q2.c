/* octuplets-threads.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
// #include "lecex3-q2-copy-file.c"


void * copy_file( void * arg );

int main(int argc, char* argv[])
{
  pthread_t tid[argc-1];    /* keep track of thread IDs */

  int i, bytes = 0, rc;

  for ( i = 1 ; i < argc ; i++ ){
    printf("MAIN: Creating thread to copy \"%s\"\n",argv[i]);
    rc = pthread_create(&tid[i],NULL,copy_file,argv[i]);

    if ( rc != 0 )
    {
      fprintf( stderr, "pthread_create() failed (%d)\n", rc );
    }
  }


#if 1
  /* wait for child threads to terminate */
  for ( i = 1 ; i < argc ; i++ )
  {
    int * x;
    pthread_join( tid[i], (void **)&x );   /* BLOCK */
    printf( "MAIN: Thread completed copying %d bytes for \"%s\"\n", *x, argv[i]);
    bytes += *x;
    free( x );
  }
#endif

#if 0
  /* wait for child threads to terminate */
  for ( i = CHILDREN - 1 ; i >= 0 ; i-- )
  {
    int * x;
    pthread_join( tid[i], (void **)&x );   /* BLOCK */
    printf( "MAIN: Joined a child thread that returned %d\n", *x );
    free( x );
  }
#endif
    if(argc-1 == 1){
        printf("MAIN: Successfully copied %d bytes via %d child thread\n",bytes,argc-1);
    }
    else{
        printf("MAIN: Successfully copied %d bytes via %d child threads\n",bytes,argc-1);
    }


  return EXIT_SUCCESS;
}
