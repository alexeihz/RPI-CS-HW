#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ostream>
#include <algorithm>
#include <sstream>
using namespace std;


//Checks the rows for invalid words
bool horizontal_checker(std::vector<std::string> words, std::vector<std::string> dictionary){
	int invalidCount = 0;
	for(unsigned int i =0; i<words.size(); i++){
		bool valid= false;
		std::string str;
		for(unsigned int j = 0; j<words[i].length(); j++){
			if(words[i][j] != '#'){
				str = str + words[i][j];

			}
			if (words[i][j] == '#' || str.length() < 1){
				str = "";
			}
			if((words[i][j] == '#' || str.length()==words[i].length()) &&  str.length() > 1){				
				for(unsigned int k = 0; k < dictionary.size(); k++){
					if(dictionary[k]==str){
						valid = true;
						break;
					}
				}
				if(valid == false){
					invalidCount++;
					std::cout << "'"<< str << "' is not a word"<<std::endl;
				}
				str = "";
			}
		}
	}
	if(invalidCount==0){
		return true;
	}
	else{
		return false;
	}
}

//Checks the columns for invalid words
bool vertical_checker(std::vector<std::string> words, std::vector<std::string> dictionary){
	int invalidCount = 0;
	for(unsigned int i =0; i<words[0].length(); i++){
		bool valid= false;
		std::string str;
		for(unsigned int j = 0; j<words.size(); j++){
			if(words[j][i] != '#'){
				str = str + words[j][i];
			}
			if (words[j][i] == '#' || str.length() < 1){
				str = "";
			}
			if((words[j][i] == '#' || str.length()==words.size()) &&  str.length() > 1){				
				for(unsigned int k = 0; k < dictionary.size(); k++){
					if(dictionary[k]==str){
						valid = true;
						break;
					}
				}
				if(valid == false){
					invalidCount++;
					std::cout <<"'" << str << "' is not a word"<<std::endl;
				}
				str = "";
			}
			
		}
	}
	if(invalidCount==0){
		return true;
	}
	else{
		return false;
	}
}

//Prints out ASCII grid
void print(std::vector<std::string> words){
	int rows = words.size();
	int cols = words[0].length();
	for(int i = 0; i < rows; i++){
		std::string str1="|";
		std::string str2="|";
		std::string str3;
		for(int j = 0; j<cols; j++){
			str3 = str3 + "+----";
			if(words[i][j] == '#'){
				str1 = str1 + "####|";
				str2 = str2 + "####|";
			}
			else{
				str1 = str1 + "    |";
				str2 = str2 + "    |";
			}
			
		}
		str3 = str3 + "+";
		std::cout << str3 << std::endl;
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;
	}
	std::string str3;
	for(int j = 0; j<cols; j++){
		
		str3 = str3 + "+----";
	}
	str3 = str3 + "+";
	std::cout << str3 << std::endl;
}

//Prints out the coordinates for each word
void print_coordinates(std::vector<std::string> words){
	for(int i =0; i<words.size(); i++){
		std::string str;
		int word_start;
		for(int j = 0; j<words[i].length(); j++){
			if(words[i][j] != '#'){
				if(str.length()==0){
					word_start = j;
				}
				str = str + words[i][j];
				
			}
			if(str.length() > 1){
				
				if(words[i][j] == '#' || j==words[i].length()-1) {
					std::cout << "(" << i << "," << word_start << ") ACROSS " << str << std::endl;
					str = "";
				}
			}
			if (words[i][j] == '#' && str.length() < 2){
				str = "";
			}
		}
	}
	
	for(int i =0; i<words[0].length(); i++){
		std::string str;
		int word_start;
		for(int j = 0; j<words.size(); j++){
			if(words[j][i] != '#'){
				if(str.length()==0){
					word_start = j;
				}
				str = str + words[j][i];
			}
			if(str.length() > 1){
				if(words[j][i] == '#' || j==words.size()-1){
					std::cout << "(" << word_start << "," << i << ") DOWN " << str << std::endl;
					str="";
				}
			}
			if (words[j][i] == '#' && str.length() < 2){
				str = "";
			}
		}
	}
}


