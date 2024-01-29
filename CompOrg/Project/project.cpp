#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <bitset>
#include <utility>
using namespace std;
int binary_and(int num1, int num2){
	std::string binary1 = std::bitset< 10 >( num1 ).to_string(); // string conversion
	std::string binary2 = std::bitset< 10 >( num2 ).to_string(); // string conversion
	std::string binary3;
	for(unsigned int i = 0; i < binary1.size(); i++){
		if(binary1[i] == '1' && binary2[i] == '1'){
			binary3 += '1';
		}
		else{
			binary3 += '0';
		}
	}
	int answer = 0;
	for(unsigned int i = 0; i < binary3.size(); i++){
		if(binary3[i] == '1'){
			answer += std::pow(2,9-i);
		}
	}
	return answer;
}

int binary_or(int num1, int num2){
	std::string binary1 = std::bitset< 10 >( num1 ).to_string(); // string conversion
	std::string binary2 = std::bitset< 10 >( num2 ).to_string(); // string conversion
	std::string binary3;
	for(unsigned int i = 0; i < binary1.size(); i++){
		if(binary1[i] == '1' || binary2[i] == '1'){
			binary3 += '1';
		}
		else{
			binary3 += '0';
		}
	}
	int answer = 0;
	for(unsigned int i = 0; i < binary3.size(); i++){
		if(binary3[i] == '1'){
			answer += std::pow(2,9-i);
		}
	}
	return answer;
}

void print_regs(std::vector<int> t, std::vector<int> s){
	for(unsigned int i = 0; i<s.size(); i++){
		int spaces = 0;
		std::cout << "$s" << i << " = " << s[i];
		if(i == 3 || i == 7){
			std::cout << std::endl;
		}
		else{
			if(s[i] > 1000){
				spaces = 3;
			}
			else if(s[i] > 100){
				spaces = 2;
			}
			else if(s[i] > 10){
				spaces = 1;
			}
			for(int j = spaces; j < 13; j++){
				std::cout<< " ";
			}
		}
	}
	for(unsigned int i = 0; i<t.size(); i++){
		int spaces = 0;
		std::cout << "$t" << i << " = " << t[i];
		if(i == 3 || i == 7 || i == 9){
			std::cout << std::endl;
		}
		else{
			if(t[i] > 1000){
				spaces = 3;
			}
			else if(t[i] > 100){
				spaces = 2;
			}
			else if(t[i] > 10){
				spaces = 1;
			}
			for(int j = spaces; j < 13; j++){
				std::cout<< " ";
			}
		}
	}
}


void slt(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t, int index){
	int num1 = 0;
	int num2 = 0;
	
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	if(instructions[index][2] == "$zero"){
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		
		if(reg1 == 's'){
			s[reg1_num] = 1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = 1;
		}
	}
	else if(instructions[index][3] == "$zero"){
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			s[reg1_num] = 1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = 1;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		if(reg1 == 's'){
			if(num1 < num2){
				s[reg1_num] = 1;
			}
			else{
				s[reg1_num] = 0;
			}
			
		}
		else if(reg1 == 't'){
			if(num1 < num2){
				t[reg1_num] = 1;
			}
			else{
				t[reg1_num] = 0;
			}
		}
	}
}
void slti(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t,int index){
	int num = 0;
	int num1 = 0;
	std::istringstream ss(instructions[index][3]);
	ss >> num;
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	if(instructions[index][2] == "$zero"){
		if(reg1 == 's'){
			s[reg1_num] = 1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = 1;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			if(num1 < num){
				s[reg1_num] = 1;
			}
			else{
				s[reg1_num] = 0;
			}
			
		}
		else if(reg1 == 't'){
			if(num1 < num){
				t[reg1_num] = 1;
			}
			else{
				t[reg1_num] = 0;
			}
		}
	}
}

void ori(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t,int index){
	int num = 0;
	int num1 = 0;
	std::istringstream ss(instructions[index][3]);
	ss >> num;
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	if(instructions[index][2] == "$zero"){
		if(reg1 == 's'){
			s[reg1_num] = num;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		// if(reg2_num == 0){
			// if(reg1 == 's'){
				// s[reg1_num] = num;
			// }
			// else if(reg1 == 't'){
				// t[reg1_num] = num;
			// }
			
		// }
		
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			int answer = binary_or(num,num1);
			s[reg1_num] = answer;
		}
		else if(reg1 == 't'){
			int answer = binary_or(num,num1);
			t[reg1_num] = answer;
		}
	}
}

