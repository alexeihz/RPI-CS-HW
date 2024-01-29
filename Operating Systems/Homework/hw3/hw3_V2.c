#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

extern int next_thread_id;
extern int max_squares;
extern char *** dead_end_boards; //= calloc( 8, sizeof( char ** ) );

int rows, cols, dead = 0;

struct ez_Struct{
    char ** board;
    int curr_row, curr_col, thread_num, move_count, S_count;
};

struct ez_Struct ez_struct_1[100];

void * board_thread(void * arg){
    int * pain = calloc( 1, sizeof( int ) );
    struct ez_Struct *struct_ptr = (struct ez_Struct*) arg;
    //int *start_boards = (int *)arg;
    int rc;
    int movecount = struct_ptr -> move_count;
    int threadnum = struct_ptr -> thread_num;
    //char *** board_state;
    int Scount = struct_ptr -> S_count;
    char board_state[8][rows][cols];
    int curr_row = struct_ptr -> curr_row;
    int curr_col = struct_ptr -> curr_col;
    int new_curr_row[8];
    int new_curr_col[8];
    struct_ptr -> board[curr_row][curr_col] = 'S';
    for(int j = 0; j < rows; j++){
        if(j == 0){
            printf("THREAD %d: >>", threadnum);
        }
        else{
            printf("THREAD %d:   ", threadnum);
        }
        for(int k = 0; k < cols; k++){
            printf( "%c",  struct_ptr -> board[j][k]);
        }
        if(j == rows-1){
            printf("<<");
        }
        printf("\n");
    }


    while(1){
        // printf("yerr\n");
        int threads_needed = 0;
        if(curr_row - 2 >= 0 && curr_col - 1 >= 0 && struct_ptr -> board[curr_row - 2][curr_col - 1] != 'S'){
            new_curr_row[threads_needed] = curr_row - 2;
            new_curr_col[threads_needed] = curr_col - 1;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }
        if(curr_row - 2 >= 0 && curr_col + 1 < cols && struct_ptr -> board[curr_row - 2][curr_col + 1] != 'S'){
            new_curr_col[threads_needed] = curr_col + 1;
            new_curr_row[threads_needed] = curr_row - 2;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row-2][curr_col+1] = 'S';
            threads_needed++;
            
        }
        if(curr_row + 2 < rows && curr_col - 1 >= 0 && struct_ptr -> board[curr_row + 2][curr_col - 1] != 'S'){
            new_curr_col[threads_needed] = curr_col - 1;
            new_curr_row[threads_needed] = curr_row + 2;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }
        if(curr_row + 2 < rows && curr_col + 1 < cols && struct_ptr -> board[curr_row + 2][curr_col + 1] != 'S'){
            new_curr_col[threads_needed] = curr_col + 1;
            new_curr_row[threads_needed] = curr_row + 2;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }

        if(curr_row - 1 >= 0 && curr_col - 2 >= 0 && struct_ptr -> board[curr_row - 1][curr_col - 2] != 'S'){
            new_curr_row[threads_needed] = curr_row - 1;
            new_curr_col[threads_needed] = curr_col - 2;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }
        if(curr_row - 1 >= 0 && curr_col + 2 < cols && struct_ptr -> board[curr_row - 1][curr_col + 2] != 'S'){
            new_curr_col[threads_needed] = curr_col + 2;
            new_curr_row[threads_needed] = curr_row - 1;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }
        if(curr_row + 1 < rows && curr_col - 2 >= 0 && struct_ptr -> board[curr_row + 1][curr_col - 2] != 'S'){
            new_curr_col[threads_needed] = curr_col - 2;
            new_curr_row[threads_needed] = curr_row + 1;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
            
        }
        if(curr_row + 1 < rows && curr_col + 2 < cols && struct_ptr -> board[curr_row + 1][curr_col + 2] != 'S'){
            new_curr_col[threads_needed] = curr_col + 2;
            new_curr_row[threads_needed] = curr_row + 1;
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < cols; k++){
                    board_state[threads_needed][j][k] = struct_ptr -> board[j][k];
                }
            }
            board_state[threads_needed][curr_row][curr_col] = 'S';
            threads_needed++;
        }
        pthread_t tid[threads_needed];
        if(threads_needed > 0){
            Scount++;
            if(threads_needed > 1){
                printf("THREAD %d: %d possible moves after move #%d; creating %d child threads...\n", threadnum, threads_needed, movecount, threads_needed);
                for ( int i = 1 ; i <= threads_needed ; i++ ){
                    
                    //ez_struct_1[next_thread_id-1].board = board_state[i-1];
                    ez_struct_1[next_thread_id-1].thread_num = next_thread_id;
                    ez_struct_1[next_thread_id-1].S_count = Scount;
                    ez_struct_1[next_thread_id-1].move_count = movecount;
                    ez_struct_1[next_thread_id-1].curr_row = new_curr_row[i-1];
                    ez_struct_1[next_thread_id-1].curr_col = new_curr_col[i-1];
                    
                    for(int j = 0; j < rows; j++){
                        for(int k = 0; k < cols; k++){
                            printf("%d\n", next_thread_id-1);
                            ez_struct_1[next_thread_id-1].board[j][k] = board_state[i-1][j][k];
                        }
                        
                    }
                    
                    rc = pthread_create(&tid[i],NULL,board_thread,&ez_struct_1[next_thread_id-1]);
                    if ( rc != 0 ){
                        fprintf( stderr, "pthread_create() failed (%d)\n", rc );
                    }
                    next_thread_id++;

                    // int * x;
                    // pthread_join(tid[i] , (void **)&x );   /* BLOCK */
                    // printf( "THREAD %d: Thread %d joined (returned %d)\n", threadnum, threadnum, *x);
                    
                    // free( x );
                        
                }

                for (int i = 1 ; i <= threads_needed ; i++ ){
                    int * x;
                    pthread_join(tid[i] , (void **)&x );   /* BLOCK */
                    printf( "THREAD %d: Thread %d joined (returned %d)\n", threadnum, threadnum, *x);
                    
                    free( x );
                }
            }
            else{
                struct_ptr -> curr_row = new_curr_row[threads_needed-1];
                struct_ptr -> curr_col = new_curr_col[threads_needed-1];
                struct_ptr -> board[new_curr_row[0]][new_curr_col[0]] = 'S';
                struct_ptr -> move_count++;
                
                curr_row = struct_ptr -> curr_row;
                curr_col = struct_ptr -> curr_col;
                for(int j = 0; j < rows; j++){
                    if(j == 0){
                        printf("THREAD %d: >>", threadnum);
                    }
                    else{
                        printf("THREAD %d:   ", threadnum);
                    }
                    for(int k = 0; k < cols; k++){
                        printf( "%c",  struct_ptr -> board[j][k]);
                    }
                    if(j == rows-1){
                        printf("<<");
                    }
                    printf("\n");
                }
                
            }

        }
        else{
            if(Scount < rows * cols){
                printf("THREAD %d: Dead end at move #%d\n", threadnum, movecount);
                dead_end_boards[dead] = struct_ptr -> board;
                dead++;
            }
            else{
                printf("THREAD %d: Sonny found a full knight's tour!\n", threadnum);
            }
            break;
        }
        movecount++;
    }
    *pain += Scount;
    if(*pain > max_squares){
        max_squares = *pain;
    }
    pthread_exit( pain );
}

