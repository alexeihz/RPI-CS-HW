/* hw4.c */
/* NAME: Alexei Hazell */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void add(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("add $%c%d,$%c%d,$%c%d\n",alpha1,num1,alpha2,num2,alpha3,num3);
}

void sub(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("sub $%c%d,$%c%d,$%c%d\n",alpha1,num1,alpha2,num2,alpha3,num3);
}

void mult(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("mult $%c%d,$%c%d\n",alpha1,num1,alpha2,num2);
	printf("mflo $%c%d\n",alpha3,num3);
}

void divide(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("div $%c%d,$%c%d\n",alpha1,num1,alpha2,num2);
	printf("mflo $%c%d\n",alpha3,num3);
}

void divide2(char sign2, int power, int num, int L, char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("bltz $%c%d,L%d\n",alpha1,num1,L);
	printf("srl $%c%d,$%c%d,%c\n",alpha2,num2,alpha1,num1,power);
	if(sign2 == '-'){
		printf("sub $%c%d,$zero,$%c%d\n",alpha2,num2,alpha2,num2);
	}
	printf("j L%d\n",L+1);
	printf("L%d:\n",L);
	if(sign2 == '-'){
		printf("li $%c%d,%c%d\n",alpha3,num3,sign2,num);
	}
	else{
		printf("li $%c%d,%d\n",alpha3,num3,num);
	}
	divide(alpha1, num1, alpha3, num3, alpha2, num2);
	printf("L%d:\n",L+1);
}

void mod(char alpha1, int num1, char alpha2, int num2, char alpha3, int num3){
	printf("div $%c%d,$%c%d\n",alpha1,num1,alpha2,num2);
	printf("mfhi $%c%d\n",alpha3,num3);
}

void powersOfTwo(int num, char* powers){
	double power = 0;
	int sum = 0;
	int first;
	int result;
	int i = 0;
	while(sum < num){
		power = 0;
		first = 0;
		result = (int)pow(2,power);
		//printf("%d\n",num-sum);
		for(; result < num-sum; power++){
			result = (int)pow(2,power);
			//printf("%d\n",result);
			if(result > num-sum){
				result = (int)pow(2,power-1);
				break;
			}
			first = (int)power;
			//printf("%d\n",first);
		}
		sum += result;
		powers[i] = first + '0';
		i++;
		//printf("%s\n",powers);
	}
	powers[i] = ';';
	//printf("%s\n",powers);
}