void andd(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t,int index){
	int num1 = 0;
	int num2 = 0;
	
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	if(instructions[index][2] == "$zero"){
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		
		if(reg1 == 's'){
			s[reg1_num] = num2;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num2;
		}
	}
	else if(instructions[index][3] == "$zero"){
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			s[reg1_num] = num1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num1;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		if(reg1 == 's'){
			int answer = binary_and(num1,num2);
			s[reg1_num] = answer;
		}
		else if(reg1 == 't'){
			int answer = binary_and(num1,num2);
			t[reg1_num] = answer;
		}
	}
}

void addi(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t, int index){
	int num = 0;
	int num1 = 0;
	std::istringstream ss(instructions[index][3]);
	ss >> num;
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	//std::cout << reg1_num << std::endl;
	if(instructions[index][2] == "$zero"){
		if(reg1 == 's'){
			s[reg1_num] = num;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			s[reg1_num] = num + num1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num + num1;
		}
	}
}

void add(std::vector<std::vector<std::string> >instructions, std::vector<int>& s, std::vector<int>& t, int index){
	int num1 = 0;
	int num2 = 0;
	
	char reg1 = instructions[index][1][1];
	int reg1_num = (int)instructions[index][1][2] - 48;
	if(instructions[index][2] == "$zero"){
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		
		if(reg1 == 's'){
			s[reg1_num] = num2;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num2;
		}
	}
	else if(instructions[index][3] == "$zero"){
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg1 == 's'){
			s[reg1_num] = num1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num1;
		}
	}
	else{
		char reg2 = instructions[index][2][1];
		int reg2_num = (int)instructions[index][2][2] - 48;
		
		char reg3 = instructions[index][3][1];
		int reg3_num = (int)instructions[index][3][2] - 48;
		if(reg2 == 's'){
			num1 = s[reg2_num];
		}
		else if(reg2 == 't'){
			num1 = t[reg2_num];
		}
		
		if(reg3 == 's'){
			num2 = s[reg3_num];
		}
		else if(reg3 == 't'){
			num2 = t[reg3_num];
		}
		
		if(reg1 == 's'){
			s[reg1_num] = num2 + num1;
		}
		else if(reg1 == 't'){
			t[reg1_num] = num2 + num1;
		}
	}
	
}

void print(std::string line){
	std::string str = "CPU Cycles ===>     ";
	std::cout << line;
	for(unsigned int j = 0; j < str.length() - line.length(); j++){
		std::cout << " ";
	}
}

