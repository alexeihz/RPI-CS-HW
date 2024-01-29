#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void regex_check(char* input_line, char* regex_word){
    char * matched = malloc(256);
    int index = 0;
    int input_len = strlen(input_line);
    int regex_index = 0;
    //step through the input line character by character
    for(int i = 0; i < input_len; i++) {
        int len = strlen(matched);
        //checks for a character match between the input and regex or if the regex character is '.'
        if((input_line[i] == regex_word[regex_index] || regex_word[regex_index] == '.') && input_line[i] != '\\' && input_line[i] !='?' && input_line[i] !='+' && input_line[i] !='*'){
            if(regex_index == 0){
                index = i;
            }
            matched[len] = input_line[i];
            regex_index++;
            
        }
        //if the current regex character is '?' then increase then it checks the same input character against the next regex character
        else if(regex_word[regex_index] == '?'){
            regex_index++;
            i--;
        }
        //if the next regex character is '?' then increase then it checks the same input character against the regex character 2 ahead of the current 
        else if(regex_word[regex_index+1] == '?'){
            regex_index = regex_index + 2;
            i--;
        }
        //if the input is a '?'
        // else if (input_line[i-1] =='?' && regex_word[regex_index-1] == '?'){
        //     matched[len] = input_line[i];
        //     regex_index++;
        // }
        //check if the regex character is '\'
        else if(regex_word[regex_index] == '\\'){
            if(regex_index == 0){
                index = i;
            }
            //if the input character has a backslash in the file, add it to matched
            if(regex_word[regex_index+1] == '\\' && input_line[i] == regex_word[regex_index+1]){
                matched[len] = input_line[i];
                regex_index = regex_index + 2;
            }
            //if the input character has a period in the file, add it to matched
            else if(regex_word[regex_index+1] == '.' && input_line[i] == regex_word[regex_index+1]){
                matched[len] = input_line[i];
                regex_index = regex_index + 2;
            }
            //check if the regex is looking for a digit
            else if(regex_word[regex_index+1] == 'd'){
                //add the input character to matched if it is a digit
                if(isdigit(input_line[i])){
                    matched[len] = input_line[i];
                    regex_index = regex_index + 2;
                }
                //if the regex wants zero or more digits and there are zero digits, add the input character to matched
                else if(regex_word[regex_index+2] == '*'){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 3;
                }
                //reset the list and start again from the character after the one you began making matches at
                else{
                    i = index;
                    regex_index = 0;
                    matched = malloc(256);
                }
            }
            //check if the regex is looking for a non-digit
            else if(regex_word[regex_index+1] == 'D'){
                //add the input character to matched if it is a non-digit
                if(!(isdigit(input_line[i]))){
                    matched[len] = input_line[i];
                    regex_index = regex_index + 2;
                }
                //if the regex wants zero or more non-digits and there are zero non-digits, add the input character to matched
                else if(regex_word[regex_index+2] == '*'){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 3;
                }
                //reset the list and start again from the character after the one you began making matches at
                else{
                    i = index;
                    regex_index = 0;
                    matched = malloc(256);
                }
            }
            //check if the regex is looking for an alpha character
            else if(regex_word[regex_index+1] == 'w'){
                //add the input character to matched if it is an alpha character
                if(isalpha(input_line[i])){
                    matched[len] = input_line[i];
                    regex_index = regex_index + 2;
                }
                //if the regex wants zero or more alpha characters and there are zero alpha characters, add the input character to matched
                else if(regex_word[regex_index+2] == '*'){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 3;
                }
                //reset the list and start again from the character after the one you began making matches at
                else{
                    i = index;
                    regex_index = 0;
                    matched = malloc(256);
                }
            }
            //check if the regex is looking for a non-alpha character
            else if(regex_word[regex_index+1] == 'W'){
                //add the input character to matched if it is a non-alpha character
                if(!(isalpha(input_line[i]))){
                    matched[len] = input_line[i];
                    regex_index = regex_index + 2;
                }
                //if the regex wants zero or more non-alpha characters and there are zero non-alpha characters, add the input character to matched
                else if(regex_word[regex_index+2] == '*'){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 3;
                }
                //reset the list and start again from the character after the one you began making matches at
                else{
                    i = index;
                    regex_index = 0;
                    matched = malloc(256);
                }
            }
            //check if the regex is looking for a space
            else if(regex_word[regex_index+1] == 's'){
                //add the input character to matched if it is a space
                if(isspace(input_line[i])){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 2;
                }
                //if the regex wants zero or more spaces and there are zero spaces, add the input character to matched
                else if(regex_word[regex_index+2] == '*'){
                    matched[len] = input_line[i];
                    i--;
                    regex_index = regex_index + 3;
                }
                //reset the list and start again from the character after the one you began making matches at
                else{
                    i = index;
                    regex_index = 0;
                    matched = malloc(256);
                }
            }
            //if the regex wants zero or more backslashs and there are zero backslashs, add the input character to matched
            else if(regex_word[regex_index+2] == '*'){
                matched[len] = input_line[i];
                i--;
                regex_index = regex_index + 3;
            }
            //reset the list and start again from the character after the one you began making matches at
            else{
                i = index;
                regex_index = 0;
                matched = malloc(256);
            }
        }
        //check if the regex character is '+' or '*'
        else if(regex_word[regex_index] == '+' || regex_word[regex_index] == '*'){
            //if regex wants zero or more of any character, add the character to matched
            if(regex_index >= 1 && regex_word[regex_index-1] == '.'){
                matched[len] = input_line[i];
                //if the following regex character is equal to the current input line, increase the regex_index by 2
                if(strlen(regex_word) > 2 &&  regex_word[regex_index+1] == input_line[i]){
                    regex_index = regex_index + 2;
                }
            }
            //checks if regex wants 1 or more of an alpha character
            else if(regex_index >= 2 && regex_word[regex_index-1] == 'w' && regex_word[regex_index-2] == '\\'){
                //add the input character to matched if it is an alpha character
                if(isalpha(input_line[i]) != 0){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is an alpha character, then add 1 to regex and i--
                    if(isalpha(matched[len-1])){
                        i--;
                        regex_index++;
                    }
                }
            }
            //checks if regex wants 1 or more of a non-alpha character
            else if(regex_index >= 2 && regex_word[regex_index-1] == 'W' && regex_word[regex_index-2] == '\\'){
                //add the input character to matched if it is a non-alpha character
                if(isalpha(input_line[i]) == 0){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is a non-alpha character, then add 1 to regex and i--
                    if(isalpha(matched[len-1]) == 0){
                        i--;
                        regex_index++;
                    }
                }
            }
            //checks if regex wants 1 or more of a digit
            else if(regex_index >= 2 && regex_word[regex_index-1] == 'd' && regex_word[regex_index-2] == '\\'){
                //add the input character to matched if it is a digit
                if(isdigit(input_line[i]) != 0){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is a digit, then add 1 to regex and i--
                    if(isdigit(matched[len-1])){
                        i--;
                        regex_index++;
                    }
                }
            }
            //checks if regex wants 1 or more of a non-digit
            else if(regex_index >= 2 && regex_word[regex_index-1] == 'D' && regex_word[regex_index-2] == '\\'){
                //add the input character to matched if it is a non-digit
                if(isdigit(input_line[i]) == 0){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is a non-digit, then add 1 to regex and i--
                    if(isdigit(matched[len-1]) == 0){
                        i--;
                        regex_index++;
                    }
                }
            }
            //checks if regex wants 1 or more spaces
            else if(regex_index >= 2 && regex_word[regex_index-1] == 's' && regex_word[regex_index-2] == '\\'){
                //add the input character to matched if it is a space
                if(isspace(input_line[i])){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is a space, then add 1 to regex and i--
                    if(isspace(matched[len-1])){
                        i--;
                        regex_index++;
                    }
                }
            }
            ////checks if regex wants 1 or more of the same character
            else{
                //add the input character to matched if it is the same as the regex character
                if(input_line[i] == regex_word[regex_index-1]){
                    matched[len] = input_line[i];
                }
                else{
                    //if the previous matched character is the same as the regex character, then add 1 to regex and i--
                    if(matched[len-1] == regex_word[regex_index-1]){
                        i--;
                        regex_index++;
                    }
                }
            }

        }
        //none of the situations match
        else{
            // avoids looping between the same two characters
            if(index!=i-1){
                i = index;
            }
            else{
                index++;
            } 
            regex_index = 0;
            matched = malloc(256);
        }
        //regex_word[regex_index] only is '\n' when matched is correct so it prints out the line and resest everything
        if (regex_word[regex_index] == '\n'){
            printf("%s",input_line);
            matched = malloc(256);
            regex_index = 0;
            break;
        }
    }
    free(matched);
}

int main(int argc, char* argv[]){
    //checks to make sure there are the right number of arguments
    if(argc != 3){
		fprintf(stderr, "ERROR: Invalid arguments.\nUSAGE: a.out <regex-file> <input-file>");
        return EXIT_FAILURE;
	}

    FILE *input;
    FILE *regex;
    char input_line[256];
    char regex_line[256];
    

	regex = fopen(argv[1], "r");
    //checks if the file can be opened
	if (!regex) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }

	input = fopen(argv[2], "r");
    //checks if the file can be opened
	if (!input) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }
    //read the regex file
    fgets(regex_line,256,regex);
    //read the input file line by line
    while (fgets(input_line, 256, input) != NULL){    
        regex_check(input_line, regex_line);  
    }
    fclose(input);
    fclose(regex);
}