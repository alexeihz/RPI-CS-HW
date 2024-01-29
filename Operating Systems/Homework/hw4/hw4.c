/* tcp-client.c */

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define MAXBUFFER 8192

int main(int argc, char * argv[]){
  /* create TCP client socket (endpoint) */
  int sd = socket( PF_INET, SOCK_STREAM, 0 );

  if ( sd == -1 )
  {
    perror( "socket() failed" );
    exit( EXIT_FAILURE );
  }

#if 0
  struct hostent * hp = gethostbyname( "localhost" );  /* 127.0.0.1 */
  struct hostent * hp = gethostbyname( "127.0.0.1" );
  struct hostent * hp = gethostbyname( "128.113.126.39" );
#endif

  struct hostent * hp = gethostbyname( argv[1] );

  if ( hp == NULL )
  {
    fprintf( stderr, "ERROR: gethostbyname() failed\n" );
    return EXIT_FAILURE;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  memcpy( (void *)&server.sin_addr, (void *)hp->h_addr, hp->h_length );
  unsigned short port = atoi(argv[2]);
  server.sin_port = htons( port );
  
  int n = atoi(argv[3]);
  int num_arr[n+1];

  for(int i = 0; i <= n; i++){
        // printf("%d\n",atoi(argv[i+3]));
        num_arr[i] = htonl(atoi(argv[i+3]));
        // printf("%d\n",ntohl(num_arr[i]));
  }
    
  //printf( "CLIENT: server address is %s\n", inet_ntoa( server.sin_addr ) );


  //printf( "CLIENT: Connected to %s (port %d)\n", hp->h_name, port);
  printf( "CLIENT: Connected to server\n");
  if ( connect( sd, (struct sockaddr *)&server, sizeof( server ) ) == -1 )
  {
    perror( "connect() failed" );
    return EXIT_FAILURE;
  }


  /* The implementation of the application protocol is below... */

  //char * msg = "why not change the world?";

  if(n == 1){
      printf( "CLIENT: Sending %d integer value\n",  n);
  }
  else{
     printf( "CLIENT: Sending %d integer values\n",  n);
  }

  int m = write( sd, num_arr, 4*(n+1) );    /* or send()/recv() */

  if ( m == -1 )
  {
    perror( "write() failed" );
    return EXIT_FAILURE;
  }

  int buffer;
  m = read( sd, &buffer, 4);    /* BLOCKING */

  if ( m == -1 )
  {
    perror( "read() failed" );
    return EXIT_FAILURE;
  }
  else if ( m == 0 )
  {
    printf( "CLIENT: Rcvd no data; also, server socket was closed\n" );
  }
  else  /* n > 0 */
  {
    //buffer[m] = '\0';    /* assume we rcvd text-based data */
    printf( "CLIENT: Rcvd response %d\n", ntohl(buffer) );
  }



  char buffer2[MAXBUFFER];
  m = read( sd, buffer2, MAXBUFFER-1);    /* BLOCKING */

  if ( m == -1 )
  {
    perror( "read() failed" );
    return EXIT_FAILURE;
  }
  else if ( m == 0 )
  {
    printf( "CLIENT: Rcvd no data; also, server socket was closed\n" );
  }
  else  /* n > 0 */
  {
    buffer2[m] = '\0';    /* assume we rcvd text-based data */
    printf( "CLIENT: Rcvd response \"%s\"\n", buffer2 );
  }

//   printf( "CLIENT: Disconnected from %s (port %d)\n", argv[1], port);
     printf( "CLIENT: Disconnected from server\n");
  close( sd );

  return EXIT_SUCCESS;
}
