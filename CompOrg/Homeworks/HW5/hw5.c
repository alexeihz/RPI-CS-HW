/* HW 5 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "Invalid use\n");
		return EXIT_FAILURE;
	}
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	if (!fp) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }
	
	char line1[128];
	char line2[128];
	char line3[128];
	char line4[128];
	char line5[128];
	
	char lines1[128];
	char lines2[128];
	char lines3[128];
	char lines4[128];
	char lines5[128];
	// char lastreg1[2];
	// char lastreg2[2];
	// char lastreg3[2];
	// char lastreg4[2];
	// char lastreg5[2];
	
	// char reg1[2];
	// char reg2[2];
	// char reg3[2];
	// char reg4[2];
	// char reg5[2];
	
	// char reg6[2];
	// char reg7[2];
	// char reg8[2];
	// char reg9[2];
	// char reg10[2];
	
	int dependencyLines[5];
	char dependencyRegs[5][2];
	int dependencycount = 0;
	int dependencycount2 = 0;
	int totalsteps = 0;
	
	int linecount = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int storeWord = 0;
	int or = 0;
	int cyclecount = 0;
	int registerCount = 1;
	
	if(fgets(line1,128,fp) != NULL){
		i = 0;
		while(line1[i] != '\n'){
			lines1[i] = line1[i];
			if(line1[i] =='$'){
				if(line1[0] == 's' && line1[1] == 'w'){
					storeWord = 1;
				}
				else if(line1[0] == 'o' && line1[1] == 'r' && line1[2] == 'i'){
					or = 1;
				}
				if(registerCount == 1){
					if(storeWord == 0){
						dependencyRegs[j][0] = line1[i+1];
						dependencyRegs[j][1] = line1[i+2];
						j++;
					}
				}
				else if(registerCount == 2){
					if(storeWord == 1){
						dependencyRegs[j][0] = line1[i+1];
						dependencyRegs[j][1] = line1[i+2];
						j++;
					}
				}
				registerCount++;
			}
			
			i++;
		}
		storeWord = 0;
		or = 0;
		linecount++;
		registerCount = 1;
	}
	
	if(fgets(line2,128,fp) != NULL){
		i = 0;
		while(line2[i] != '\n'){
			lines2[i] = line2[i];
			if(line2[i] =='$'){
				if(line2[0] == 's' && line2[1] == 'w'){
					storeWord = 1;
				}
				else if(line2[0] == 'o' && line2[1] == 'r' && line2[2] == 'i'){
					or = 1;
					
				}
				if(registerCount == 1){
					if(storeWord == 0){
						dependencyRegs[j][0] = line2[i+1];
						dependencyRegs[j][1] = line2[i+2];
						j++;
					}
				}
				else if(registerCount == 2){
					if(or != 1){
						if(storeWord == 1){
							dependencyRegs[j][0] = line2[i+1];
							dependencyRegs[j][1] = line2[i+2];
							j++;
						}
						else{
							if(dependencyRegs[0][0] == line2[i+1] && dependencyRegs[0][1] == line2[i+2]){
								dependencyLines[k] = 2;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[1][0] == line2[i+1] && dependencyRegs[1][1] == line2[i+2]){
								dependencyLines[k] = 2;
								k++;
								dependencycount++;
							}
						}
					}
				}
				else if(registerCount == 3){
					if(or != 1){
						if(dependencyRegs[0][0] == line2[i+1] && dependencyRegs[0][1] == line2[i+2]){
							dependencyLines[k] = 2;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[1][0] == line2[i+1] && dependencyRegs[1][1] == line2[i+2]){
							dependencyLines[k] = 2;
							k++;
							dependencycount++;
						}
					}
				}
				registerCount++;
			}
			i++;
		}
		or = 0;
		storeWord = 0;
		linecount++;
		registerCount = 1;
	}
	
	
	if(fgets(line3,128,fp) != NULL){
		i = 0;
		while(line3[i] != '\n'){
			lines3[i] = line3[i];
			
			if(line3[i] =='$'){
				if(line3[0] == 's' && line3[1] == 'w'){
					storeWord = 1;
				}
				else if(line3[0] == 'o' && line3[1] == 'r' && line3[2] == 'i'){
					or = 1;
				}
				if(registerCount == 1){
					if(storeWord == 0){
						dependencyRegs[j][0] = line3[i+1];
						dependencyRegs[j][1] = line3[i+2];
						j++;
					}
				}
				else if(registerCount == 2){
					
					if(storeWord == 1){
						dependencyRegs[j][0] = line3[i+1];
						dependencyRegs[j][1] = line3[i+2];
						j++;
					}
					else{
						if(or != 1){
							if(dependencyRegs[0][0] == line3[i+1] && dependencyRegs[0][1] == line3[i+2]){
								dependencyLines[k] = 3;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[1][0] == line3[i+1] && dependencyRegs[1][1] == line3[i+2]){
								dependencyLines[k] = 3;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[2][0] == line3[i+1] && dependencyRegs[2][1] == line3[i+2]){
								dependencyLines[k] = 3;
								k++;
								dependencycount++;
							}
						}
					}
				}
				else if(registerCount == 3){
					if(or != 1){
						if(dependencyRegs[0][0] == line3[i+1] && dependencyRegs[0][1] == line3[i+2]){
							dependencyLines[k] = 3;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[1][0] == line3[i+1] && dependencyRegs[1][1] == line3[i+2]){
							dependencyLines[k] = 3;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[2][0] == line3[i+1] && dependencyRegs[2][1] == line3[i+2]){
							dependencyLines[k] = 3;
							k++;
							dependencycount++;
						}
					}
				}
				registerCount++;
			}
			
			i++;
		}
		storeWord = 0;
		or = 0;
		linecount++;
		registerCount = 1;
	}
	
	if(fgets(line4,128,fp) != NULL){
		i = 0;
		while(line4[i] != '\n'){
			lines4[i] = line4[i];
			if(line4[i] =='$'){
				if(line4[0] == 's' && line4[1] == 'w'){
					storeWord = 1;
				}
				else if(line4[0] == 'o' && line4[1] == 'r' && line4[2] == 'i'){
					or = 1;
				}
				if(registerCount == 1){
					if(storeWord == 0){
						dependencyRegs[j][0] = line4[i+1];
						dependencyRegs[j][1] = line4[i+2];
						j++;
					}
				}
				else if(registerCount == 2){
					if(storeWord == 1){
						dependencyRegs[j][0] = line4[i+1];
						dependencyRegs[j][1] = line4[i+2];
						j++;
					}
					else{
						if(or != 1){
							if(dependencyRegs[0][0] == line4[i+1] && dependencyRegs[0][1] == line4[i+2]){
								dependencyLines[k] = 4;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[1][0] == line4[i+1] && dependencyRegs[1][1] == line4[i+2]){
								dependencyLines[k] = 4;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[2][0] == line4[i+1] && dependencyRegs[2][1] == line4[i+2]){
								dependencyLines[k] = 4;
								k++;
								dependencycount++;
							}else if(dependencyRegs[3][0] == line4[i+1] && dependencyRegs[3][1] == line4[i+2]){
								dependencyLines[k] = 4;
								k++;
								dependencycount++;
							}
						}
					}
				}
				else if(registerCount == 3){
					if(or != 1){
						if(dependencyRegs[0][0] == line4[i+1] && dependencyRegs[0][1] == line4[i+2]){
							dependencyLines[k] = 4;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[1][0] == line4[i+1] && dependencyRegs[1][1] == line4[i+2]){
							dependencyLines[k] = 4;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[2][0] == line4[i+1] && dependencyRegs[2][1] == line4[i+2]){
							dependencyLines[k] = 4;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[3][0] == line4[i+1] && dependencyRegs[3][1] == line4[i+2]){
							dependencyLines[k] = 4;
							k++;
							dependencycount++;
						}
					}
				}
				registerCount++;
			}
			
			i++;
		}
		linecount++;
		storeWord = 0;
		or = 0;
		registerCount = 1;
	}
	
	
	if(fgets(line5,128,fp) != NULL){
		i = 0;
		while(line5[i] != '\n'){
			lines5[i] = line5[i];
			if(line5[i] =='$'){
				if(line5[0] == 's' && line5[1] == 'w'){
					storeWord = 1;
				}
				else if(line5[0] == 'o' && line5[1] == 'r' && line5[2] == 'i'){
					or = 1;
				}
				if(registerCount == 1){
					if(storeWord == 0){
						dependencyRegs[j][0] = line5[i+1];
						dependencyRegs[j][1] = line5[i+2];
						j++;
					}
				}
				else if(registerCount == 2){
					if(storeWord == 1){
						dependencyRegs[j][0] = line5[i+1];
						dependencyRegs[j][1] = line5[i+2];
						j++;
					}
					else{
						if(or != 1){
							if(dependencyRegs[0][0] == line5[i+1] && dependencyRegs[0][1] == line5[i+2]){
								dependencyLines[k] = 5;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[1][0] == line5[i+1] && dependencyRegs[1][1] == line5[i+2]){
								dependencyLines[k] = 5;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[2][0] == line5[i+1] && dependencyRegs[2][1] == line5[i+2]){
								dependencyLines[k] = 5;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[3][0] == line5[i+1] && dependencyRegs[3][1] == line5[i+2]){
								dependencyLines[k] = 5;
								k++;
								dependencycount++;
							}
							else if(dependencyRegs[4][0] == line5[i+1] && dependencyRegs[4][1] == line5[i+2]){
								dependencyLines[k] = 5;
								k++;
								dependencycount++;
							}
						}
					}
				}
				else if(registerCount == 3){
					if(or != 1){
						if(dependencyRegs[0][0] == line5[i+1] && dependencyRegs[0][1] == line5[i+2]){
							dependencyLines[k] = 5;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[1][0] == line5[i+1] && dependencyRegs[1][1] == line5[i+2]){
							dependencyLines[k] = 5;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[2][0] == line5[i+1] && dependencyRegs[2][1] == line5[i+2]){
							dependencyLines[k] = 5;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[3][0] == line5[i+1] && dependencyRegs[3][1] == line5[i+2]){
							dependencyLines[k] = 5;
							k++;
							dependencycount++;
						}
						else if(dependencyRegs[4][0] == line5[i+1] && dependencyRegs[4][1] == line5[i+2]){
							dependencyLines[k] = 5;
							k++;
							dependencycount++;
						}
					}
				}
				registerCount++;
			}
			i++;
		}
		linecount++;
		storeWord = 0;
		or = 0;
		registerCount = 1;
	}

	if(dependencyLines[0] ==0){
		
	}
	totalsteps = (linecount*2) + 1 + dependencycount; 
	printf("%d",dependencycount);
	printf("%d",totalsteps);
	printf("START OF SIMULATION\n\n");
	
	while (cyclecount <= 9){
		switch(cyclecount){
			case 1:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\t.\t.\t.\t.\t.\t.\t.\t.\n");
							break;
						
						case 2:
							printf("%s", lines2);
							printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
							break;
							
						case 3:
							printf("%s", lines3);
							printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
							
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
							
							break;
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
							
							break;
					}
					i++;
				}
				printf("\n");
				break;
			case 2:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\t.\t.\t.\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							printf("%s", lines2);
							printf("\t.\tIF\t.\t.\t.\t.\t.\t.\t.\n");
							i++;
							break;
							
						case 3:
							if(3 <= linecount){
								printf("%s", lines3);
								printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 4:
							if(4 <= linecount){
								printf("%s", lines4);
								printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 5:
							if(5 <= linecount){
								printf("%s", lines5);
								printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
					}
				}
				printf("\n");
				break;
			case 3:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\t.\t.\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							printf("%s", lines2);
							printf("\t.\tIF\tID\t.\t.\t.\t.\t.\t.\n");
							i++;
							break;
							
						case 3:
							if(3 <= linecount){
								printf("%s", lines3);
								printf("\t.\t.\tIF\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 4:
							if(4 <= linecount){
								printf("%s", lines4);
								printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 5:
							if(5 <= linecount){
								printf("%s", lines5);
								printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
					}
				}
				printf("\n");
				break;
				
			case 4:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\t.\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t.\t.\t.\t.\t.\n");
								
								printf("%s", lines2);
								printf("\t.\tIF\tID\tID\t.\t.\t.\t.\t.\n");
								i++;
								dependencycount2++;
								
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("%s", lines3);
								printf("\t.\t.\tIF\tIF\t.\t.\t.\t.\t.\n");
								i++;
								
							}
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\t.\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\t.\t.\t.\t.\t.\n");
							i++;
							
							break;
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\t.\t.\t.\t.\t.\n");
							i++;
							
							break;
					}
				}
				printf("\n");
				break;
			case 5:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t*\t.\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\tMEM\t.\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
									printf("nop\t\t.\tIF\tID\tID\t*\t.\t.\t.\t.\n");
									
									printf("%s", lines2);
									printf("\t.\tIF\tID\tID\tID\t.\t.\t.\t.\n");
									
									
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tIF\t.\t.\t.\t.\n");
									i++;
									dependencycount2++;
								}
								else{
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tID\t.\t.\t.\t.\n");
									i++;
								}
							}
							else if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
								printf("nop\t\t.\t.\tIF\tID\t*\t.\t.\t.\t.\n");
								
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tID\t.\t.\t.\t.\n");
								i++;
								dependencycount2++;
							}
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tEX\t.\t.\t.\t.\n");
								i++;
							}
						
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\tID\t.\t.\t.\t.\n");
							i++;
							
							break;
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\tIF\t.\t.\t.\t.\n");
							i++;
						
							break;
					}
				}
				printf("\n");
				break;
			case 6:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t*\t*\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
									printf("nop\t\t.\tIF\tID\tID\t*\t*\t.\t.\t.\n");
									
									printf("%s", lines2);
									printf("\t.\tIF\tID\tID\tID\tEX\t.\t.\t.\n");
									
									
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tIF\tID\t.\t.\t.\n");
									i++;
									dependencycount2++;
								}
								else{
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tID\tEX\t.\t.\t.\n");
									i++;
								}
							}
						
							
							else if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
								printf("nop\t\t.\t.\tIF\tID\t*\t*\t.\t.\t.\n");
								
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tID\tEX\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tEX\tMEM\t.\t.\t.\n");
								i++;
							}
							
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\tID\tEX\t.\t.\t.\n");
							i++;
							
							break;
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\tIF\tID\t.\t.\t.\n");
							i++;
							
							break;
					}
				}
				printf("\n");
				break;
			case 7:
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t*\t*\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
									printf("nop\t\t.\tIF\tID\tID\t*\t*\t*\t.\t.\n");
									
									printf("%s", lines2);
									printf("\t.\tIF\tID\tID\tID\tEX\tMEM\t.\t.\n");
									
									
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tIF\tID\tEX\t.\t.\n");
									i++;
									dependencycount2++;
								}
								else{
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tID\tEX\tMEM\t.\t.\n");
									i++;
								}
							}
							else if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
								printf("nop\t\t.\t.\tIF\tID\t*\t*\t*\t.\t.\n");
								
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tID\tEX\tMEM\t.\t.\n");
								i++;
							}
						
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
								i++;
							}
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\tID\tEX\tMEM\t.\t.\n");
							i++;
							
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\tIF\tID\tEX\t.\t.\n");
							i++;
							
							break;
					}
				}
				printf("\n");
				break;
			case 8:
				if(totalsteps < 8){
					break;
				}
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t*\t*\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
									printf("nop\t\t.\tIF\tID\tID\t*\t*\t*\t.\t.\n");
									
									printf("%s", lines2);
									printf("\t.\tIF\tID\tID\tID\tEX\tMEM\tWB\t.\n");
									
									
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tIF\tID\tEX\tMEM\t.\n");
									i++;
									dependencycount2++;
								}
								else{
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tID\tEX\tMEM\tWB\t.\n");
									i++;
								}
							}
							else if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
								printf("nop\t\t.\t.\tIF\tID\t*\t*\t*\t.\t.\n");
								
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tID\tEX\tMEM\tWB\t.\n");
								i++;
							}
							
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
								i++;
							}
							break;
							
						case 4:
							
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
							i++;
							
							break;
							
						case 5:
							
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\tIF\tID\tEX\tMEM\t.\n");
							i++;
							
							break;
					}
				}
				printf("\n");
				break;
			case 9:
				if(totalsteps < 9){
					break;
				}
				printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
				i = 1;
				while(i <= linecount){
					switch(i){
						case 1:
							printf("%s", lines1);
							printf("\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\t.\n");
							i++;
							break;
						
						case 2:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								printf("nop\t\t.\tIF\tID\t*\t*\t*\t.\t.\t.\n");
								i++;
							}
							else{
								printf("%s", lines2);
								printf("\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\t.\n");
								i++;
							}
							break;
							
						case 3:
							if(dependencyLines[0] == 2 || dependencyLines[1] == 2 || dependencyLines[2] == 2 || dependencyLines[3] == 2 || dependencyLines[4] == 2){
								if(dependencyLines[0] == 3 || dependencyLines[1] == 3 || dependencyLines[2] == 3 || dependencyLines[3] == 3 || dependencyLines[4] == 3){
									printf("nop\t\t.\tIF\tID\tID\t*\t*\t*\t.\t.\n");
									
									printf("%s", lines2);
									printf("\t.\tIF\tID\tID\tID\tEX\tMEM\tWB\t.\n");
									
									
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tIF\tID\tEX\tMEM\tWB\n");
									i++;
									dependencycount2++;
								}
								else{
									printf("%s", lines3);
									printf("\t.\t.\tIF\tIF\tID\tEX\tMEM\tWB\t.\n");
									i++;
								}
							}
							else{
								printf("%s", lines3);
								printf("\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\t.\n");
								i++;
							}
							
							break;
							
						case 4:
							printf("%s", lines4);
							printf("\t.\t.\t.\tIF\tID\tEX\tMEM\tWB\t.\n");
							i++;
							
							break;
							
						case 5:
							printf("%s", lines5);
							printf("\t.\t.\t.\t.\tIF\tID\tEX\tMEM\tWB\n");
							i++;
							
							break;
					}
				}
				printf("\n");
				break;
		}
		cyclecount++;
	}
	
	printf("END OF SIMULATION\n");

    fclose(fp);

    return EXIT_SUCCESS;
}