void print_numbered(std::vector<std::string> words){
	
	std::vector<std::pair<int,int> > across;
	std::vector<std::pair<int,int> > down;
	for(int i =0; i<words.size(); i++){
		std::string str;
		int word_start;
		for(int j = 0; j<words[i].length(); j++){
			if(words[i][j] != '#'){
				if(str.length()==0){
					word_start = j;
				}
				str = str + words[i][j];
				
			}
			if(str.length() > 1){
				
				if(words[i][j] == '#' || j==words[i].length()-1) {
					across.push_back(std::make_pair(i,word_start));
				}
			}
			if (words[i][j] == '#' && str.length() < 2){
				str = "";
			}
		}
	}
	
	for(int i =0; i<words[0].length(); i++){
		
		std::string str;
		int word_start;
		for(int j = 0; j<words.size(); j++){
			if(words[j][i] != '#'){
				if(str.length()==0){
					word_start = j;
				}
				str = str + words[j][i];
			}
			if(str.length() > 1){
				if(words[j][i] == '#' || j==words.size()-1){
					down.push_back(std::make_pair(word_start,i));
				}
			}
			if (words[j][i] == '#' && str.length() < 2){
				str = "";
			}
		}
	}
	
	std::vector<std::pair<int,int> > all;
	for(int i = 0; i < across.size(); i++){
		all.push_back(across[i]);
	}
	for(int i = 0; i < down.size(); i++){
		all.push_back(down[i]);
	}
	
	/*
	std::vector<std::pair<std::pair<int,int>,string> > across_sorted;
	std::pair <int,int> max;
	std::pair<std::pair<int,int>,string> temp_vec;
	while(across_sorted.size()<across.size()){
		std::pair <int,int> temp;
		max = std::max(across[0].first,across[0].first);
		for(int i = 0; i<across.size()-1; i++){
			temp = std::max(across[i].first,across[i+1].first);
			if(temp<max){
				max = temp;
				if(max == across[i].first){
					temp_vec = across[i+1];
				}
				else{
					temp_vec = across[i];
				}
			}
		}
		across_sorted.push_back(temp_vec);
	}
	
	std::vector<std::pair<std::pair<int,int>,string> > down_sorted;
	std::pair <int,int> max1;
	std::pair<std::pair<int,int>,string> temp_vec1;
	while(down_sorted.size()<down.size()){
		std::pair <int,int> temp;
		max1 = std::min(down[0].first,down[0].first);
		for(int i = 0; i<down.size()-1; i++){
			temp = std::max(down[i].first,down[i+1].first);
			if(temp>max1){
				max1 = temp;
				
				if(max1 == down[i].first){
					temp_vec1 = down[i+1];
				}
				else{
					temp_vec1 = down[i];
				}
				
			}
		}
		down_sorted.push_back(temp_vec1);
	}
	
	std::vector<std::pair<std::pair<int,int>,string> > all_sorted;
	std::pair <int,int> min2;
	std::pair<std::pair<int,int>,string> temp_vec2;
	while(all_sorted.size()<down.size() + across.size()){
		std::pair <int,int> temp;
		if(across.size() <= down.size()){
			min2 = std::min(down[0].first,down[0].first);
			for(int i = 0; i<across.size(); i++){
				temp = std::min(across_sorted[i].first,down_sorted[i].first);
				if(temp<min2){
					min2 = temp;
					//temp_vec.pop_back();
				
					if(min2 == across_sorted[i].first){
						temp_vec2 = across_sorted[i];
					}
					else{
						temp_vec2 = down_sorted[i];
					}
				//temp_vec = min;
				//std::cout<< temp_vec2.first.first << std::endl;
				}	
			}
			all_sorted.push_back(temp_vec2);
			for(int j=across.size(); j<down_sorted.size(); j++){
				all_sorted.push_back(down_sorted[j]);
			}
		}
		//std::cout << all_sorted.size() << "sdfasdf" << std::endl;
		//std::cout << down_sorted.size() + across_sorted.size() << std::endl;
		if(across.size() > down.size()){
			min2 = std::min(down_sorted[0].first,down_sorted[0].first);
			for(int i = 0; i<down_sorted.size(); i++){
				temp = std::min(down_sorted[i].first,across_sorted[i].first);
				if(temp<min2){
					min2 = temp;
					//temp_vec.pop_back();
				
					if(min2 == down_sorted[i].first){
						temp_vec2 = down_sorted[i];
					}
					else{
						temp_vec2 = across_sorted[i];
					}
				//temp_vec = min;
				
				}	
			}
			all_sorted.push_back(temp_vec2);
			for(int j=down.size(); j<across_sorted.size(); j++){
				all_sorted.push_back(across_sorted[j]);
			}
		}
		
	}
	
	std::vector<std::pair<int,int> > coor_sorted;
	for(int i = 0; i<all_sorted.size(); i++){
		coor_sorted.push_back(all_sorted[i].first);
	}
	
	for(int k = 0; k < coor_sorted.size(); k++){
		std::cout  << coor_sorted[k].first << std::endl;
		std::cout  << coor_sorted[k].second << std::endl;
	}
	*/
	int rows = words.size();
	int cols = words[0].length();
	int count = 1;
	int zero = 0;
	for(int i = 0; i < rows; i++){
		std::string str1="|";
		std::string str2="|";
		std::string str3;
		for(int j = 0; j<cols; j++){
			str3 = str3 + "+----";
			if(words[i][j] == '#'){
				str1 = str1 + "####|";
				str2 = str2 + "####|";
			}
			else{				
				//std::cout  << k << std::endl;
				stringstream intStr;
				for(int k = 0; k < all.size(); k++){
					if(i==all[k].first && j==all[k].second){
						if(i == 0 & j ==0){
							if(zero > 0){
								continue;
							}
							zero++;
						}
						std::cout << all[k].first << std::endl;
						std::cout << all[k].second << std::endl;
						intStr << count;
						std::string num = intStr.str();
						str1 = str1 + num + "   |";
						//std::cout << count << std::endl;
						count++;
						//coor_sorted.erase(coor_sorted.begin());
						break;
					}
					else{
						str1 = str1 + "    |";
					}
				}
				//std::cout << coor_sorted.size() << std::endl;
				str2 = str2 + "    |";
			}
			
		}
		str3 = str3 + "+";
		std::cout << str3 << std::endl;
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;
	}
	std::string str3;
	for(int j = 0; j<cols; j++){
		
		str3 = str3 + "+----";
	}
	str3 = str3 + "+";
	std::cout << str3 << std::endl;
	
}
int main(int argc, char* argv[]){
	
	std::ifstream infile(argv[1]);
	std::ifstream infile2(argv[2]);
	if (!infile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	if (!infile2.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}
	
	std::vector<std::string> words;
	std::string word;
	while (infile >> word) {
		words.push_back(word);
	}
	std::vector<std::string> dic;
	while(infile2 >> word){
		dic.push_back(word);
	}
	
	if (argc == 4){
		std::string argStr = argv[3];
		if(argStr =="--print"){
			print(words);
		}
		if(argStr =="--print_coordinates"){
			print(words);
			std::cout<<std::endl;
			print_coordinates(words);
			
		}
		if(argStr =="--print_numbered"){
			print_numbered(words);
		}
	}
	else if(argc==3){
		
		
		bool horizontal = true;
		
		horizontal= horizontal_checker(words,dic);
		bool vertical = true;
		vertical = vertical_checker(words,dic);
		if(horizontal && vertical){
			std::cout << "valid crossword puzzle" << std::endl;
		}		
	}
}