int main(int argc, char* argv[]){
	std::ifstream infile(argv[2]);
	if (!infile.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}
	std::vector<int> t;
	std::vector<int> s;
	std::pair <std::string,int> foo;
	for(int i =0; i<10; i++){
		t.push_back(0);
	}
	for(int i =0; i<8; i++){
		s.push_back(0);
	}
	std::string line;
	std::vector<std::vector<std::string> >instructions;
	
	std::map<std::string,int> function;
	//std::vector<int> functionLine;
	std::vector<std::string> dependencyRegs;
	std::vector<int> dependencyLines;
	std::vector<std::string> lines;
	int i = 1;
	// int j = 0;
	while(infile >> line){
		std::vector<std::string> instructions1;
		std::string first = line;
		if(std::find(line.begin(), line.end(), ':') != line.end()){
			foo = std::make_pair(line,i);
			function.insert(foo);
			continue;
		}
		std::string strr = line;
		instructions1.push_back(first);
		//std::cout << instructions1[0] << std::endl;
		infile >> line;
		int reg_count = 0;
		std::stringstream linestream(line);
		std::string value;
		//std::string save_value;
		std::string comma = " ";
		while(getline(linestream,value,',')){
			strr = strr + comma + value;
			if(value == "$zero"){
				reg_count++;
				instructions1.push_back(value);
				continue;
			}
			if(value[0] == '$'){
				reg_count++;
			}
			if(reg_count == 1){
				if(first != "sw"){
					dependencyRegs.push_back(value);
					//save_value = value;
				}	
			}
			else if(reg_count == 2){
				if(first != "or" || first != "ori"){
					if(first == "sw"){
						dependencyRegs.push_back(value);
					}
					else if(i>1){
						if(std::find(dependencyRegs.begin(),dependencyRegs.end(),value) != dependencyRegs.end()){
							//if(value != save_value && std::count(dependencyRegs.begin(),dependencyRegs.end(),value) != 1 ){
								dependencyLines.push_back(i);
							//}
						}
					}			
				}					
			}
			else if(reg_count == 3){
				if(first != "or" || first != "ori"){
					if(i>1){
						if(std::find(dependencyRegs.begin(),dependencyRegs.end(),value) != dependencyRegs.end()){
							//if(value != save_value && std::count(dependencyRegs.begin(),dependencyRegs.end(),value) != 1 ){
								dependencyLines.push_back(i);
							//}
						}
					}	
				}					
			}
			instructions1.push_back(value);
			// std::cout << instructions1[j] << std::endl;
			// std::cout << value << std::endl;
			comma = ",";
			// j++;
		}
		instructions.push_back(instructions1);
		//std::cout << instructions1[0] << std::endl;
		//std::cout << instructions[i][0] << std::endl;
		lines.push_back(strr);
		i++;
		
	}
	
	
	
	//std::cout << std::count(dependencyLines.begin(), dependencyLines.end(), 3) << std::endl;
	
	std::string var = argv[1];
	std::string str = "CPU Cycles ===>     ";
	if(var == "N"){
		std::cout << "START OF SIMULATION (no forwarding)" << std::endl;
		for(unsigned int i = 0; i < 16; i++){
			std::cout << "----------------------------------------------------------------------------------" << std::endl;
			std::cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16"<< std::endl;			
			if(i == 0){
				print(lines[0]);
				std::cout <<"IF  .   .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
			}
			else if(i == 1){
				print(lines[0]);
				std::cout <<"IF  ID  .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
			}
			else if(i == 2){
				print(lines[0]);
				std::cout <<"IF  ID  EX  .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  .   .   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
				print(lines[2]);
				std::cout <<".   .   IF  .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
			}
			else if(i == 3){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					print(lines[1]);
					std::cout <<".   IF  ID  ID  .   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
					print(lines[2]);
					std::cout <<".   .   IF  IF  .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  .   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
					print(lines[2]);
					std::cout <<".   .   IF  ID  .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				
			}
			
			else if(i == 4){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(instructions[0][0] == "ori"){
					ori(instructions,s,t,0);
				}
				else if(instructions[0][0] == "addi"){
					addi(instructions,s,t,0);
				}
				else if(instructions[0][0] == "add"){
					add(instructions,s,t,0);
				}
				else if(instructions[0][0] == "and"){
					andd(instructions,s,t,0);
				}
				else if(instructions[0][0] == "slti"){
					slti(instructions,s,t,0);
				}
				else if(instructions[0][0] == "slt"){
					slt(instructions,s,t,0);
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
						
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){					
					std::cout <<"nop                 .   .   IF  ID  *   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
					
					print(lines[2]);
					std::cout <<".   .   IF  ID  ID  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  .   .   .   .   .   .   .   .   .   .   ." << std::endl;	
				}
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
					}
					else{
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
					
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 5){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
					
					if(instructions[1][0] == "ori"){
						ori(instructions,s,t,1);
					}
					else if(instructions[1][0] == "addi"){
						addi(instructions,s,t,1);
					}
					else if(instructions[1][0] == "add"){
						add(instructions,s,t,1);
					}	
					else if(instructions[1][0] == "and"){
						andd(instructions,s,t,1);
					}
					else if(instructions[1][0] == "slti"){
						slti(instructions,s,t,1);
					}
					else if(instructions[1][0] == "slt"){
						slt(instructions,s,t,1);
					}
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   *   .   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  EX  .   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  EX  .   .   .   .   .   .   .   .   .   ." << std::endl;
						
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
					std::cout <<"nop                 .   .   IF  ID  *   *   .   .   .   .   .   .   .   .   .   ."<< std::endl;
					if(std::count(dependencyLines.begin(), dependencyLines.end(), 3) == 2){
						std::cout <<"nop                 .   .   IF  ID  ID  *   .   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
					else{ 
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  EX  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   ." << std::endl;	
				}
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  IF  .   .   .   .   .   .   .   .   .   ." << std::endl;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
					}
					else{
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  EX  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  .  .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 6){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  EX  MEM .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  ID  EX  .   .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  EX  MEM .   .   .   .   .   .   .   .   ." << std::endl;
						
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
					std::cout <<"nop                 .   .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
					if(std::count(dependencyLines.begin(), dependencyLines.end(), 3) == 2){
						std::cout <<"nop                 .   .   IF  ID  ID  *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  ID  EX  .   .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  EX  MEM .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
					if(instructions[2][0] == "ori"){
						ori(instructions,s,t,2);
					}
					else if(instructions[2][0] == "addi"){
						addi(instructions,s,t,2);
					}					
					else if(instructions[2][0] == "add"){
						add(instructions,s,t,2);
					}
					else if(instructions[2][0] == "and"){
						andd(instructions,s,t,2);
					}
					else if(instructions[2][0] == "slti"){
						slti(instructions,s,t,2);
					}
					else if(instructions[2][0] == "slt"){
						slt(instructions,s,t,2);
					}
					break;
				}
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  IF  ID  .   .   .   .   .   .   .   .   ." << std::endl;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  EX  MEM .  .   .   .   .   .   .   .   ." << std::endl;
					}

					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 7){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}				
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
					std::cout <<"nop                 .   .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
					if(std::count(dependencyLines.begin(), dependencyLines.end(), 3) == 2){
						std::cout <<"nop                 .   .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}	
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;	
					break;
				}
				
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  IF  ID  EX  .   .   .   .   .   .   .   ." << std::endl;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  EX  MEM WB .   .   .   .   .   .   .   ." << std::endl;
					}
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 8){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
					std::cout <<"nop                 .   .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
					if(std::count(dependencyLines.begin(), dependencyLines.end(), 3) == 2){
						std::cout <<"nop                 .   .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}					
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}	
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;	
					break;
				}
				
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  IF  ID  EX  MEM .   .   .   .   .   .   ." << std::endl;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  EX  MEM WB .   .   .   .   .   .   .   ." << std::endl;
					}
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 9){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					std::cout << "nop                 .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				else{
					print(lines[1]);
					std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				}
				
				if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						std::cout <<"nop                 .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[1]);
						std::cout <<".   IF  ID  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  IF  IF  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}			
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}
				else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
					std::cout <<"nop                 .   .   IF  ID  *   *   *   .   .   .   .   .   .   .   .   ."<< std::endl;
					if(std::count(dependencyLines.begin(), dependencyLines.end(), 3) == 2){
						std::cout <<"nop                 .   .   IF  ID  ID  *   *   *   .   .   .   .   .   .   .   ."<< std::endl;
						
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
					}
					else{
						print(lines[2]);
						std::cout <<".   .   IF  ID  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
						if(instructions[2][0] == "ori"){
							ori(instructions,s,t,2);
						}
						else if(instructions[2][0] == "addi"){
							addi(instructions,s,t,2);
						}	
						else if(instructions[2][0] == "add"){
							add(instructions,s,t,2);
						}
						else if(instructions[2][0] == "and"){
							andd(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slti"){
							slti(instructions,s,t,2);
						}
						else if(instructions[2][0] == "slt"){
							slt(instructions,s,t,2);
						}
						break;
					}
				}	
				else{
					print(lines[2]);
					std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;	
					break;
				}
				
				
				if(lines.size() > 3){
					if(std::find(dependencyLines.begin(),dependencyLines.end(),2) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
							if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						
							}
							else{
								
							}
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),3) != dependencyLines.end()){
						if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
							print(lines[3]);
							std::cout <<".   .   .   IF  IF  IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
							
							if(instructions[3][0] == "ori"){
								ori(instructions,s,t,3);
							}
							else if(instructions[3][0] == "addi"){
								addi(instructions,s,t,3);
							}	
							else if(instructions[3][0] == "add"){
								add(instructions,s,t,3);
							}
							else if(instructions[3][0] == "and"){
								andd(instructions,s,t,3);
							}
							else if(instructions[3][0] == "slti"){
								slti(instructions,s,t,3);
							}
							else if(instructions[3][0] == "slt"){
								slt(instructions,s,t,3);
							}
							break;
						}
						else{
							
						}
					}
					else if(std::find(dependencyLines.begin(),dependencyLines.end(),4) != dependencyLines.end()){
						print(lines[3]);
						std::cout <<".   .   .   IF  ID  EX  MEM WB .   .   .   .   .   .   .   ." << std::endl;
					}
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			std::cout << std::endl;
			// std::cout << s[instructions[0][1][2]] << std::endl;
			// std::cout << s[1] << std::endl;
			print_regs(t,s);
		}
		std::cout << std::endl;
		print_regs(t,s);
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		std::cout << "END OF SIMULATION" << std::endl;
	}
	
	else if(var == "F"){
		std::cout << "START OF SIMULATION (forwarding)" << std::endl;
		for(unsigned int i = 0; i < 16; i++){
			std::cout << "----------------------------------------------------------------------------------" << std::endl;
			std::cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16"<< std::endl;			
			if(i == 0){
				print(lines[0]);
				std::cout <<"IF  .   .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
			}
			else if(i == 1){
				print(lines[0]);
				std::cout <<"IF  ID  .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  .   .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
			}
			else if(i == 2){
				print(lines[0]);
				std::cout <<"IF  ID  EX  .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  .   .   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
				print(lines[2]);
				std::cout <<".   .   IF  .   .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
			}
			else if(i == 3){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  .   .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
					
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  .   .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				}
				
			}
			
			else if(i == 4){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(instructions[0][0] == "ori"){
					ori(instructions,s,t,0);
				}
				else if(instructions[0][0] == "addi"){
					addi(instructions,s,t,0);
				}
				else if(instructions[0][0] == "add"){
					add(instructions,s,t,0);
				}
				else if(instructions[0][0] == "and"){
					andd(instructions,s,t,0);
				}
				else if(instructions[0][0] == "slti"){
					slti(instructions,s,t,0);
				}
				else if(instructions[0][0] == "slt"){
					slt(instructions,s,t,0);
				}
				
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){					
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
					}
				}				
			}
			
			else if(i == 5){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				if(instructions[1][0] == "ori"){
					ori(instructions,s,t,1);
				}
				else if(instructions[1][0] == "addi"){
					addi(instructions,s,t,1);
				}
				else if(instructions[1][0] == "add"){
					add(instructions,s,t,1);
				}	
				else if(instructions[1][0] == "and"){
					andd(instructions,s,t,1);
				}
				else if(instructions[1][0] == "slti"){
					slti(instructions,s,t,1);
				}
				else if(instructions[1][0] == "slt"){
					slt(instructions,s,t,1);
				}
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM .   .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  .   .   .   .   .   .   .   .   .   ." << std::endl;
					
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  .   .   .   .   .   .   .   .   .   ." << std::endl;
						
						if(lines.size() > 5){
							print(lines[5]);
							std::cout <<".   .   .   .   .   IF  .   .   .   .   .   .   .   .   .   ." << std::endl;
						}
						
					}
				}				
			}
			
			else if(i == 6){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
					
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				if(instructions[2][0] == "ori"){
					ori(instructions,s,t,2);
				}
				else if(instructions[2][0] == "addi"){
					addi(instructions,s,t,2);
				}					
				else if(instructions[2][0] == "add"){
					add(instructions,s,t,2);
				}
				else if(instructions[2][0] == "and"){
					andd(instructions,s,t,2);
				}
				else if(instructions[2][0] == "slti"){
					slti(instructions,s,t,2);
				}
				else if(instructions[2][0] == "slt"){
					slt(instructions,s,t,2);
				}
				if(lines.size() == 3){
					break;
				}
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM .   .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  .   .   .   .   .   .   .   .   ." << std::endl;
						if(lines.size() > 5){
							print(lines[5]);
							std::cout <<".   .   .   .   .   IF  ID  .   .   .   .   .   .   .   .   ." << std::endl;
							if(lines.size() > 6){
								print(lines[6]);
								std::cout <<".   .   .   .   .   .   IF  .   .   .   .   .   .   .   .   ." << std::endl;
							}
						}
					}
				}				
			}
			
			else if(i == 7){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(instructions[3][0] == "ori"){
						ori(instructions,s,t,3);
					}
					else if(instructions[3][0] == "addi"){
						addi(instructions,s,t,3);
					}					
					else if(instructions[3][0] == "add"){
						add(instructions,s,t,3);
					}
					else if(instructions[3][0] == "and"){
						andd(instructions,s,t,3);
					}
					else if(instructions[3][0] == "slti"){
						slti(instructions,s,t,3);
					}
					else if(instructions[3][0] == "slt"){
						slt(instructions,s,t,3);
					}
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM .   .   .   .   .   .   .   ." << std::endl;
						if(lines.size() > 5){
							print(lines[5]);
							std::cout <<".   .   .   .   .   IF  ID  EX  .   .   .   .   .   .   .   ." << std::endl;
							if(lines.size() > 6){
								print(lines[6]);
								std::cout <<".   .   .   .   .   .   IF  ID  .   .   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 7){
									print(lines[7]);
									std::cout <<".   .   .   .   .   .   .   IF  .   .   .   .   .   .   .   ." << std::endl;
								}
							}
						}
					}
				}						
			}
			
			else if(i == 8){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(instructions[4][0] == "ori"){
							ori(instructions,s,t,4);
						}
						else if(instructions[4][0] == "addi"){
							addi(instructions,s,t,4);
						}					
						else if(instructions[4][0] == "add"){
							add(instructions,s,t,4);
						}
						else if(instructions[4][0] == "and"){
							andd(instructions,s,t,4);
						}
						else if(instructions[4][0] == "slti"){
							slti(instructions,s,t,4);
						}
						else if(instructions[4][0] == "slt"){
							slt(instructions,s,t,4);
						}
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   .   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   .   .   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   .   .   .   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  .   .   .   .   .   .   ." << std::endl;
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM .   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  .   .   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  .   .   .   .   .   .   ." << std::endl;
										
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 9){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   .   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   .   .   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  .   .   .   .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  .   .   .   .   .   ." << std::endl;
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM .   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  .   .   .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 10){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   .   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  .   .   .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  .   .   .   .   ." << std::endl;
							
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  .   .   .   .   ." << std::endl;
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM .   .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 11){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   *   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  MEM .   .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  EX  .   .   .   ." << std::endl;
							
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  ID  .   .   .   ." << std::endl;
							
							print(lines[index+3]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   IF  .   .   .   ." << std::endl;
							
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 12){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   *   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   ." << std::endl;
							
							if(instructions[index][0] == "ori"){
								ori(instructions,s,t,index);
							}
							else if(instructions[index][0] == "addi"){
								addi(instructions,s,t,index);
							}					
							else if(instructions[index][0] == "add"){
								add(instructions,s,t,index);
							}
							else if(instructions[index][0] == "and"){
								andd(instructions,s,t,index);
							}
							else if(instructions[index][0] == "slti"){
								slti(instructions,s,t,index);
							}
							else if(instructions[index][0] == "slt"){
								slt(instructions,s,t,index);
							}
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  EX  MEM .   .   ." << std::endl;
							
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  ID  EX  .   .   ." << std::endl;
							
							print(lines[index+3]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   IF  ID  .   .   ." << std::endl;
							
							print(lines[index+4]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   IF  .   .   ." << std::endl;
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 13){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   *   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   ." << std::endl;
							
							if(instructions[index+1][0] == "ori"){
								ori(instructions,s,t,index+1);
							}
							else if(instructions[index+1][0] == "addi"){
								addi(instructions,s,t,index+1);
							}					
							else if(instructions[index+1][0] == "add"){
								add(instructions,s,t,index+1);
							}
							else if(instructions[index+1][0] == "and"){
								andd(instructions,s,t,index+1);
							}
							else if(instructions[index+1][0] == "slti"){
								slti(instructions,s,t,index+1);
							}
							else if(instructions[index+1][0] == "slt"){
								slt(instructions,s,t,index+1);
							}
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM .   ." << std::endl;
							
							
							
							print(lines[index+3]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  .   ." << std::endl;
							
							print(lines[index+4]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   IF  ID  .   ." << std::endl;
							
							print(lines[index+5]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   IF  .   ." << std::endl;
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 14){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   *   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   ." << std::endl;
							
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  ." << std::endl;
							
							if(instructions[index+2][0] == "ori"){
								ori(instructions,s,t,index+2);
							}
							else if(instructions[index+2][0] == "addi"){
								addi(instructions,s,t,index+2);
							}					
							else if(instructions[index+2][0] == "add"){
								add(instructions,s,t,index+2);
							}
							else if(instructions[index+2][0] == "and"){
								andd(instructions,s,t,index+2);
							}
							else if(instructions[index+2][0] == "slti"){
								slti(instructions,s,t,index+2);
							}
							else if(instructions[index+2][0] == "slt"){
								slt(instructions,s,t,index+2);
							}
							
							print(lines[index+3]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM ." << std::endl;
							
							print(lines[index+4]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  ." << std::endl;
							
							print(lines[index+5]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   IF  ID  ." << std::endl;
							
							print(lines[index+6]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   .   IF  ." << std::endl;
							
							
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			
			else if(i == 15){
				print(lines[0]);
				std::cout <<"IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   .   ." << std::endl;
				print(lines[1]);
				std::cout <<".   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   .   ."<< std::endl;
				
				print(lines[2]);
				std::cout <<".   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   .   ." << std::endl;
				
				if(lines.size() > 3){
					print(lines[3]);
					std::cout <<".   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   .   ." << std::endl;
					if(lines.size() > 4){
						print(lines[4]);
						std::cout <<".   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   .   ." << std::endl;
						if(function[instructions[4][3] + ':'] != 0){
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  *   *   .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  *   *   *   .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  *   *   *   *   .   .   .   ." << std::endl;
										
									}
								}
							}
							//std::cout << function[instructions[4][3] + ':'] << std::endl;
							int index = function[instructions[4][3] + ':']-1;
							print(lines[index]);
							std::cout <<".   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   ." << std::endl;
							
							print(lines[index+1]);
							std::cout <<".   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   ." << std::endl;
							
							print(lines[index+2]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB  ." << std::endl;
							
							
							print(lines[index+3]);
							std::cout <<".   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM WB" << std::endl;
							
							if(instructions[index+3][0] == "ori"){
								ori(instructions,s,t,index+3);
							}
							else if(instructions[index+3][0] == "addi"){
								addi(instructions,s,t,index+3);
							}					
							else if(instructions[index+3][0] == "add"){
								add(instructions,s,t,index+3);
							}
							else if(instructions[index+3][0] == "and"){
								andd(instructions,s,t,index+3);
							}
							else if(instructions[index+3][0] == "slti"){
								slti(instructions,s,t,index+3);
							}
							else if(instructions[index+3][0] == "slt"){
								slt(instructions,s,t,index+3);
							}
							
							
							if(function[instructions[index+3][3] + ':'] != 0){
								int index2 = function[instructions[index+3][3] + ':']-1;
								print(lines[index + 4]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  *" << std::endl;
								
								print(lines[index + 5]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   IF  ID  *" << std::endl;
								
								print(lines[index + 6]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   .   IF  *" << std::endl;
								
								print(lines[index2]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   .   .   IF" << std::endl;
							}
							else{
								print(lines[index+4]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   IF  ID  EX  MEM" << std::endl;
								
								print(lines[index+5]);
								std::cout <<".   .   .   .   .   .   .   .   .   .   .   .   .   IF  ID  EX" << std::endl;
							}
						}
						else{
							if(lines.size() > 5){
								print(lines[5]);
								std::cout <<".   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   .   ." << std::endl;
								if(lines.size() > 6){
									print(lines[6]);
									std::cout <<".   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   .   ." << std::endl;
									if(lines.size() > 7){
										print(lines[7]);
										std::cout <<".   .   .   .   .   .   .   IF  ID  EX  MEM WB  .   .   .   ." << std::endl;
									}
								}
							}
						}
					}
				}						
			}
			if(i != 15){
				std::cout << std::endl;
				print_regs(t,s);
			}
		}
		std::cout << std::endl;
		print_regs(t,s);
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		std::cout << "END OF SIMULATION" << std::endl;
	}
	
	else{
		std::cerr << "Can't do " << argv[1] << " \n";
		exit(1);
	}
}