int main( int argc, char * argv[] ){
  char line[256];
  FILE *fp;
  fp = fopen(argv[1], "r");
  //fscanf(fp, "%s", line);
  // fgets(line,255,(FILE*)fp);
  // printf("%s",line);
  // fgets(line,255,(FILE*)fp);
  // printf("%s",line);
  //printf("Please enter a valid C assignment statement:\n");
  // if (fgets(line, 256, stdin) == NULL)
  // {
    // fprintf(stderr, "fgets() failed");
    // return EXIT_FAILURE;
  // }

  //printf("The MIPS pseudocode is:\n");
  
	// Do your magic here
	char alpha[100];
	int alphacount = 0;
	int t = 0;
	int t2 = 0;
	int L = 0;
	
	while(fgets(line,255,(FILE*)fp) != NULL){
		int i = 0;
		int j = 0;
		int num;
		int count = 0;
		int duplicate = 0;
		int mathcount = 0;
		char all[100];
		int zero = 0;
		int s = 0;
		int s2 = 0;
		int s3 = 0;
		int equals = 0;
		int first = 1;
		int mathcount2 = 0;
		char sign;
		char sign2 = '+';
		char sign3;
		char str[5];
		char powers[9];
		
		printf("# ");
		while(line[i] != ';'){
			printf("%c",line[i]);
			i++;
		}
		printf(";\n");
		i = 0;
		while(line[i] != ';'){
			//printf("%c",line[i]);
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
			
			else if(line[i] == '+' ||  line[i] == '-' || line[i] == '=' || line[i] == '*' || line[i] == '/' || line[i] == '%'){
				all[j] = line[i];
				if(line[i] == '*' || line[i] == '/' || line[i] == '='){
					if(line[i+2] == '-'){
						mathcount--;
					}
				}
				i++;
				j++;
				mathcount++;
				
				// if(line[i+1] == '+' ||  line[i+1] == '-' || line[i+1] == '=' ||  line[i+1] == ';' || line[i+1] == '*' || line[i+1] == '/'){
					// fprintf( stderr, "Parsing error...\n" ); 
					// return EXIT_FAILURE;
				// }
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
			
			// else{
				// fprintf( stderr, "Parsing error...\n" ); 
				// return EXIT_FAILURE;
			// }
			
		}
		all[j] = ';';
		alpha[alphacount] = ';';
		i = 0;
		
		if(mathcount == 1){
			while(alpha[s] != ';'){
				if(alpha[s] == all[i]){
					break;
				}
				s++;
			}
			printf("li $s%d,",s);
			i = 2;
			while(all[i] != ';'){
				printf("%c",all[i]);
				i++;
			}
			printf("\n");
			continue;
		}
		
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
						sign3 = sign;
						i++;
						if(all[i] == '-'){
							sign2 = all[i];
							i++;
						}
						if(isalpha(all[i])){
							while(alpha[s2] != ';'){
								if(alpha[s2] == all[i]){
									break;
								}
								s2++;
							}
							while(alpha[s3] != ';'){
								if(alpha[s3] == all[0]){
									break;
								}
								s3++;
							}
							if(mathcount == 2){
								if(sign == '-'){
									sub('s',s3,'s',s,'s',s2);
								}
								if(sign == '+'){
									add('s',s3,'s',s,'s',s2);
								}
								if(sign == '*'){
									mult('s',s,'s',s2,'s',s3);
								}
								if(sign == '/'){
									divide('s',s,'s',s2,'s',s3);
								}
								if(sign == '%'){
									mod('s',s,'s',s2,'s',s3);
								}
							}
							else{
								if(sign == '-'){
									sub('t',t,'s',s,'s',s2);
								}
								if(sign == '+'){
									add('t',t,'s',s,'s',s2);
								}
								if(sign == '*'){
									mult('s',s,'s',s2,'t',t);
									//t--;
								}
								if(sign == '/'){
									divide('s',s,'s',s2,'t',t);
									//t--;
								}
								if(sign == '%'){
									mod('s',s,'s',s2,'t',t);
								}
							}
						}
						else if(isdigit(all[i])){
							if(sign == '*'){
								if(mathcount == 2){
									j = 0;
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										str[j] = all[i];
										i++;
										j++;
									}
									j = 0;
									i--;
									s2 = 0;
									while(alpha[s2] != ';'){
										if(alpha[s2] == all[0]){
											break;
										}
										s2++;
									}
									num = atoi(str);
									if(num == 0){
										printf("li $s%d,0\n",s2);
									}
									if(num == 1){
										if(sign2 == '-'){
											printf("move $t%d,$s%d\n",t,s);
											printf("sub $s%d,$zero,$t%d\n",s2,t);
											t++;
											continue;
										}
										else{
											printf("move $t%d,$s%d\n",t,s);
											printf("move $s%d,$t%d\n",s2,t);
											t++;
											continue;
										}
										
									}
									powersOfTwo(num,powers);
									printf("sll $t%d,$s%d,%c\n",t,s,powers[0]);
									printf("move $t%d,$t%d\n",t+1,t);
									int a = 1;
									while(powers[a] != '0' && powers[a] != ';'){
										printf("sll $t%d,$s%d,%c\n",t,s,powers[a]);
										add('t',t+1,'t',t+1,'t',t);
										a++;
									}
									add('t',t+1,'t',t+1,'s',s);
									
									if(sign2 == '-'){
										printf("sub $s%d,$zero,$t%d\n",s2,t+1);
									}
									else{
										printf("move $s%d,$t%d\n",s2,t+1);
									}
									//t++;
								}
								else{
									j = 0;
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										str[j] = all[i];
										i++;
										j++;
									}
									j = 0;
									i--;
									s2 = 0;
									while(alpha[s2] != ';'){
										if(alpha[s2] == all[0]){
											break;
										}
										s2++;
									}
									num = atoi(str);
									if(num == 0){
										printf("li $t%d,0\n",t);
									}
									if(num == 1){
										if(sign2 == '-'){
											printf("move $t%d,$s%d\n",t,s);
											printf("sub $t%d,$zero,$t%d\n",t+1,t);
											t++;
											continue;
										}
										else{
											printf("move $t%d,$s%d\n",t,s);
											printf("move $t%d,$t%d\n",t+1,t);
											t++;
											continue;
										}
										
									}
									powersOfTwo(num,powers);
									printf("sll $t%d,$s%d,%c\n",t,s,powers[0]);
									printf("move $t%d,$t%d\n",t+1,t);
									int a = 1;
									while(powers[a] != '0' && powers[a] != ';'){
										printf("sll $t%d,$s%d,%c\n",t,s,powers[a]);
										add('t',t+1,'t',t+1,'t',t);
										a++;
									}
									add('t',t+1,'t',t+1,'s',s);
									
									if(sign2 == '-'){
										printf("sub $t%d,$zero,$t%d\n",t+2,t+1);
									}
									else{
										printf("move $t%d,$t%d\n",t+2,t+1);
									}
									//t++;
									
									
									
								}
							}
							else if(sign == '/'){
								j = 0;
								while(all[i] != '-' && all[i] != '+' && all[i] != '*' && all[i] != '%' && all[i] != '/' && all[i] != ';'){
									str[j] = all[i];
									i++;
									j++;
								}
								j = 0;
								i--;
								//printf("%c", all[i]);
								s2 = 0;
								while(alpha[s2] != ';'){
									if(alpha[s2] == all[0]){
										break;
									}
									s2++;
								}
								num = atoi(str);
								if(mathcount == 2){
									if(num == 1){
										if(sign2 == '-'){
											printf("sub $s%d,$zero,$s%d\n",s2,s);
											continue;
										}
										else{
											printf("move $s%d,$s%d\n",s2,s);
											continue;
										}
										
									}
									else{
										powersOfTwo(num,powers);
										//printf("%d",powers[0]);
										if(powers[1] != ';'){
											if(sign2 == '-'){
												printf("li $t%d,-%d\n",t,num);
											}
											else{
												printf("li $t%d,%d\n",t,num);
											}
											if(sign == '/'){
												divide('s',s,'t',t,'t',t+1);
											}
										}
										else{
											//printf("%d",powers[0]);
											divide2(sign2,powers[0],num,L,'s',s,'s',s2,'t',t);
											L = L + 2;
											t++;
										}
									}
								}
								else{
									if(num == 1){
										if(sign2 == '-'){
											printf("sub $t%d,$zero,$s%d\n",t,s);
										}
										else{
											printf("move $t%d,$s%d\n",t,s);
										}
									}
									else{
										powersOfTwo(num,powers);
										if(powers[1] != ';'){
											if(sign2 == '-'){
												printf("li $t%d,-%d\n",t,num);
											}
											else{
												printf("li $t%d,%d\n",t,num);
											}
											if(sign == '/'){
												divide('s',s,'t',t,'t',t+1);
											}
										}
										else{
											divide2(sign2,powers[0],num,L,'s',s,'s',s2,'t',t);
											L = L + 2;
											t++;
										}
									}
								}
							}
							else if(sign == '-'){
								if(mathcount == 2){
									s2 = 0;
									while(alpha[s2] != ';'){
										if(alpha[s2] == all[0]){
											break;
										}
										s2++;
									}
									printf("addi $s%d,$s%d,-",s2,s);
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										printf("%c",all[i]);
										i++;
									}
									printf("\n");
								}
								else{
									printf("addi $t%d,$s%d,-",t,s);
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										printf("%c",all[i]);
										i++;
									}
									i--;
									printf("\n");
								}
							}
							else if(sign == '+'){
								if(mathcount == 2){
									s2 = 0;
									while(alpha[s2] != ';'){
										if(alpha[s2] == all[0]){
											break;
										}
										s2++;
									}
									printf("addi $s%d,$s%d,",s2,s);
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										printf("%c",all[i]);
										i++;
									}
									printf("\n");
								}
								else{
									printf("addi $t%d,$s%d,",t,s);
									while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
										printf("%c",all[i]);
										i++;
									}
									i--;
									printf("\n");
								}
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
					sign3 = sign;
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
						if(sign == '*'){
							if(sign3 == '*'){
								mult('t',t-1,'s',s,'t',t);
							}
							else{
								mult('t',t,'s',s,'t',t+1);
							}
						}
						if(sign == '/'){
							if(sign3 == '/'){
								divide('t',t-1,'s',s,'t',t);
							}
							else{
								divide('t',t,'s',s,'t',t+1);
							}
						}
						if(sign == '%'){
							if(sign3 == '%'){
								mod('t',t-1,'s',s,'t',t);
							}
							mod('t',t,'s',s,'t',t+1);
						}
						if(zero == 1){
							i++;
						}
					}
					else if(isdigit(all[i])){
						if(sign == '/'){
							j = 0;
							while(all[i] != '-' && all[i] != '+' && all[i] != '*' && all[i] != '%' && all[i] != '/' && all[i] != ';'){
								str[j] = all[i];
								i++;
								j++;
							}
							j = 0;
							i--;
							//printf("%c", all[i]);
							s2 = 0;
							while(alpha[s2] != ';'){
								if(alpha[s2] == all[0]){
									break;
								}
								s2++;
							}
							if(num == 1){
								if(sign2 == '-'){
									printf("sub $t%d,$zero,$s%d\n",t,s);
								}
								else{
									printf("move $t%d,$s%d\n",t,s);
								}
							}
							else{
								powersOfTwo(num,powers);
								if(powers[1] != ';'){
									if(sign2 == '-'){
										printf("li $t%d,-%d\n",t,num);
									}
									else{
										printf("li $t%d,%d\n",t,num);
									}
									if(sign == '/'){
										divide('s',s,'t',t,'t',t+1);
									}
								}
								else{
									divide2(sign2,powers[0],num,L,'s',s,'s',t2,'t',t);
									L = L + 2;
									t++;
								}
							}
						}
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
				s2 = 0;
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
			while(alpha[s2] != ';'){
				if(alpha[s2] == all[0]){
					break;
				}
				s2++;
			}
			if(sign == '-'){
				sub('s',s2,'t',t,'s',s);
			}
			if(sign == '+'){
				add('s',s2,'t',t,'s',s);
			}
			if(sign == '*'){
				mult('t',t,'s',s,'s',s2);
			}
			if(sign == '/'){
				divide('t',t,'s',s,'s',s2);
			}
			if(sign == '%'){
				mod('t',t,'s',s,'s',s2);
			}
		}
		else if(isdigit(all[i])){
			s2 = 0;
			while(alpha[s2] != ';'){
				if(alpha[s2] == all[0]){
					break;
				}
				s2++;
			}
			if(sign == '*'){
				char str[5];
				j = 0;
				while(all[i] != '-' && all[i] != '+' && all[i] != '*' && all[i] != '%' && all[i] != '/' && all[i] != ';'){
					str[j] = all[i];
					i++;
					j++;
				}
				j = 0;
				i--;
				//printf("%s",str);
				num = atoi(str);
				//printf("%d",num);
				if(num == 0){
					printf("li $s%d,0\n",s2);
				}
			}
			else if(sign == '/'){
				char str[5];
				j = 0;
				while(all[i] != '-' && all[i] != '+' && all[i] != '*' && all[i] != '%' && all[i] != '/' && all[i] != ';'){
					str[j] = all[i];
					i++;
					j++;
				}
				j = 0;
				i--;
				//printf("%s",str);
				num = atoi(str);
				if(num == 1){
					if(sign2 == '-'){
						printf("sub $t%d,$zero,$s%d\n",t,s);
					}
					else{
						printf("move $t%d,$s%d\n",t,s);
					}
				}
				else{
					powersOfTwo(num,powers);
					if(powers[1] != ';'){
						if(sign2 == '-'){
							printf("li $t%d,-%d\n",t,num);
						}
						else{
							printf("li $t%d,%d\n",t,num);
						}
						if(sign == '/'){
							divide('s',s,'t',t,'t',t+1);
						}
					}
					else{
						divide2(sign2,powers[0],num,L,'t',t,'s',s2,'t',t+1);
						L = L + 2;
						t++;
					}
				}
				
			}
			else if(sign == '-'){
				printf("addi $s%d,$t%d,-",s2,t);
				while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
					printf("%c",all[i]);
					i++;
				}
				i--;
				printf("\n");
			}
			else if(sign == '+'){
				printf("addi $s%d,$t%d,",s2,t);
				while(all[i] != '-' && all[i] != '+' && all[i] != ';'){
					printf("%c",all[i]);
					i++;
				}
				i--;
				printf("\n");
			}
		}
	}
	fclose(fp);
  return EXIT_SUCCESS;
}
