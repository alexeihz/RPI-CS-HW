
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]){
	std::ifstream infile(argv[1]);
	std::string num;
	std::map<std::string, int> numbers;
	while(infile >> num){
		++numbers[num];
	}

	typename std::map<std::string, int>::const_iterator itr;
	int max = 0;
	std::vector<std::string> modes;
	for(itr = numbers.begin(); itr != numbers.end(); ++itr){
		if(itr->second > max){
			modes.clear();
			max = itr->second;
			modes.push_back(itr->first);		
		}

		else if(itr->second == max){
			modes.push_back(itr->first);
		}
	}

	std::cout << "Modes: ";
	if(modes.size() > 0){
		for(unsigned int i = 0; i < modes.size(); i++){
			std::cout << modes[i] + " ";
		}
	}
	else{
		std::cout << "None";
	}

	std::cout << "\n";
	return 0;
}