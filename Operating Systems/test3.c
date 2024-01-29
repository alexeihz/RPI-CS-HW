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
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char * nine;
void * q9( void * y ){
    char n = *(char *)y;
    for ( int m = n + n ; m > 0 ; m-- ){
        pthread_mutex_lock(&mutex);
        { 
        usleep( 10 ); /* <== forces a thread context switch... */
        strncat( nine, &n, 1 );
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit( NULL );
    return NULL;
}

int main(){
nine = malloc( 9999 );
nine[0] = '\0';
pthread_t * t = calloc( 9, sizeof( pthread_t ) );
for ( int i = 0 ; i < 9 ; i++ ){
    char * j = malloc( 1 );
    *j = 'q' + i;
    pthread_create( t + i, NULL, q9, j );
    free(j);
}
for ( int i = 0 ; i < 9 ; i++ ){ 
    pthread_join( *(t + i), NULL );
}
free(t);
printf( "%s\n", nine );
free(nine);
return EXIT_SUCCESS;
}


