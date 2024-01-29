#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    struct stat stats;
    int file, status;
    int count = 0;
    char buf;
    if(stat("data.txt", &stats) != 0){
        fprintf(stderr, "ERROR: stat() failed: No such file or directory\n");
        exit(EXIT_FAILURE);
    }
    int bytes = stats.st_size;
    int work = (bytes/atoi(argv[1]));
    
    int rc = fork();
    for(int i = 0; i< atoi(argv[1]); i++){
        if(rc == 0){
            int G_count = 0;
            int count2 = 0;
            int temp;
            file = open("data.txt", O_RDONLY);
            if(count == 0){
                lseek(file, count, SEEK_CUR);
            }
            else{
                lseek(file, count-1, SEEK_CUR);
            }
            count2 += count;
            if(i+1 == atoi(argv[1])){
                temp = bytes;
            }
            else{
                temp = count2 + work;
            }
            //temp = count2 + work;
            //printf("%d\n",count2);
            while(read(file,&buf,1) && count2 < temp-1){
                //printf("%s", argv[2]);
                if(buf == argv[2][0]){
                    //printf("%c", buf);
                    G_count++;
                }
                count2++;
            }
            if(G_count == 1){
                printf("Counted %d occurrence of \'%s\' in byte range %d-%d\n", G_count, argv[2],count,count2);
            }
            else{
                printf("Counted %d occurrences of \'%s\' in byte range %d-%d\n", G_count, argv[2],count,count2);
            }
            
            close(file);
            return EXIT_SUCCESS;
        }
        else{
            waitpid(rc, &status, 0 );
            count += work;
            rc = fork();
        }
    }
    return EXIT_SUCCESS;
}