#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void empty(char * matched){
    //empties a char array
    int len = strlen(matched);
    for(int i = len; i >= 0; i--){
        matched[i] = '\0';
    }
}

bool backslash_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1];
    bool one = false; 
    //if the input character has a backslash in the file, add it to matched
    if(regex[regex_index] == '\\' && input_line[i] == regex[regex_index]){
        matched[len] = input_line[i];
        regex_index = regex_index + 1;
        one = true;
        len++;
    }
    //if the input character has a period in the file, add it to matched
    else if(regex[regex_index] == '.' && input_line[i] == regex[regex_index]){
        matched[len] = input_line[i];
        regex_index = regex_index + 1;
        one = true;
        len++;
    }
    //if the regex character is a backslash, add to matched if the regex character that follows is a + or a *
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
    //if the regex character is a period, add to matched if the regex character that follows is a + or a *
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
    //else if one is false then 
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    return one;
}

bool space_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    //add the input character to matched if it is a space
    if(isspace(input_line[i])){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    //if the regex wants 1 or more spaces and there is already 1 space, add the input character to matched until no longer a space
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
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
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more spaces, add the input character to matched until no longer a space
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
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
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

bool not_space_check(char * input_line, const char * regex, char * matched, int * count_check){
    //add the input character to matched if it is not a space
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    if(!(isspace(input_line[i]))){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    //if the regex wants 1 or more non-spaces and there is already 1 non-space, add the input character to matched until no longer a non-space
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isspace(input_line[i]))){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more non-spaces, add the input character to matched until a space
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
            for(i = i+1; i < strlen(input_line); i++){
                if(!(isspace(input_line[i]))){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

bool digit_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    //add the input character to matched if it is a digit
    if(isdigit(input_line[i])){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    //if the regex wants 1 or more digits and there is already 1 digit, add the input character to matched until no longer a digit
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
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
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more digits, add the input character to matched until no longer a digit
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
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
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

bool not_digit_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    //add the input character to matched if it is a non-digit
    if(!(isdigit(input_line[i]))){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    //if the regex wants 1 or more non-digits and there is already 1 non-digit, add the input character to matched until no longer a digit
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
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
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more non-digits, add the input character to matched until no longer a non-digit
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
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
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    
    return one;
}

bool alpha_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    //add the input character to matched if it is a alpha character
    if(isalpha(input_line[i])){
        matched[len] = input_line[i];
        one = true;
        len++;
    }
    //if the regex wants 1 or more alpha characters and there is already 1 alpha character, add the input character to matched until no longer a alpha character
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
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
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more alpha characters, add the input character to matched until no longer a alpha character
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
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
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

bool not_alpha_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+2;
    bool one = false; 
    //add the input character to matched if it is a non-alpha character
    if(!(isalpha(input_line[i]))){
        
        matched[len] = input_line[i];
        len++;
        one = true;
    }
    //if the regex wants 1 or more non-alpha characters and there is already 1 non-alpha character, add the input character to matched until no longer a non-alpha character
    if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if(!(isalpha(input_line[i]))){
                matched[len] = input_line[i];
                len++;
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 1;
    }
    //if the regex wants 0 or more non-alpha characters, add the input character to matched until no longer a non-alpha character
    else if(regex_index-2 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
            for(i = i+1; i < strlen(input_line); i++){
                if(!(isalpha(input_line[i]))){
                    matched[len] = input_line[i];
                    len++;
                }
                else{
                    i--;
                    break;
                }
            }
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

bool basic_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    int i = count_check[0];
    int regex_index = count_check[1]+1;
    bool one = true; 
    matched[len] = input_line[i];
    len++;
    //if the regex wants 1 or more of any character and there is already 1 character, add the input character to matched
    if(regex_index-1 != strlen(regex)-1 && regex[regex_index] == '+' && one == true){
        for(i = i+1; i < strlen(input_line); i++){
            if((regex[regex_index-1] == '.')){
                matched[len] = input_line[i];
                len++;
                if(input_line[i] == regex[regex_index+1]){
                    regex_index = regex_index + 1;
                    break;
                }
            }
            else{
                i--;
                break;
            }
        }
        regex_index = regex_index + 1;
    }
    //if the regex wants 1 or more any character, add the input character to matched
    else if(regex_index-1 != strlen(regex)-1 && regex[regex_index] == '*'){
        if(one == false){
            one = true;
            i--;
        }
        else{
            for(i = i+1; i < strlen(input_line); i++){
                if((regex[regex_index-1] == '.') && input_line[i] != '\\' && input_line[i] !='?' && input_line[i] !='+' && input_line[i] !='*'){
                    matched[len] = input_line[i];
                    len++;
                    if(input_line[i] == regex[regex_index+1]){
                        regex_index = regex_index + 1;
                        break;
                    }
                }
                else{
                    i--;
                    break;
                }
            }
        }
        regex_index = regex_index + 1;
    }
    //reset the list and start again from the character after the one you began making matches at
    else if (one == false){
        if(count_check[2]!=i-1){
            i = count_check[2];
        }
        else{
            count_check[2]++;
        } 
        regex_index = 0;
        empty(matched);
    }
    count_check[0] = i;
    count_check[1] = regex_index;
    count_check[3] = one;
    return one;
}

void bracket_check(char * input_line, const char * regex, char * matched, int * count_check){
    int len = strlen(matched);
    char * bracket_gang = malloc(256);
    char * matched2 = malloc(256);
    char * oof = malloc(2);
    int regex_index = count_check[1]+1;
    int j = 0;
    bool one = false;
    bool mult = false;
    bool add = false;
    bool question = false;
    bool two = false;
    bool not = false;
    bool first = false;
    //check for the not character
    if(regex[regex_index] == '^'){
        not = true;
        regex_index++;
        
    }
    //get regex characters in brackets
    while(regex[regex_index] != ']'){
        bracket_gang[j] = regex[regex_index];
        j++;
        regex_index++;
    }
    regex_index++;
    //figure out if +.*, or ? is present
    if(regex[regex_index] == '+'){
        regex_index++;
        add = true;
        
    }
    else if(regex[regex_index] == '*'){
        mult = true;
        regex_index++;
    }
    else if(regex[regex_index] == '?'){
        question = true;
        regex_index++;
    }
    //loops until line ends
    while(count_check[0] < strlen(input_line)){
        int num = 0;
        two = false;
        //loops until the end of the bracket
        while (num < j){
            count_check[1] = 0;
            oof[0] = bracket_gang[num];
            if(bracket_gang[num] == '\\'){
                oof[1] = bracket_gang[num+1];
                num++;
            };
            //if there is only one char in oof, do a basic check
            if(strlen(oof) == 1){
                if((input_line[count_check[0]] == oof[0] || oof[0] == '.') && not == false){
                    if(basic_check(input_line, oof, matched2, count_check) && not == false){
                        
                        matched[len] = matched2[0];
                        len++;

                        if(one == true){
                            two = true;
                        }

                        if(two == false){
                            one = true;
                        }
                        break;
                    }       
                } 
                else if((input_line[count_check[0]] != oof[0] || oof[0] != '.') && not == true){
                    if(!(basic_check(input_line, oof, matched2, count_check)) == false && not == true){
                        matched[len] = matched2[0];
                        len++;
                        if(one == true){
                            two = true;
                        }

                        if(two == false){
                            one = true;
                        }
                        break;
                    }       
                }   
                     
            }
            else if(oof[0] == '\\' && oof[1] == 'd' && digit_check(input_line, oof, matched2, count_check) && not == false){   
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'd' && not_digit_check(input_line, oof, matched2, count_check) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'D' && not_digit_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'D' && digit_check(input_line, oof, matched2, count_check) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'w' && alpha_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }
                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'w' && not_alpha_check(input_line, oof, matched2, count_check) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'W' && not_alpha_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 'W' && alpha_check(input_line, oof, matched2, count_check) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 's' && space_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && oof[1] == 's' && not_space_check(input_line, oof, matched2, count_check) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && (oof[1] == '\\' || oof[1] == '.') && backslash_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if(oof[0] == '\\' && (oof[1] == '\\' || oof[1] == '.') && !(backslash_check(input_line, oof, matched2, count_check)) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if((input_line[count_check[0]] == oof[0] || oof[0] == '.') && basic_check(input_line, oof, matched2, count_check) && not == false){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else if((input_line[count_check[0]] == oof[0] || oof[0] == '.') && !(basic_check(input_line, oof, matched2, count_check)) && not == true){
                matched[len] = matched2[0];
                len++;
                if(one == true){
                    two = true;
                }

                if(two == false){
                    one = true;
                }
                break;
            }
            else{
                 
                
                count_check[1] = 0;
                empty(matched);
                
            }
            num++;
        }
        
        if(one == true && add == false && mult == false){
            
            break;
        }
        //if add is true, loop until no longer matches the requirements
        else if(add == true){
            if(one == false){
                empty(matched);
                empty(matched2);
                empty(oof);
                count_check[0] = count_check[2];
                count_check[0]++;
                break;
            }
            else if(one == true && two == false){
                
                if(first == false){
                    first = true;
                }
                else{
                    empty(matched2);
                    empty(oof);
                    
                    break;
                }
            }
        }
        //if mult is true, loop until no longer matches the requirements
        else if(mult == true){
            if(one == false){
                one = true;
                count_check[0]++;
                break;
            }
            if(one == true && two == false){
                if(first == false){
                    first = true;
                }
                else{
                    empty(matched2);
                    empty(oof);
                    
                    break;
                }
            }
        }
        //if question is true, break
        else if(question == true){
            if(one == false){
                count_check[0]++;
                break;
            }
            if(one == true){
                count_check[0]++;
                break;
            }
        }

        
        empty(matched2);
        empty(oof);
        
        count_check[0]++;
        
    }
    //resets
    if(one == false && mult == false && question == false){
        
        empty(matched2);
        empty(oof);
        empty(matched);
        
        count_check[0] = count_check[2];
        
        
    }
   
    count_check[3] = one;
    count_check[1] = regex_index;
}

int regex_match( const char * filename, const char * regex,char *** matches, int trim_to_match ){
    
    FILE *input = fopen(filename, "r");
    char input_line[256];
    //checks if the file can be opened
	if (!input) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }
    char * matched = malloc(256);
    int * count_check = malloc(5);
    while (fgets(input_line, 256, input) != NULL){    
        count_check[3] = false;
        count_check[2] = 0;
        int input_len = strlen(input_line);
        count_check[1] = 0;
        for(count_check[0] = 0; count_check[0] < input_len; count_check[0]++) {
            //if the current regex character is '?' then increase then it checks the same input character against the next regex character
            if(regex[count_check[1]] == '?'){
                count_check[1]++;
                count_check[0]--;
            }
            //if the next regex character is '?' then increase then it checks the same input character against the regex character 2 ahead of the current 
            else if(regex[count_check[1]+1] == '?'){
                count_check[1] = count_check[1] + 2;
                count_check[0]--;
            }
            //check if the regex is looking for a digit
            else if(regex[count_check[1]] == '\\' && regex[count_check[1]+1] == 'd'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                
                digit_check(input_line, regex, matched, count_check);
                
            }
            //check if the regex is looking for a non-digit
            else if(regex[count_check[1]] == '\\' && regex[count_check[1]+1] == 'D'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                
                not_digit_check(input_line, regex, matched, count_check);
                
            }
            // //check if the regex is looking for an alpha character
            else if(regex[count_check[1]] == '\\' && regex[count_check[1]+1] == 'w'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                
                alpha_check(input_line, regex, matched, count_check);
                
            }
            // //check if the regex is looking for a non-alpha character
            else if(regex[count_check[1]] == '\\' && regex[count_check[1]+1] == 'W'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                
                not_alpha_check(input_line, regex, matched, count_check);
                
            }
            // //check if the regex is looking for a space
            else if(regex[count_check[1]] == '\\' && regex[count_check[1]+1] == 's'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
               
                space_check(input_line, regex, matched, count_check);
                
                
               
            }
            //check if the regex character is '\'
            else if(regex[count_check[1]] == '\\'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
               
                backslash_check(input_line, regex, matched, count_check);
                
            }

            //check if the regex character is '['
            else if(regex[count_check[1]] == '['){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                bracket_check(input_line, regex, matched, count_check);
                
            }
            else if(input_line[count_check[0]] == regex[count_check[1]] || regex[count_check[1]] == '.'){
                if(count_check[1] == 0){
                    count_check[2] = count_check[0];
                }
                
                basic_check(input_line, regex, matched, count_check);
                
            }

            else{
                // avoids looping between the same two characters
                if(count_check[2]!=count_check[0]-1){
                    count_check[0] = count_check[2];
                }
                else{
                    count_check[2]++;
                } 
                count_check[1] = 0;
            }
            //prints 
            if (count_check[1] == strlen(regex) && count_check[3] == true){
                if(trim_to_match == 1){
                    printf("%s\n",matched);
                }
                else{
                    printf("%s",input_line);
                }
                empty(matched);
                count_check[1] = 0;
                break;
            }
        }
    }
    free(matched);
    free(count_check);
    fclose(input);
    return 0;
}


#ifndef USE_SUBMITTY_MAIN
int main( int argc, char * argv[] ){
    setvbuf(stdout, NULL, _IONBF, 0);
  if ( argc != 3 && argc != 4 )
  {
    fprintf( stderr, "ERROR: Invalid arguments\n" );
    fprintf( stderr, "USAGE: %s <regex-file> <input-file> [<trim-to-match>]\n", argv[0] );
    return EXIT_FAILURE;
  }

  FILE * regexfile = fopen( argv[1], "r" );

  if ( regexfile == NULL )
  {
    perror( "fopen() failed" );
    return EXIT_FAILURE;
  }

  char * regex = NULL;

  if ( fscanf( regexfile, "%m[^\n]", &regex ) != 1 )
  {
    free( regex );
    fprintf( stderr, "ERROR: regex file is incorrect\n" );
    return EXIT_FAILURE;
  }

  fclose( regexfile );

#ifdef DEBUG_MODE
  printf( "REGEX: \"%s\"\n", regex );
#endif


  /* call regex_match() to find matches of a given regex   */
  /*  in a given file (argv[2]); lines must be dynamically */
  /*   allocated in the regex_match() function call        */
  char ** lines = NULL;
  int trim_to_match = 0;
  if ( argc == 4 ) trim_to_match = ( atoi( argv[3] ) ? 1 : 0 );
  int matched_lines = regex_match( argv[2], regex, &lines, trim_to_match );

  free( regex );

  int i;

  /* display resulting matched lines */
  for ( i = 0 ; i < matched_lines ; i++ )
  {
    printf( "%s\n", lines[i] );
  }

  /* deallocate dynamically allocated memory */
  for ( i = 0 ; i < matched_lines ; i++ )
  {
    free( lines[i] );
  }

  free( lines );

  return EXIT_SUCCESS;
}
#endif