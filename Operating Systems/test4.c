#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void * q8( void * arg )
{
int * w = (int *)arg;
pthread_mutex_lock( &mutex );
*w += 8;
pthread_mutex_unlock( &mutex );
return NULL;
}
int main()
{
pthread_t tid1, tid2;
int eight = 4;
pthread_create( &tid1, NULL, q8, &eight );
eight = 5;
pthread_create( &tid2, NULL, q8, &eight );
eight = 6;
pthread_join( tid1, NULL );
pthread_join( tid2, NULL );
printf("%d\n", eight);
return EXIT_SUCCESS;
}