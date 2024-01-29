#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// char * reverse( char * s){
//     char buffer[1024];
//     int i, len = strlen( s );
//     for ( i = 0 ; i < len ; i++ ){
//         buffer[i] = s[len-i-1];
//     }
//     buffer[i] = '\0';
//     strcpy( s, buffer );
    
//     return s;
// }


char * reverse(char * s){
    int i, len = strlen( s );
    char * buffer = malloc(len + 1);
    for ( i = 0 ; i < len ; i++ ){
        buffer[i] = s[len-i-1];
    }
    buffer[i] = '\0';
    strcpy( s, buffer );
    free(buffer);
    return s;
}

int main(){
    char s[11] = "1234567890";
    printf("%s\n",s);
    reverse(s);
    printf("%s\n",s);
}