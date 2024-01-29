#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void addition(char str1[],char str2[],char str3[]){
	
	printf("add %s,%s,%s\n",str1,str2,str3);
	
}

void subtraction(char str1[],char str2[],char str3[]){
	printf("sub %s,%s,%s\n",str1,str2,str3);
}


int main(){
	char str[100];
	int i;
	int j;
	int k;
	int counts = 0;
	int countt = 0;
	char character;
	char character2;
	char str2[100];
	char str3[100];
	int equals = 0;
	int exists = 0;
	char arg1[100];
	char arg2[100];
	char arg3[100];
	//char integer[10];
	int signs = 0;
	int signs2 = 0;
	char num[11] = "0123456789";
	int end = 0;
	i = 0;
	j = 0;
	k = 0;
	
	printf("Please enter a valid C assignment statement:\n");
	//scanf("%s", str);
	fgets(str,99,stdin);
	character2 = *(str+i);
	printf("The MIPS pseudocode is:\n");
	//printf("%s",str);
	while(character2 != '\0'){
		character2 = *(str+i);
		if(character2 != ' '){
			if(str[i] == '+' || str[i] == '-'){
				signs++;
				//printf("%d\n",signs);
			}
			if(isalpha(character2)){
				k=0;
				while(k<i){					
					if(str[k] == character2){
						exists = 1;
						k=0;
						break;
						
					}
					k++;
				}
				if(exists == 0){
					str3[counts] = character2;
					counts++;
				}
				exists = 0;
			}
			
			str2[j] = character2;
			j++;
		}
		
		i++;
	}
	str3[counts] = '\0';
	str2[j] = '\0';
	//printf("%s",str3);
	//printf("%s",str2);
	//printf("\n");
	
	//printf("%d",counts);
	//printf("%s",str3);
	//printf("\n");
	i = 0;
	j = 0;
	k = 0;
	
	character = str2[i];
	
	
	while(end != 1){
		
		if(character == '='){
			equals = 1;
			i++;
			character = *(str2+i);
			continue;
		}
		
		if(equals == 0){
			
			i++;
			character = *(str2+i);
			continue;
		}
		
		if(equals==1){
			while(signs2 < signs){
				if(character == '+'){
					
					
					if(signs2==0){
						if(isalpha(str2[i+1])){
							addition("$t0","$s1","$s2");
							signs2++;
							countt++;
						}
						if(isdigit(str2[i+1])){
							k = 0;
							j=i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
							j=0;
							k = 0;
							addition("$t0","$s1",arg2);
							signs2++;
							countt++;
						}
					}
					
					else if(signs2 == signs-1){
						arg1[0] = '$';
						arg1[1] = 't';
						arg1[2] = num[countt-1];
						//printf("%c",str2[i+1]);
						if(isdigit(str2[i+1])){
							// printf("%s",str3);
							// printf("\n");
							k = 0;
							j=i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
							j=0;
						}
						else if(isalpha(str2[i+1])){
							while(j<counts){
								if(str2[i+1] == str3[j]){
									arg2[0] = '$';
									arg2[1] = 's';
									arg2[2] = num[j];
								}
								j++;
							}
							j=0;
						}
						
						addition("$s0",arg1,arg2);
						end = 1;
						break;
					}
					
					else{
						
						arg1[0] = '$';
						arg1[1] = 't';
						arg1[2] = num[countt];
						if(isalpha(str2[i+1])){
							while(j<counts){
								if(str2[i-1] == str3[j]){
									arg2[0] = '$';
									arg2[1] = 's';
									arg2[2] = num[j];
								}
								j++;
							}
							j=0;
						}
						if(isdigit(str2[i+1])){
							k = 0;
							j = i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
						}
						arg3[0] = '$';
						arg3[1] = 't';
						arg3[2] = num[countt-1];
						addition(arg1,arg3,arg2);
						signs2++;
						countt++;
					}
				}
				
				else if(character == '-'){
					
					if(signs2==0){
						if(isalpha(str2[i+1])){
							subtraction("$t0","$s1","$s2");
							signs2++;
							countt++;
						}
						if(isdigit(str2[i+1])){
							k = 0;
							j=i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
							j=0;
							k = 0;
							subtraction("$t0","$s1",arg2);
							signs2++;
							countt++;
						}
					}
					else if(signs2 == signs-1){
						arg1[0] = '$';
						arg1[1] = 't';
						arg1[2] = num[countt-1];
						if(isalpha(str2[i+1])){
							while(j<counts){
								if(str2[i+1] == str3[j]){
									arg2[0] = '$';
									arg2[1] = 's';
									arg2[2] = num[j];
								}
								j++;
							}
							j=0;
						}
						if(isdigit(str2[i+1])){
							k = 0;
							j=i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
							j=0;
							k = 0;
						}
						
						subtraction("$s0",arg1,arg2);
						end = 1;
						break;
					}
					
					else{
						arg1[0] = '$';
						arg1[1] = 't';
						arg1[2] = num[countt];
						if(isalpha(str2[i+1])){
							while(j<counts){
								if(str2[i-1] == str3[j]){
									arg2[0] = '$';
									arg2[1] = 's';
									arg2[2] = num[j];
								}
								j++;
							}
							j=0;
						}
						if(isdigit(str2[i+1])){
							k = 0;
							j=i;
							while(isdigit(str2[j+1])){
								arg2[k] = str2[j+1];
								j++;
								k++;
							}
							arg2[k-1] = '\0';
							j = 0;
							k= 0;
						}
						arg3[0] = '$';
						arg3[1] = 't';
						arg3[2] = num[countt-1];
						subtraction(arg1,arg3,arg2);
						signs2++;
						countt++;
					}
				}
				i++;
				character = *(str2+i);
				//continue;
			}
		}
	}
	
	
	
	
	
	
	
	
	

}