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
#include <sys/ipc.h>
#include <sys/shm.h>

int lecex3_q1_child( int pipefd ){
    int buffer;
    int buffer1;
    read( pipefd, &buffer, 4 ); 
    key_t key = buffer;
    //printf("%d\n",key);
    read( pipefd, &buffer1, 4 );
    int size = buffer1;
    //printf("%d\n",size);
    int shmid = shmget( key, size, 0660 );
    //printf("%d\n",shmid);
    if ( shmid == -1 ){
        perror( "shmget() failed" );
        return EXIT_FAILURE;
    }

    char * data = shmat( shmid, NULL, 0 );

    if ( data == (char *)-1 ){
        perror( "shmat() failed" );
        return EXIT_FAILURE;
    }
    
    int j = 0;
    while ( j <= size){
        //printf("%d\n",data[j]);
        data[j] = toupper( data[j] );
        j++;
    }

  /* child process detaches from the shared memory segment */
  int rc = shmdt( data );

  if ( rc == -1 ){
    perror( "shmdt() failed" );
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}