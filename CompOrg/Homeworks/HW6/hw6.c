#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
	int associative_cache;
	if(argc < 4){
		fprintf(stderr, "Invalid usage\n");
        return EXIT_FAILURE;
	}
	
	if(argv[1][0] == '1'){
		associative_cache = 1;
	}
	else if (argv[1][0] == '2'){
		associative_cache = 2;
	}
	else if (argv[1][0] == '4'){
		associative_cache = 4;
	}
	else{
		fprintf(stderr, "Invalid usage\n");
        return EXIT_FAILURE;
	}
	
	FILE *fp;
	fp = fopen(argv[3], "r");
	
	if (!fp) {
        fprintf(stderr, "Error: Cannot open file!\n");
        return EXIT_FAILURE;
    }
	
	int cache_set = 256/associative_cache;
	char line[6];
	int mem_addresses[1024];
	int linecount = 0;
	
	while(fgets(line,6,fp) != NULL){
		int num = atoi(line);
		mem_addresses[linecount] = num;
		linecount++;
	}
	
	int mem_accesses[256];
	int mem_accesses2[256];
	int cache_mem[256];
	for(int i = 0; i < 256; i++){
		mem_accesses[i] = 0;
		mem_accesses2[i] = 0;
		cache_mem[i] = 0;
	}
	
	
	
	printf("Cache size: 256\n");
    printf("Cache associativity: %d\n", associative_cache);
    printf("Cache sets: %d\n", cache_set);
	int hitcount = 0;
	int count = 0;
	int set;
	// int hit;
	
	if(argv[2][0] == 'L' && argv[2][1] == 'R' && argv[2][2] == 'U'){
		printf("Cache algorithm: LRU\n");
		while(count < linecount){
			//hit = 0;
			set = mem_addresses[count] % cache_set;
			if(cache_mem[set] == mem_addresses[count]){
				hitcount++;
				// hit = 1;
				printf("%d (hit)\n",mem_addresses[count]);
				int j;
				int k = 0;
				for(j = 0; j < 256 && k < 256; j++){
					if(j == set){
						k++;
					}
					if(mem_accesses[k] == 0){
						break;
					}
					if(k < 256){
						mem_accesses2[j] = mem_accesses[k];
					}
					k++;
				}
				mem_accesses2[j] = mem_addresses[count];
				for(j = 0; j < 256; j++){
					mem_accesses[j] = mem_accesses2[j];
				}
			}
			else{
				printf("%d (miss)\n",mem_addresses[count]);
				if(count > cache_set){
					int j;
					int set2 = mem_accesses[0] % cache_set;
					cache_mem[set2] = mem_addresses[count];
					for(j = 1; j < 256; j++){
						mem_accesses2[j-1] = mem_accesses[j];
					}
					mem_accesses2[j-1] = mem_addresses[count];
					for(j = 0; j < 256; j++){
						mem_accesses[j] = mem_accesses2[j];
					}
				}
				else{
					cache_mem[set] = mem_addresses[count];
					for(int i = 0; i< 256; i++){
						if(mem_accesses[i] == 0){
							mem_accesses[i] = mem_addresses[count];
							break;
						}
					}
				}
			}
			count++;
		}
		printf("Cache accesses: %d\n", linecount);
		printf("Cache hits: %d\n", hitcount);
		printf("Cache misses: %d\n", linecount-hitcount);
		printf("Overall hit rate: %1.6f\n", (float)hitcount/linecount);
	}
	
	
	
	// if(argv[2][0] == 'L' && argv[2][1] == 'R' && argv[2][2] == 'U'){
		// printf("Cache algorithm: LRU\n");
		// while(p = 0; p<1024; p++){
			// int hit = 0;
			// set = mem_addresses[p] % cache_set;
			// for(int i = 0; i< 256; i++){
				// if(mem_accesses[i] == mem_addresses[p]){
					// hit = 1;
					// hitcount++;
					// int j;
					// int k = 0;
					// for(j = 0; j < 256 && k < 256; j++){
						// if(j == i){
							// k++;
						// }
						// if(mem_accesses[k] == 0){
							// break;
						// }
						// if(k < 256){
							// mem_accesses2[j] = mem_accesses[k];
						// }
						// k++;
					// }
					// mem_accesses2[j] = mem_addresses[p];
					// for(j = 0; j < 256; j++){
						// mem_accesses[j] = mem_accesses2[j];
					// }
					// break;
				// }
			// }
			// if(hit == 0){
				// if(count > cache_set){
					// int j;
					// for(j = 1; j < 256; j++){
						// mem_accesses2[j-1] = mem_accesses[j];
					// }
					// mem_accesses2[j-1] = mem_addresses[p];
					// for(j = 0; j < 256; j++){
						// mem_accesses[j] = mem_accesses2[j];
					// }
				// }
				// else{
					// for(int i = 0; i< 256; i++){
						// if(mem_accesses[i] == 0){
							
							// mem_accesses[set] = mem_addresses[p];
							// printf("%d\n",set);
							// break;
						// }
					// }
				// }
			// }
			// linecount++;
			// count++;
		// }
		// printf("Cache accesses: %d\n", linecount);
		// printf("Cache hits: %d\n", hitcount);
		// printf("Cache misses: %d\n", linecount-hitcount);
		// printf("Overall hit rate: %1.6f\n", (float)hitcount/linecount);
		
	// }
	
	else if(argv[2][0] == 'B' && argv[2][1] == 'e' && argv[2][2] == 'l' && argv[2][3] == 'a' && argv[2][4] == 'd' && argv[2][5] == 'y'){
		printf("Cache algorithm: Belady\n");
		while(fgets(line,6,fp) != NULL){
			//printf("%s",line);
			int num = atoi(line);
			//printf("%d\n",num);
			for(int i = 0; i< 1024; i++){
				if(mem_accesses[i] == num){
					printf("%d (hit)\n",num);
					hitcount++;
					break;
				}
				if(mem_accesses[i] == 0){
					printf("%d (miss)\n",num);
					mem_accesses[i] = num;
					break;
				}
			}
			linecount++;
		}
		printf("Cache accesses: %d\n", linecount);
		printf("Cache hits: %d\n", hitcount);
		printf("Cache misses: %d\n", linecount-hitcount);
		printf("Overall hit rate: %1.6f\n", (float)hitcount/linecount);
	}
	
	else{
		fprintf(stderr, "Invalid usage\n");
        return EXIT_FAILURE;
	}
	
	fclose(fp);
    return EXIT_SUCCESS;
}