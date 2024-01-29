// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cassert>
#include <cstdlib>
#include <typeinfo>
#include <numeric>



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
//typedef  /*** YOUR TYPE ***/  MY_MAP;

//2 typedefs are needed to handle both window sizes of 2 and 3
typedef  std::map<std::string, std::map<std::string, int> >  MY_MAP;
typedef  std::map<std::string, std::map<std::string,std::map<std::string, int> > > MY_MAP2;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
		// skip whitespace before a word starts
		istr.get(c);
		if (word != "") {
		// break words at whitespace
			return true;
		}
    } else if (c == '"') {
		// double quotes are a delimiter and a special "word"
		if (word == "") {
			istr.get(c);
			word.push_back(c);
		}
		return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
		istr.get(c);
		word.push_back(tolower(c));
    } else {
		// ignore this character (probably punctuation)
		istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}


// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data,const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  
  std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << "\n" << std::endl;
  
  //loads info from file into data for a window size of 2
	std::string word1;
	std::string word2;
	ReadNextWord(istr, word1);
	while (ReadNextWord(istr, word2)) {
		std::map<std::string, std::map<std::string, int> >::iterator itr;
		itr = data.find(word1);
		
		if (itr == data.end()) {
			std::map<std::string, int> mapp;
			mapp.insert(std::pair<std::string,int>(word2, 1));
			data.insert(std::pair<std::string,std::map<std::string,int> >(word1, mapp));
		} else {
			data[word1][word2]++;
		}
		
		word1 = word2;
	}
	std::map<std::string, std::map<std::string, int> >::iterator itr;
	itr = data.find(word1);
	std::map<std::string, int> mapp;
	if(itr == data.end()){
		mapp.insert(std::pair<std::string,int>(" ", 1));		
		data.insert(std::pair<std::string,std::map<std::string,int> >(word1, mapp));	
	}
	else{
		data[word1].insert(std::pair<std::string,int>(" ", 1));
		
		
	}	
}
  
 



void LoadSampleText(MY_MAP2 &data, const std::string &filename, int window, const std::string &parse_method) {
	// open the file stream
	std::ifstream istr(filename.c_str());
	if (!istr) { 
		std::cerr << "ERROR cannot open file: " << filename << std::endl; 
		exit(1);
	} 
	// verify the window parameter is appropriate
	if (window < 2) {
		std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
	}
	  // verify that the parse method is appropriate
	bool ignore_punctuation = false;
	if (parse_method == "ignore_punctuation") {
		ignore_punctuation = true;
	} else {
		std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
		exit(1);
	}
	
	std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << "\n" << std::endl;
	//loads info from file into data for a window size of 3
	std::string word;
	ReadNextWord(istr,word);
	std::string word1;
	std::string word2;
	std::string word3;
	ReadNextWord(istr, word1);
	ReadNextWord(istr, word2);
	while (ReadNextWord(istr, word3)) {
		std::map<std::string, std::map<std::string, std::map<std::string, int> > >::iterator itr;
		itr = data.find(word1);
		
		if (itr == data.end()) {
			std::map<std::string, int> mappp;
			mappp.insert(std::pair<std::string,int>(word3, 1));
			std::map<std::string, std::map<std::string, int> > mapp;
			mapp.insert(std::pair<std::string,std::map<std::string,int> >(word2, mappp));
			data.insert(std::pair<std::string,std::map<std::string,std::map<std::string,int> > >(word1, mapp));
		} else {
			data[word1][word2][word3] += 1;
		}
		
		word1 = word2;
		word2 = word3;
	}
}



