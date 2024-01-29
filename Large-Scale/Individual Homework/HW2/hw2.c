#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool slash_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = count_check[3];
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    //if the input character has a slash in the file, add it to matched
    if(regex[regex_index] == '\\' && input_line[i] == regex[regex_index]){
        matched[len] = input_line[i];
        regex_index = regex_index + 1;
        one = true;
    }
    //if the input character has a period in the file, add it to matched
    else if(regex[regex_index] == '.' && input_line[i] == regex[regex_index]){
        matched[len] = input_line[i];
        regex_index = regex_index + 1;
        one = true;
    }
    if(regex[regex_index] == '\\'){
        if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
            for(i = i+1; i < strlen(input_line); i++){
                if(input_line[i] == regex[regex_index]){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
            regex_index = regex_index + 3;
        }
        else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
            one = true;
            for(i = i+1; i < strlen(input_line); i++){
                if(input_line[i] == regex[regex_index]){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
            regex_index = regex_index + 3;
        }
    }

    else if(regex[regex_index] == '.'){
        if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
            for(i = i+1; i < strlen(input_line); i++){
                if(input_line[i] == regex[regex_index]){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
            regex_index = regex_index + 3;
        }
        else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
            one = true;
            for(i = i+1; i < strlen(input_line); i++){
                if(input_line[i] == regex[regex_index]){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
            regex_index = regex_index + 3;
        }
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = len;
    return one;
}

bool space_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = count_check[3];
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    if(isspace(input_line[i])){
        matched[len] = input_line[i];
        one = true;
    }
    if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(isspace(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
        one = true;
        for(i = i+1; i < strlen(input_line); i++){
            if(isspace(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = len;
    return one;
}

bool digit_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    if(isdigit(input_line[i])){
        matched[len] = input_line[i];
        one = true;
    }
    if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(isdigit(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
        one = true;
        for(i = i+1; i < strlen(input_line); i++){
            if(isdigit(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    return one;
}

bool not_digit_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = count_check[3];
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    if(!(isdigit(input_line[i]))){
        matched[len] = input_line[i];
        one = true;
    }
    if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isdigit(input_line[i]))){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
        one = true;
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isdigit(input_line[i]))){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = len;
    return one;
}

bool alpha_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = count_check[3];
    // printf("%d\n",len);
    // printf("%s\n",matched);
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    if(isalpha(input_line[i])){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(isalpha(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
        one = true;
        for(i = i+1; i < strlen(input_line); i++){
            if(isalpha(input_line[i])){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = len;
    return one;
}

bool not_alpha_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = count_check[3];
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    if(!(isalpha(input_line[i]))){
        matched[len] = input_line[i];
        one = true;
    }
    if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isalpha(input_line[i]))){
                matched[len] = input_line[i];
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    else if(regex_index != strlen(regex)-1 && regex[regex_index+2] == '*'){
        one = true;
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isalpha(input_line[i]))){
                matched[len] = input_line[i];
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 3;
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = len;
    return one;
}


// void bracket_check(char * input_line, const char * regex, char * matched, int * count_check){
//     char * bracket_gang = malloc(256);
//     int regex_index = count_check[1];
//     int j = 0;
//     bool not = false;
//     if(regex[regex_index+1] == '^'){
//         not = true;
//         regex_index++;
//     }
//     while(regex[regex_index] != ']'){
//         bracket_gang[j] = regex[regex_index];
//         j++;
//         regex_index++;
//     }
//     bool one = false;
//     //bracket_gang[j] = ']';
//     char oof[2];
//     oof[1] = ']';
//     int k = 0;
//     while(k < j){
//         oof[0] = bracket_gang[k];
//         if(digit_check(input_line, oof, matched, count_check) == false){
//             if(not_digit_check(input_line, oof, matched, count_check) == false){
//                 if(alpha_check(input_line, oof, matched, count_check) == false){
//                     if(not_alpha_check(input_line, oof, matched, count_check) == false){
//                         if(space_check(input_line, oof, matched, count_check) == false){
//                             if(slash_check(input_line, oof, matched, count_check) == false){
                                
//                             } 
//                         } 
//                     } 
//                 } 
//             } 
//         } 
//     }
    
// }

int regex_match( const char * filename, const char * regex,char *** matches, int trim_to_match ){
    FILE *input = fopen(filename, "r");
    char input_line[256];
    //checks if the file can be opened
	if (!input) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }

    while (fgets(input_line, 256, input) != NULL){    
        char * matched = malloc(256);
        int index = 0;
        int input_len = strlen(input_line);
        int regex_index = 0;
        bool result = false;
        int len = 0;
        for(int i = 0; i < input_len; i++) {
            // printf("%d\n",len);
            // printf("%s\n",matched);
            // printf("%d\n",len);
            //printf("%d\n",strlen(matched));
            if((input_line[i] == regex[regex_index] || regex[regex_index] == '.') && input_line[i] != '\\' && input_line[i] !='?' && input_line[i] !='+' && input_line[i] !='*'){
                //printf("%d\n",0);
                if(regex_index == 0){
                    index = i;
                }
                matched[len] = input_line[i];
                len++;
                result = true;
                regex_index++;
            
            }
            //if the current regex character is '?' then increase then it checks the same input character against the next regex character
            else if(regex[regex_index] == '?'){
                regex_index++;
                i--;
            }
            //if the next regex character is '?' then increase then it checks the same input character against the regex character 2 ahead of the current 
            else if(regex[regex_index+1] == '?'){
                regex_index = regex_index + 2;
                i--;
            }
            //check if the regex is looking for a digit
            else if(regex[regex_index] == '\\' && regex[regex_index+1] == 'd'){
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                count_check[3] = len;
                result = digit_check(input_line, regex, matched, count_check);
                if (result == false){
                    i = count_check[2];
                    regex_index = 0;
                }
                len = count_check[3];
                i = count_check[0];
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
            }
            //check if the regex is looking for a non-digit
            else if(regex[regex_index] == '\\' && regex[regex_index+1] == 'D'){
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                result = not_digit_check(input_line, regex, matched, count_check);
                if (result == false){
                    i = count_check[2];
                    regex_index = 0;
                }
                
                
                i = count_check[0];
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
            }
            // //check if the regex is looking for an alpha character
            else if(regex[regex_index] == '\\' && regex[regex_index+1] == 'w'){
                
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                count_check[3] = len;
               // printf("%c\n",input_line[0]);
                result = alpha_check(input_line, regex, matched, count_check);
                if(result == false){
                    i = count_check[2];
                    regex_index = 0;
                    //printf("%d",i);
                }
                
                i = count_check[0];
                len = count_check[3];
                //printf("%d\n",count_check[0]);
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
                
            }
            // //check if the regex is looking for a non-alpha character
            else if(regex[regex_index] == '\\' && regex[regex_index+1] == 'W'){
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                result = not_alpha_check(input_line, regex, matched, count_check);
                if(result == false){
                    i = count_check[2];
                    regex_index = 0;
                }

                i = count_check[0];
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
            }
            // //check if the regex is looking for a space
            else if(regex[regex_index] == '\\' && regex[regex_index+1] == 's'){
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                result = space_check(input_line, regex, matched, count_check);
                if (result == false){
                    i = count_check[2];
                    regex_index = 0;
                }
                
                i = count_check[0];
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
            }
            //check if the regex character is '\'
            else if(regex[regex_index] == '\\'){
                if(regex_index == 0){
                    index = i;
                }
                int * count_check = malloc(256);
                count_check[0] = i;
                count_check[1] = regex_index;
                count_check[2] = index;
                result = slash_check(input_line, regex, matched, count_check);
                if(result == false){
                    i = count_check[2];
                    regex_index = 0;
                }
                
                
                i = count_check[0];
                regex_index = count_check[1];
                index = count_check[2];
                free(count_check);
            }

            //check if the regex character is '['
            // else if(regex[regex_index] == '['){
            //     if(regex_index == 0){
            //         index = i;
            //     }
            //     int * count_check = malloc(256);
            //     count_check[0] = i;
            //     count_check[1] = regex_index;
            //     count_check[2] = index;
            //     bracket_check(input_line, regex, matched, count_check);
            //     i = count_check[0];
            //     regex_index = count_check[1];
            //     index = count_check[2];
            //     free(count_check);
            // }

            else{
                // avoids looping between the same two characters
                //printf("%s\n","yerrrrr");
                if(index!=i-1){
                    i = index;
                }
                else{
                    index++;
                } 
                regex_index = 0;
            }
            //regex_word[regex_index] only is '\n' when matched is correct so it prints out the line and resest everything
            //printf("%c",regex[regex_index]);
            if (regex_index == strlen(regex)){
                printf("%s",input_line);
                //printf("%s\n",matched);
                //matched = malloc(256);
                len = 0;
                // printf("%s\n",matched);
                // printf("%d\n",strlen(matched));
                regex_index = 0;
                break;
            }
            else{
                if(result == false){
                    matched = malloc(256);
                }
                
            }
        }
        matched = malloc(256);
    }

    fclose(input);
    return 0;
}

int main(int argc, char* argv[]){
    //checks to make sure there are the right number of arguments
    if( argc != 4 ){
        fprintf( stderr, "ERROR: Invalid arguments\n" );
        fprintf( stderr, "USAGE: %s <regex-file> <input-file> <trim-to-match>\n", argv[0] );
        return EXIT_FAILURE;
    }

    FILE * regexfile = fopen( argv[1], "r" );

    if( regexfile == NULL ){
        perror( "fopen() failed" );
        return EXIT_FAILURE;
    }

    char * regex = NULL;
    char *** matches = malloc(256);

    if( fscanf( regexfile, "%m[^\n]", &regex ) != 1 ){
        free( regex );
        fprintf( stderr, "ERROR: regex file is incorrect\n" );
        return EXIT_FAILURE;
    }
    //printf("%s",regex);
    fclose( regexfile );

    regex_match(argv[2], regex, matches, *argv[3]);

    //fclose(input);
    free(matches);
}