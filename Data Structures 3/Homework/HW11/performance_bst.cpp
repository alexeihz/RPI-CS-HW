#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>



// defined in performance.cpp
void usage();


void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
   //std::set<std::string> st;
  // OR 
  std::map<std::string,int> mp;
  std::map<std::string,int>::iterator itr;
 
 
  

  if (operation == "sort") { 
  
   //fills the bst
	for (int i = 0; i < input_count; i++){ 
		if(mp.find(input_data[i]) == mp.end()){
			mp.insert( std::pair<std::string,int>(input_data[i],1) );
		}
		else{
			mp[input_data[i]]++;
		}
	}
  
  
	//map is already sorted so output_data is populated in order
		int i = 0;
		for (itr = mp.begin(); itr != mp.end(); ++itr){
			for(int j = 0; j < (*itr).second; j++){
				output_data[i] = (*itr).first;
				i++;
			}
		}
		output_count = input_count;
	
  } else if (operation == "remove_dups_same_order") {
	   //fills the bst
		for (int i = 0; i < input_count; i++){ 
			if(mp.find(input_data[i]) == mp.end()){
				mp.insert( std::pair<std::string,int>(input_data[i],i) );
			}
		}
	
		output_count = mp.size();
		int count = 0;
		
		std::string word;
		for(int i = 0; i<output_count; i++){
			int min = 999;
			for(itr = mp.begin(); itr != mp.end(); ++itr){
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
			mp.erase(word);
		}
	  
	  
  } else if (operation == "remove_dups_any_order") {
	  
	  
	  
	   //fills the bst
	for (int i = 0; i < input_count; i++){ 
		if(mp.find(input_data[i]) == mp.end()){
			mp.insert( std::pair<std::string,int>(input_data[i],1) );
		}
		else{
			mp[input_data[i]]++;
		}
	}
	  
	  
	  //map has already removed the duplicates
		output_count = mp.size();
		int i = 0;
		for (itr = mp.begin(); itr != mp.end(); ++itr){
			output_data[i] = (*itr).first;
			i++;
		}
	
  } else if (operation == "mode") {
	   
	  
	   //fills the bst
	for (int i = 0; i < input_count; i++){ 
		if(mp.find(input_data[i]) == mp.end()){
			mp.insert( std::pair<std::string,int>(input_data[i],1) );
		}
		else{
			mp[input_data[i]]++;
		}
	}
	  
	  
	  //finds the key with the largest value
		int max = 0;
		std::string word;
		for (itr = mp.begin(); itr!= mp.end(); ++itr){ 
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
