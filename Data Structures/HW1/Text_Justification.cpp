#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

/*
std::string super_long(int num, std::string& word, std::vector<std::string>& sentence, std::string& str){
	std::string str2;
	if(str.length()>0){
		sentence.push_back(str + " ");
	}
	str.erase();
	//double numera = word.length()/(num-1);
	//std::cout << int(word.length())/num << std::endl;
	for(int i=0; i<ceil(word.length()/(num-1)) + 1; i++){
		str = str +"| ";
		for(int k =(num) * i; k<num*(i+1)-1;k++){
			if(i==0){
				str = str + word[k];
			}else{
				str = str + word[k-1];
			}
			if(k==word.length()){
				break;
			}
			//std::cout << i << std::endl;
			//std::cout << str << std::endl;
		}
		if(i != ceil(word.length()/(num-1))){
			str += "- |\n";
			sentence.push_back(str);
			str.erase();
		}
	}
	return str;
	std::cout << str << std::endl;
}*/

void flush_left(int num, std::vector<std::string> words, std::ofstream& outfile){
	std::string str = "| ";
	std::vector<std::string> sentence;
	//std::cout << str << std::endl;
	for(int i = 0; i < words.size();i++){
		str = str + words[i] + " ";
		
		if (str.length() > num+3){
			str.erase(str.length()-words[i].length()-1,words[i].length()+1);
			//std::cout << str.length() << std::endl;
			//std::cout << num+4-str.length() << std::endl;
			int strlen = str.length();
			for(int j=0; j<num+3-strlen; j++){
				str = str + " ";
				//std::cout << num+4-str.length() << std::endl;
			}
			str = str +"|";
			sentence.push_back(str);
			//std::cout<<words[i]<<std::endl;
			str = "| " + words[i] + ' ';
		}
		if(i==words.size()-1){
			int strlen = str.length();
			for(int j=0; j<num+3-strlen; j++){
				str = str + " ";
				//std::cout << num+4-str.length() << std::endl;
			}
			sentence.push_back(str);
		}
	}
	sentence[sentence.size()-1] = sentence[sentence.size()-1] + "|";
	//std:: cout << sentence[0] << std::endl;
	std::string str2;
	for(int j=0; j < sentence.size();j++){
		str2 = str2 + sentence[j];
		if(j!=sentence.size()-1){
			str2 = str2 +"\n";
		}
	}
	outfile << str2 << std::endl;
}

void flush_right(int num, std::vector<std::string> words, std::ofstream& outfile){
	std::string str = "| ";
	std::vector<std::string> sentence;
	//std::cout << str << std::endl;
	for(int i = 0; i < words.size();i++){
		str = str + words[i] + " ";
		
		if (str.length() > num+3){
			str.erase(str.length()-words[i].length()-1,words[i].length()+1);
			//std::cout << str.length() << std::endl;
			//std::cout << num+4-str.length() << std::endl;
			int strlen = str.length();
			for(int j=0; j<num+3-strlen; j++){
				str.insert(1," ");
				//std::cout << num+4-str.length() << std::endl;
			}
			str = str +"|";
			sentence.push_back(str);
			//std::cout<<words[i]<<std::endl;
			str = "| " + words[i] + ' ';
		}
		if(i==words.size()-1){
			int strlen = str.length();
			for(int j=0; j<num+3-strlen; j++){
				str.insert(1," ");
				//std::cout << num+4-str.length() << std::endl;
			}
			sentence.push_back(str);
		}
	}
	
	sentence[sentence.size()-1] = sentence[sentence.size()-1] + "|";
	//std:: cout << sentence[0] << std::endl;
	std::string str2;
	for(int j=0; j < sentence.size();j++){
		str2 = str2 + sentence[j];
		if(j!=sentence.size()-1){
			str2 = str2 +"\n";
		}
	}
	outfile << str2 << std::endl;
}


void flush_full(int num, std::vector<std::string> words, std::ofstream& outfile){
	std::string str = "| ";
	std::vector<std::string> sentence;
	int num_words = 0;
	
	//std::cout << str << std::endl;
	
	for(int i = 0; i < words.size();i++){
		/*if(words[i].length() > num){
			super_long(num,words[i],sentence,str);
		}*/
		str = str + words[i] + " ";
		num_words = num_words + 1;
		int count = 1;
		
		
		
		if (str.length() > num+4){
			str.erase(str.length()-words[i].length()-1,words[i].length()+1);
			num_words = num_words - 1;
			//std::cout << str.length() << std::endl;
			int loopCount = 0;
			
			while(str.length() < num+3){
				int wordlen = 2;
				if(i-num_words != 0){
					num_words++;
					count++;
				}
				for(int j=num_words; j>count; j = j-1){
					//std::cout << j << std::endl;
					str.insert(words[i-j].length()+wordlen," ");
					//std::cout << words[i-j] << std::endl;
					//std::cout << str << std::endl;
					wordlen += words[i-j].length() + words[i-(j-1)].length() + loopCount ;
					//std::cout << num+4-str.length() << std::endl;
				}
				loopCount += 1;
			}
			num_words = 0;
			str = str +"|";
			sentence.push_back(str);
			//std::cout<<words[i]<<std::endl;
			str = "| " + words[i] + ' ';
		}
		if(i==words.size()-1){
			int strlen = str.length();
			for(int j=0; j<num+3-strlen; j++){
				str = str + " ";
				//std::cout << num+4-str.length() << std::endl;
			}
			sentence.push_back(str);
		}
	}
	
	sentence[sentence.size()-1] = sentence[sentence.size()-1] + "|";
	//std:: cout << sentence[0] << std::endl;
	std::string str2;
	for(int j=0; j < sentence.size();j++){
		str2 = str2 + sentence[j];
		if(j!=sentence.size()-1){
			str2 = str2 +"\n";
		}
	}
	outfile << str2 << std::endl;
}



//std::atoi

int main(int argc, char* argv[]){
	std::ifstream infile(argv[1]);
	if (!infile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	std::ofstream outfile(argv[2]);
	if (!outfile.good()) {
		std::cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}
	
	std::vector<std::string> words;
	std::string word;
	while (infile >> word) {
		words.push_back(word);
	}
	
	std::string dashes;
	for (int i=0; i<std::atoi(argv[3]) + 4;i++){
		dashes = dashes + "-";
	}
	
	outfile << dashes << std::endl;
	//std::cout << std::string(argv[3],'-') << std::endl;
	//std::cout <<argv[4]<<std::endl;
	std::string argStr = argv[4];
	if(argStr=="flush_left"){
		flush_left(std::atoi(argv[3]), words, outfile);
	}
	
	if (argStr == "flush_right"){
		flush_right(std::atoi(argv[3]), words, outfile);
	}
	
	if (argStr == "full_justify"){
		flush_full(std::atoi(argv[3]), words, outfile);
	}
	outfile << dashes << std::endl;	
	return 0;
}