#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/stat.h>

void f1( int s ) { fprintf( stderr, "-I-LIKE-" ); }
void f2( int s ) { printf( "-MOUSE-" ); fflush( stdout ); }
int main(){
int p[2];
    pipe( p );
    dup2( p[1], 1 );
    signal( SIGUSR1, f1 );
    signal( SIGUSR2, f2 );
    printf( "COFFEE" );
    fflush( stdout );
    sleep( 1 );
    printf( "K-A" );
    fflush( stdout );
    sleep( 1 );
    char * buffer = calloc( 3, sizeof( char ) );
    close( p[1] );
    char * ptr = buffer;
    read( p[0], buffer, 2 );
    fprintf( stderr, "%s%sA-PU", buffer, ptr++ );
    read( p[0], buffer, 2 );
    fprintf( stderr, "%sS\n", buffer );
    free( buffer );
    close( p[0] );
return EXIT_SUCCESS;
}