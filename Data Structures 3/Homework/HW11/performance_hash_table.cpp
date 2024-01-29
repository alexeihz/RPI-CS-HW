#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  //std::unordered_set<std::string> ht(input_count);
  // OR 
  std::unordered_map<std::string,int> ht(input_count);
  std::unordered_map<std::string,int>::iterator itr;
  
  

  
  
  if (operation == "sort") {
	//Impossible
	  exit(0);
	  
  } else if (operation == "remove_dups_same_order") {
	 //fills the hashtable
		for (int i = 0; i < input_count; i++){ 
			if(ht.find(input_data[i]) == ht.end()){
				ht.insert( std::pair<std::string,int>(input_data[i],i) );
			}
		}
	
		output_count = ht.size();
		int count = 0;
		
		std::string word;
		for(int i = 0; i<output_count; i++){
			int min = 999;
			for(itr = ht.begin(); itr != ht.end(); ++itr){
				if((*itr).second <= min){
					min = (*itr).second;
					word = (*itr).first;
				}
			}
			if(min > count){
				min = count;
			}
			output_data[min] = word;
			count++;
			ht.erase(word);
		}
	  
	  
	  
  } else if (operation == "remove_dups_any_order") {
	  
	  //populates the hashtable
		for (int i = 0; i < input_count; i++){ 
			if(ht.find(input_data[i]) == ht.end()){
				ht.insert( std::pair<std::string,int>(input_data[i],1) );
			}
			else{
				ht[input_data[i]]++;
			}
		}
	 
	  
	  //hashtable has already removed the duplicates
		output_count = ht.size();
		int i = 0;
		for (itr = ht.begin(); itr != ht.end(); itr++){
			output_data[i] = (*itr).first;
			i++;
		}
	  
	  
	  
  } else if (operation == "mode") {
	  
	  
	  //populates the hashtable
		for (int i = 0; i < input_count; i++){ 
			if(ht.find(input_data[i]) == ht.end()){
				ht.insert( std::pair<std::string,int>(input_data[i],1) );
			}
			else{
				ht[input_data[i]]++;
			}
		}
	  
	  //finds the key with the largest value
		int max = 0;
		std::string word;
		for (itr = ht.begin(); itr!= ht.end(); ++itr){ 
			if((*itr).second > max){
				max = (*itr).second;
				word = (*itr).first;
			}
		}
		output_count = 1;
		output_data[0] = word;
	  
	  
	  
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