int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;
  MY_MAP2 data2;

  // Parse each command
  std::string command;  
	int window;  
	while (std::cin >> command) {
		// load the sample text file
		if (command == "load") {
		  std::string filename;
		  //int window;
		  std::string parse_method;
		  std::cin >> filename >> window >> parse_method;      
			if(window == 2){
				LoadSampleText(data,filename,window,parse_method);
			}
			else if(window == 3){
				LoadSampleText(data2,filename,window,parse_method);
				
			}
		} 


		else if (command == "print") {
		  std::vector<std::string> sentence = ReadQuotedWords(std::cin);
			std::string str = sentence[0];
			for(unsigned i = 1; i < sentence.size(); i++){
				str = str + " " + sentence[i];
			}
			MY_MAP::iterator itr;
			std::map<std::string,int>::iterator itr2;
			int count = 0;
			//for window size of 2, prints the portion of the map structure with the choices for the next word
			if(window == 2){
				itr = data.find(sentence[0]);
				if(itr != data.end()){
					if(sentence.size() == 1){
						for(itr2 = data[sentence[0]].begin(); itr2 != data[sentence[0]].end(); ++itr2){
							count = count + (itr2 -> second);
						}
					}
					else{
						itr2 = data[sentence[0]].find(sentence[1]);
						if(itr2 != data[sentence[0]].end()){
							count = count + (itr2 -> second);
						}
					}
				}
				std::cout << str << " (" << count << ")" << std::endl;
				for(itr2 = data[sentence[0]].begin(); itr2 != data[sentence[0]].end(); ++itr2){
					if(itr2 -> first != " "){
						std::cout << str << " " << itr2 -> first << " (" << itr2 -> second << ")" << std::endl;
					}
				}
				
			}
			//for window size of 3, prints the portion of the map structure with the choices for the next word
			else if(window == 3){
				MY_MAP2::iterator itr3;
				itr3 = data2.find(sentence[0]);
				std::vector<int> vec;
				
				if(itr3 != data2.end()){
					if(sentence.size() == 1){
						for(itr = data2[sentence[0]].begin(); itr != data2[sentence[0]].end(); ++itr){
							for(itr2 = data2[sentence[0]][itr->first].begin(); itr2 != data2[sentence[0]][itr->first].end(); ++itr2){
								count = count + (itr2 -> second);
							}
						}
						std::cout << str << " (" << count << ")" << std::endl;
						for(itr = data2[sentence[0]].begin(); itr != data2[sentence[0]].end(); ++itr){
							int count2 = 0;
							for(itr2 = data2[sentence[0]][itr->first].begin(); itr2 != data2[sentence[0]][itr->first].end(); ++itr2){
								count2 = count2 + (itr2 -> second);
							}
							std::cout << str << " " << itr -> first << " (" << count2 << ")" << std::endl;
						}
					}
					else if(sentence.size() == 2){
						itr = data2[sentence[0]].find(sentence[1]);
						for(itr2 = data2[sentence[0]][sentence[1]].begin(); itr2 != data2[sentence[0]][sentence[1]].end(); ++itr2){
							count = count + (itr2 -> second);
						}
						std::cout << str << " (" << count << ")" << std::endl;
						for(itr2 = data2[sentence[0]][sentence[1]].begin(); itr2 != data2[sentence[0]][sentence[1]].end(); ++itr2){
							std::cout << str << " " << itr2 -> first << " (" << itr2 -> second << ")" << std::endl;
						}
					}
				}
			}
			std::cout << std::endl;
		}
		
		// generate the specified number of words 
		else if (command == "generate") {
			std::vector<std::string> sentence = ReadQuotedWords(std::cin);
			// how many additional words to generate
			int length;
			std::cin >> length;
			std::string selection_method;
			std::cin >> selection_method;
			bool random_flag;
			if (selection_method == "random") {
				random_flag = true;
			} else {
				assert (selection_method == "most_common");
				random_flag = false;
			}
			
			std::string str = sentence[0];
			for(unsigned i = 1; i < sentence.size(); i++){
				str = str + " " + sentence[i];
			}
			std::cout << str;
			std::map<std::string,int>::iterator itr;
			std::string str_word;
			
			if(window == 2){
				str_word = sentence[0];
				//for window size 2, given a word ,randomly picks an element to follow the previous word for the given length
				if(random_flag){
					for(int i = 0; i<length; i++){
						int rand_vari = std::rand() % data[str_word].size();
						int count = 0;
						for(itr = data[str_word].begin(); itr != data[str_word].end(); ++itr){
							
							if(count == rand_vari){
								break;
							}
							count++;
						}
						std::cout << " " << itr -> first;
						str_word = itr -> first;
					}
					std::cout << std::endl;
				}
				//for window size 2, given a word ,selects the most common word that comes after the previous one for the given length
				else{
					for(int i = 0; i<length; i++){
						std::map<std::string,int>::iterator itr2 = data[str_word].begin();
						for(itr = data[str_word].begin(); itr != data[str_word].end(); ++itr){
							if(itr->second > itr2->second){
								itr2 = itr;
							}
						}
						std::cout << " " << itr2 -> first;
						str_word = itr2 -> first;
					}
					std::cout << std::endl;
				}

			}
			else if(window == 3){
				std::map<std::string,std::map<std::string,int> >::iterator itr2;
				if(sentence.size()==1){
					str_word = sentence[0];
					
				}
				else if (sentence.size() == 2){
					str_word = sentence[1];
					
				}
				//for window size 3, given a word ,randomly picks an element to follow the previous word for the given length
				if(random_flag){
					int i = 0;
					while(i<length){
						int rand_vari = std::rand() % data2[str_word].size();
						int count = 0;
						for(itr2 = data2[str_word].begin(); itr2 != data2[str_word].end(); ++itr2){
							
							if(count == rand_vari){
								break;
							}
							count++;
						}
						std::cout << " " << itr2 -> first;
						i++;
						if(i>=length){
							break;
							
						}
						int count2 = 0;
						int rand_vari2 = std::rand() % data2[str_word][itr2->first].size();
						for(itr = data2[str_word][itr2->first].begin(); itr != data2[str_word][itr2->first].end(); ++itr){
							if(count2 == rand_vari2){
								break;
							}
							count2++;
							
						}
						std::cout << " " << itr -> first;
						str_word = itr -> first;
						i++;
						
					}
					std::cout << std::endl;
				}
				//for window size 3, given a word ,selects the most common word that comes after the previous one for the given length
				else{
					int i = 0;
					int count = 0;
					str_word = sentence[0];
					std::string str_word2;
					if(sentence.size()==1){
						
						
						std::map<std::string,std::map<std::string,int> >::iterator itr3 = data2[str_word].begin();
						
						for(itr2 = data2[str_word].begin(); itr2 != data2[str_word].end(); ++itr2){
							int count2 = 0;
							for(itr = data2[str_word][itr2->first].begin(); itr != data2[str_word][itr2->first].end(); ++itr){
								count2 = count2 + itr->second;
								
							}
							if(count2 > count){
								itr3 = itr2;
								count = count2;
							}												
						}
					
						str_word2 = itr3-> first;
						
						
						std::map<std::string,int>::iterator itr4= data2[str_word][str_word2].begin();
						for(itr = data2[str_word][str_word2].begin(); itr != data2[str_word][str_word2].end(); ++itr){
							if(itr->second > itr4->second){
								itr4 = itr;
							}
						}
						
						str_word = str_word2;
						str_word2 = itr4-> first;
						std::cout << " " << str_word << " "<< str_word2;
						i=i+2;
					}
					else if(sentence.size()==2){
						str_word2 = sentence[1];
						std::map<std::string,int>::iterator itr4= data2[str_word][str_word2].begin();
						for(itr = data2[str_word][str_word2].begin(); itr != data2[str_word][str_word2].end(); ++itr){
							if(itr->second > itr4->second){
								itr4 = itr;
							}
						}
						
						str_word = str_word2;
						str_word2 = itr4-> first;
						std::cout << " "<< str_word2;
						i=i+1;
					}
					while(i<length){
						std::map<std::string,int>::iterator itr4= data2[str_word][str_word2].begin();
						for(itr = data2[str_word][str_word2].begin(); itr != data2[str_word][str_word2].end(); ++itr){
							if(itr->second > itr4->second){
								itr4 = itr;
							}
						}
						
						str_word = str_word2;
						str_word2 = itr4-> first;
						std::cout << " " << str_word2;
						
						
						i++;
					}
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
		} else if (command == "quit") {
			break;
		} else {
			std::cout << "WARNING: Unknown command: " << command << std::endl;
		}
	}
}
