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

int rows, cols, dead = 0, space_limit;

struct ez_Struct{
    char ** board;
    int curr_row, curr_col, thread_num, move_count, S_count;
};

struct ez_Struct ez_struct_1[50];

void * board_thread(void * arg){
    //int check = next_thread_id;
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
    //printf( "%c\n",  struct_ptr -> board[1][2]);
    
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
            //printf("yerrr\n");
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
            //printf("yerrr\n");
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
            //printf("yerrr\n");
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
       
        pthread_t tid[threads_needed];
        if(threads_needed > 0){
            Scount++;
            if(threads_needed > 1){
                printf("THREAD %d: %d possible moves after move #%d; creating %d child threads...\n", threadnum, threads_needed, movecount, threads_needed);
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


                // for(int j = 0; j < rows; j++){
                //     if(j == 0){
                //         printf("THREAD %d?: >>", threadnum);
                //     }
                //     else{
                //         printf("THREAD %d?:   ", threadnum);
                //     }
                //     for(int k = 0; k < cols; k++){
                //         printf( "%c",  board_state[0][j][k]);
                //     }
                //     if(j == rows-1){
                //         printf("<<");
                //     }
                //     printf("\n");
                // }

                for ( int i = 1 ; i <= threads_needed ; i++ ){
                    
                    //ez_struct_1[next_thread_id-1].board = board_state[i-1];
                    //printf("%d\n",struct_ptr -> thread_num);
                    //printf("%d\n",next_thread_id);
                    ez_struct_1[next_thread_id].thread_num = struct_ptr -> thread_num+1;
                    ez_struct_1[next_thread_id].S_count = Scount;
                    ez_struct_1[next_thread_id].move_count = movecount;
                    ez_struct_1[next_thread_id].curr_row = new_curr_row[i-1];
                    ez_struct_1[next_thread_id].curr_col = new_curr_col[i-1];
                    
                    ez_struct_1[next_thread_id].board = calloc( rows, sizeof( char * ) );
                    for(int j = 0; j < rows; j++){
                        ez_struct_1[next_thread_id].board[j] = calloc( cols, sizeof( char ) );
                    }

                    for(int j = 0; j < rows; j++){
                        for(int k = 0; k < cols; k++){
                            //printf("%d\n", next_thread_id-1);
                            //ez_struct_1[next_thread_id-1].board[j][k] = board_state[i-1][j][k];
                            if(board_state[i-1][j][k] == 'S'){
                                //printf("yerrr\n");
                                ez_struct_1[next_thread_id].board[j][k] = 'S';
                                
                            }
                            else{
                                ez_struct_1[next_thread_id].board[j][k] = '.';
                            }
                        }
                        
                    }
                    
                    rc = pthread_create(&tid[i],NULL,board_thread,&ez_struct_1[next_thread_id]);
                    if ( rc != 0 ){
                        fprintf( stderr, "pthread_create() failed (%d)\n", rc );
                    }
                    

                    int * x;
                    pthread_join(tid[i] , (void **)&x );   /* BLOCK */
                    printf( "THREAD %d: Thread %d joined (returned %d)\n", threadnum, threadnum, *x);
                    
                    free( x );

                    next_thread_id++;
                        
                }

                // for (int i = 1 ; i <= threads_needed ; i++ ){
                //     int * x;
                //     pthread_join(tid[i] , (void **)&x );   /* BLOCK */
                //     printf( "THREAD %d: Thread %d joined (returned %d)\n", threadnum, threadnum, *x);
                    
                //     free( x );
                // }
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
                if(Scount >= space_limit){
                    dead_end_boards[dead] = struct_ptr -> board;
                    dead++;
                }
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
    return NULL;
}

int simulate(int argc, char * argv[]){
    
    int rc;
    int threads_needed = 0;
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    int startrow = atoi(argv[3]);
    int startcol = atoi(argv[4]);
    space_limit = atoi(argv[5]);
    int new_curr_row[8];
    int new_curr_col[8];
    //int start_boards[rows][cols]; //[startrow, startcol, curr_row, curr_col, rows, cols,thread_num,max_thread_num]

    if(rows < 2 || cols < 2 || startrow < 0 || startcol < 0 || startrow >= rows || startcol >= cols || space_limit > rows * cols){
        fprintf(stderr, "ERROR: Invalid argument(s)\nUSAGE: a.out <m> <n> <r> <c> <x>");
        return EXIT_FAILURE;
    }


    printf("MAIN: Solving Sonny's knight's tour problem for a %dx%d board\n", rows, cols);
    printf("MAIN: Sonny starts at row %d and column %d\n", startrow, startcol);
    
    if(startrow + 1 < rows && startcol + 2 < cols){
        new_curr_row[threads_needed] = startrow + 1;
        new_curr_col[threads_needed] = startcol + 2;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 2 >= 0 && startcol - 1 >= 0){
        new_curr_row[threads_needed] = startrow - 2;
        new_curr_col[threads_needed]= startcol - 1;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 2 >= 0 && startcol + 1 < cols){
        new_curr_row[threads_needed] = startrow - 2;
        new_curr_col[threads_needed]= startcol + 1;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;  
    }
    if(startrow + 2 < rows && startcol - 1 >= 0){
        new_curr_row[threads_needed] = startrow + 2;
        new_curr_col[threads_needed]= startcol - 1;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow + 2 < rows && startcol + 1 < cols){
        new_curr_row[threads_needed] = startrow + 2;
        new_curr_col[threads_needed]= startcol + 1;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    
    if(startrow - 1 >= 0 && startcol - 2 >= 0){
        new_curr_row[threads_needed] = startrow - 1;
        new_curr_col[threads_needed]= startcol - 2;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    if(startrow - 1 >= 0 && startcol + 2 < cols){
        new_curr_row[threads_needed] = startrow - 1;
        new_curr_col[threads_needed]= startcol + 2;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;  
    }
    if(startrow + 1 < rows && startcol - 2 >= 0){
        new_curr_row[threads_needed] = startrow + 1;
        new_curr_col[threads_needed]= startcol - 2;
        // ez_struct_1[threads_needed].board = calloc( rows, sizeof( char * ) );
        // for(int i = 0; i < rows; i++){
        //     ez_struct_1[threads_needed].board[i] = calloc( cols, sizeof( char ) );
        //     for(int j = 0; j < cols; j++){
        //         ez_struct_1[threads_needed].board[i][j] = '.';
        //     }
        // }
        // ez_struct_1[threads_needed].board[startrow][startcol] = 'S';
        threads_needed++;
    }
    
    
    pthread_t tid[threads_needed];
    if(threads_needed > 0){
        for(int j = 0; j < rows; j++){
            if(j == 0){
                printf("MAIN: >>");
            }
            else{
                printf("MAIN:   ");
            }
            for(int k = 0; k < cols; k++){
                
                if(j == startrow && k == startcol){
                    printf( "S" );
                }
                else{
                    printf( "." );
                }
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
                //printf( "%c",  ez_struct_1[threads_needed-1].board[j][k]);
                if(j == startrow && k == startcol){
                    printf( "S" );
                }
                else{
                    printf( "." );
                }
            }
            if(j == rows-1){
                printf("<<");
            }
            printf("\n");
        }
        for (int i = 1 ; i <= threads_needed ; i++ ){
            ez_struct_1[i-1].thread_num = i;
            ez_struct_1[i-1].S_count = 2;
            ez_struct_1[i-1].move_count = 2;
            ez_struct_1[i-1].curr_col = new_curr_col[i-1];
            ez_struct_1[i-1].curr_row = new_curr_row[i-1];
            ez_struct_1[i-1].board = calloc( rows, sizeof( char * ) );
            for(int j = 0; j < rows; j++){
                ez_struct_1[i-1].board[j] = calloc( cols, sizeof( char ) );
                for(int k = 0; k < cols; k++){
                    ez_struct_1[i-1].board[j][k] = '.';
                }
            }
            ez_struct_1[i-1].board[startrow][startcol] = 'S';
            ez_struct_1[i-1].board[new_curr_row[i-1]][new_curr_col[i-1]] = 'S';
            //printf("%d\n",next_thread_id);
            
            rc = pthread_create(&tid[i], NULL, board_thread, &ez_struct_1[i-1]);
            if ( rc != 0 ){
                fprintf( stderr, "pthread_create() failed (%d)\n", rc );
            }

            int * x;
            pthread_join( tid[i] , (void **)&x );   /* BLOCK */
            printf( "MAIN: Thread %d joined (returned %d)\n", i, *x);
            
            free( x );

            next_thread_id++;
            
        }


        // for (int i = 1 ; i <= threads_needed ; i++ ){
        //     int * x;
        //     pthread_join( tid[i] , (void **)&x );   /* BLOCK */
        //     printf( "MAIN: Thread %d joined (returned %d)\n", i, *x);
            
        //     free( x );
        // }
    }
    else{
        printf("MAIN: Dead end at move #1\n");
        max_squares = 1;
        ez_struct_1[0].board = calloc( rows, sizeof( char * ) );
        for(int j = 0; j < rows; j++){
            ez_struct_1[0].board[j] = calloc( cols, sizeof( char ) );
            for(int k = 0; k < cols; k++){
                ez_struct_1[0].board[j][k] = '.';
            }
        }
            ez_struct_1[0].board[startrow][startcol] = 'S';
        if(1 >= space_limit){
            dead_end_boards[dead] = ez_struct_1[0].board;
            dead++;
        }
    }


    if(max_squares == rows * cols){
        printf( "MAIN: All threads joined; full knight's tour of %d achieved\n", max_squares);
    }
    else{
        if(max_squares == 1){
            printf( "MAIN: All threads joined; best solution(s) visited %d square out of %d\n", max_squares, rows * cols);
        }
        else{
            printf( "MAIN: All threads joined; best solution(s) visited %d squares out of %d\n", max_squares, rows * cols);
        }

        if(space_limit == 1){
            printf( "MAIN: Dead end board covering at least %d square is:\n", space_limit);
        }
        else{
            printf( "MAIN: Dead end boards covering at least %d squares are:\n", space_limit);
        }
        
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
    // for(int i = cols-1; i>=0; i--){
    //     free(ez_struct_1->board[i]);
    // }
    // free(ez_struct_1->board);
    return EXIT_SUCCESS;
}