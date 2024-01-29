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
  std::set<std::string> st;
  std::set<std::string> st2;
  // OR 
  std::map<std::string,int> mp;

  std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);
	
	
  if (operation == "sort") {
	  std::map<std::string,int>>::iterator itr;
	  for (itr = input_data.begin(); itr!= input_data.end(); ++itr){ 
		st.push_back(*itr);
	  }
	  

  } else if (operation == "remove_dups") {
	  std::map<std::string,int>>::iterator itr;
	  for (itr = input_data.begin(); itr!= input_data.end(); ++itr){ 
		if(itr == input_data.begin()){
			st2.push_back(*itr);
		}
		else{
			if(st2.find(*itr) == input_data.end()){
				st2.push_back(*itr);
			}
		}
	  }
	  
	  
	  
	  
  } else if (operation == "mode") {
		std::map<std::string,int>>::iterator itr;
	  for (itr = input_data.begin(); itr!= input_data.end(); ++itr){ 
		if(itr == input_data.begin()){
			mp.push_back(std::make_pair(*itr,1));
		}
		else{
			if(st2.find(*itr) == input_data.end()){
				mp.push_back(std::make_pair(*itr,1));
			}
			else{
				mp[*itr]++;
				
			}
		}
	  }
	  
	  
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