int simulate(int argc, char * argv[]){
    
    int rc;
    int threads_needed = 0;
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    int startrow = atoi(argv[3]);
    int startcol = atoi(argv[4]);
    int space_limit = atoi(argv[5]);
    //int ** start_boards = calloc( 8, sizeof( int * ) ); //[startrow, startcol, curr_row, curr_col, rows, cols,thread_num,max_thread_num]


    printf("MAIN: Solving Sonny's knight's tour problem for a %dx%d board\n", rows, cols);
    printf("MAIN: Sonny starts at row %d and column %d\n", startrow, startcol);
    if(startrow + 1 < rows && startcol + 2 < cols){
        ez_struct_1[threads_needed].curr_row = startrow + 1;
        ez_struct_1[threads_needed].curr_col = startcol + 2;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 2 >= 0 && startcol - 1 >= 0){
        ez_struct_1[threads_needed].curr_row = startrow - 2;
        ez_struct_1[threads_needed].curr_col = startcol - 1;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 2 >= 0 && startcol + 1 < cols){
        ez_struct_1[threads_needed].curr_row = startrow - 2;
        ez_struct_1[threads_needed].curr_col = startcol + 1;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;  
    }
    if(startrow + 2 < rows && startcol - 1 >= 0){
        ez_struct_1[threads_needed].curr_row = startrow + 2;
        ez_struct_1[threads_needed].curr_col = startcol - 1;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow + 2 < rows && startcol + 1 < cols){
        ez_struct_1[threads_needed].curr_row = startrow + 2;
        ez_struct_1[threads_needed].curr_col = startcol + 1;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    
    if(startrow - 1 >= 0 && startcol - 2 >= 0){
        ez_struct_1[threads_needed].curr_row = startrow - 1;
        ez_struct_1[threads_needed].curr_col = startcol - 2;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 1 >= 0 && startcol + 2 < cols){
        ez_struct_1[threads_needed].curr_row = startrow - 1;
        ez_struct_1[threads_needed].curr_col = startcol + 2;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;  
    }
    if(startrow + 1 < rows && startcol - 2 >= 0){
        ez_struct_1[threads_needed].curr_row = startrow + 1;
        ez_struct_1[threads_needed].curr_col = startcol - 2;
        ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        for(int i = 0; i < rows; i++){
            ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
            for(int j = 0; j < cols; j++){
                ez_struct_1[threads_needed].board[i][j] = '.';
            }
        }
        ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    
    pthread_t tid[threads_needed];
    
    for(int j = 0; j < rows; j++){
        if(j == 0){
            printf("MAIN: >>");
        }
        else{
            printf("MAIN:   ");
        }
        for(int k = 0; k < cols; k++){
            printf( "%c",  ez_struct_1[threads_needed-1].board[j][k]);
        }
        if(j == rows-1){
            printf("<<");
        }
        printf("\n");
    }
    printf("MAIN: %d possible moves after move #1; creating %d child threads...\n", threads_needed, threads_needed);
    for(int j = 0; j < rows; j++){
        if(j == 0){
            printf("MAIN: >>");
        }
        else{
            printf("MAIN:   ");
        }
        for(int k = 0; k < cols; k++){
            printf( "%c",  ez_struct_1[threads_needed-1].board[j][k]);
        }
        if(j == rows-1){
            printf("<<");
        }
        printf("\n");
    }
    for (int i = 1 ; i <= threads_needed ; i++ ){
        ez_struct_1[next_thread_id-1].thread_num = next_thread_id;
        ez_struct_1[next_thread_id-1].S_count = 2;
        ez_struct_1[next_thread_id-1].move_count = 2;
        rc = pthread_create(&tid[i], NULL, board_thread, &ez_struct_1[i-1]);
        if ( rc != 0 ){
            fprintf( stderr, "pthread_create() failed (%d)\n", rc );
        }
        next_thread_id++;
    }


    for (int i = 1 ; i <= threads_needed ; i++ ){
        int * x;
        pthread_join( tid[i] , (void **)&x );   /* BLOCK */
        printf( "MAIN: Thread %d joined (returned %d)\n", i, *x);
        
        free( x );
    }

    if(max_squares == rows * cols){
        printf( "MAIN: All threads joined; full knight's tour of %d achieved\n", max_squares);
    }
    else{
        printf( "MAIN: All threads joined; best solution(s) visited %d squares out of %d\n", max_squares, rows * cols);
        printf( "MAIN: Dead end boards covering at least %d spaces are:\n", space_limit);
        for(int i = 0; i < dead; i++){
            for(int j = 0; j < rows; j++){
                if(j == 0){
                    printf("MAIN: >>");
                }
                else{
                    printf("MAIN:   ");
                }
                for(int k = 0; k < cols; k++){
                    printf( "%c",  dead_end_boards[i][j][k]);
                }
                if(j == rows-1){
                    printf("<<");
                }
                printf("\n");
            }
        }
    }
    for(int i = cols-1; i>=0; i--){
        free(ez_struct_1->board[i]);
    }
    free(ez_struct_1->board);
    return EXIT_SUCCESS;
}