/* hw2.c */
/* NAME: Alexei Hazell */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("add  $%c%d,$%c%d,$%c%d\n",alpha1,num1,alpha2,num2,alpha3,num3);
}

void sub(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("sub  $%c%d,$%c%d,$%c%d\n",alpha1,num1,alpha2,num2,alpha3,num3);
}

int main( int argc, char * argv[] ){
  char line[256];

  printf("Please enter a valid C assignment statement:\n");
  if (fgets(line, 256, stdin) == NULL)
  {
    fprintf(stderr, "fgets() failed");
    return EXIT_FAILURE;
  }

  printf("The MIPS pseudocode is:\n");
  
	// Do your magic here
	int i = 0;
	int j = 0;
	int count = 0;
	int duplicate = 0;
	int mathcount = 0;
	char alpha[100];
	int alphacount = 0;
	char all[100];
	int zero = 0;
	int t = 0;
	int t2 = 0;
	int s = 0;
	int s2 = 0;
	int equals = 0;
	int first = 1;
	int mathcount2 =0;
	char sign;
	
	while(line[i] != ';'){
		if(isspace(line[i])){
			i++;
			continue;
		}
		else if(isdigit(line[i])){
			while(isdigit(line[i])){
				all[j] = line[i];
				i++;
				j++;
			}
		}
		
		else if(line[i] == '+' ||  line[i] == '-' || line[i] == '='){
			all[j] = line[i];
			i++;
			j++;
			mathcount++;
			if(line[i+1] == '+' ||  line[i+1] == '-' || line[i+1] == '=' ||  line[i+1] == ';'){
				fprintf( stderr, "Parsing error...\n" ); 
				return EXIT_FAILURE;
			}
		}
		
		else if(isalpha(line[i])){
			all[j] = line[i];
			if(!(islower(line[i]))){
				fprintf( stderr, "Parsing error...\n" ); 
				return EXIT_FAILURE;
			}
			while(count < alphacount){
				if(alpha[count] == line[i]){
					duplicate = 1;
					break;
				}	
				count++;				
			}
			if(duplicate==0){
				alpha[alphacount] = line[i];
				alphacount++;	
			}
			duplicate = 0;
			count = 0;
			i++;
			j++;
			
			
		}
		
		else{
			fprintf( stderr, "Parsing error...\n" ); 
			return EXIT_FAILURE;
		}
		
	}
	all[j] = ';';
	alpha[alphacount] = ';';
	i = 0;
	
	while(mathcount2 < mathcount-1){
		if(all[i] == '='){
			mathcount2++;
			equals = 1;
			i++;
		}
		
		if(equals == 1){
			if(first == 1){
				first = 0;
				if(isalpha(all[i])){
					while(alpha[s] != ';'){
						if(alpha[s] == all[i]){
							break;
						}
						s++;
					}
					i++;
					sign = all[i];
					i++;
					if(isalpha(all[i])){
						while(alpha[s2] != ';'){
							if(alpha[s2] == all[i]){
								break;
							}
							s2++;
						}
						if(sign == '-'){
							sub('t',t,'s',s,'s',s2);
						}
						if(sign == '+'){
							add('t',t,'s',s,'s',s2);
						}
					}
					else if(isdigit(all[i])){
						if(sign == '-'){
							printf("addi $t%d,$s%d,-",t,s);
							while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
								printf("%c",all[i]);
								i++;
							}
							i--;
							printf("\n");
						}
						if(sign == '+'){
							printf("addi $t%d,$s%d,",t,s);
							while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
								printf("%c",all[i]);
								i++;
							}
							i--;
							printf("\n");
						}
					}
					s2 = 0;
				}
				else if(isdigit(all[i])){
					zero = 1;
					printf("addi $t%d,$zero,",t);
					while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
						printf("%c",all[i]);
						i++;
					}
					mathcount2--;
					
					printf("\n");
				}
				
				
				s = 0;
			}
			else{
				t2 = t; 
				t++;
				sign = all[i];
				i++;
				if(isalpha(all[i])){
					while(alpha[s] != ';'){
						if(alpha[s] == all[i]){
							break;
						}
						s++;
					}
					if(sign == '-'){
						sub('t',t,'t',t2,'s',s);
					}
					if(sign == '+'){
						add('t',t,'t',t2,'s',s);
					}
					if(zero == 1){
						i++;
					}
				}
				else if(isdigit(all[i])){
					if(sign == '-'){
						printf("addi $t%d,$t%d,-",t,t2);
						while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
							printf("%c",all[i]);
							i++;
						}
						i--;
						printf("\n");
					}
					if(sign == '+'){
						printf("addi $t%d,$t%d,",t,t2);
						while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
							printf("%c",all[i]);
							i++;
						}
						i--;
						printf("\n");
					}
				}
			}
			s = 0;
			mathcount2++;
		}
		if(zero != 1){
			i++;
		}
	}
	sign = all[i];
	i++;
	if(isalpha(all[i])){
		while(alpha[s] != ';'){
			if(alpha[s] == all[i]){
				break;
			}
			s++;
		}
		if(sign == '-'){
			sub('s',0,'t',t,'s',s);
		}
		if(sign == '+'){
			add('s',0,'t',t,'s',s);
		}
	}
	else if(isdigit(all[i])){
		if(sign == '-'){
			printf("addi $s%d,$t%d,-",s,t);
			while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
				printf("%c",all[i]);
				i++;
			}
			i--;
			printf("\n");
		}
		if(sign == '+'){
			printf("addi $s%d,$t%d,",s,t);
			while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
				printf("%c",all[i]);
				i++;
			}
			i--;
			printf("\n");
		}
	}
  return EXIT_SUCCESS;
}
