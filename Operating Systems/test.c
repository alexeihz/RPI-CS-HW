#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/stat.h>

int main(){
    int t = sizeof( int * );
    int * r = malloc( sizeof( int ) );
    float * i = malloc( sizeof( float ) );
    double ** x = calloc( 20, sizeof( double * ) );
    *i = 8.88;
    *r = sizeof( short );
    pid_t p = fork();
    printf( "{%d}{%d}{%.3f}{%d}{", t, *r, *i, p );
    if ( p == 0 )
    {
        x[t] = calloc( 20, sizeof( double ) );
        *r = t - *r;
        printf( "you're a %d}\n", *r );
        x[t][*r] = 3.10;
    }
    else if ( p > 0 )
    {
        x[t] = calloc( 40, sizeof( double ) );
        *r = t + *r;
        printf( "square %d}\n", t );
        waitpid( p, NULL, 0 );
    }
    printf( "{%0.2lf}\n", x[t][t-2] );
    return EXIT_SUCCESS;
}