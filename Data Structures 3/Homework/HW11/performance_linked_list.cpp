#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


void list_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;
  std::list<std::string>::iterator itr;
  
  //populate the list
  for (int i = 0; i < input_count; i++){
    lst.push_back(input_data[i]);
  }
  



  if (operation == "sort") {
	lst.sort();
	output_count = input_count;
	int i = 0;
    for (itr = lst.begin(); itr != lst.end(); itr++){
		output_data[i] = *itr;
		i++;
	}
	
  } else if (operation == "remove_dups_same_order") {
	  
	  // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
	int i = 0;
    for (itr = lst.begin(); itr != lst.end(); ++itr) {
		bool dup = false;
		for (int j = 0; j < output_count; j++) {
			if (*itr == output_data[j]) {
				dup = true;
				break;
			}
		}
      // if it has not already been added to the output list
		if (!dup) {
			output_data[output_count] = input_data[i];
			output_count++;
		}
		i++;
    }
	  
	
	
  } else if (operation == "remove_dups_any_order") {
	 //use list sort
	output_count = 0;
	lst.sort();
    if(lst.empty()){
      return;
    }
    std::string tmp = *(lst.begin());
    for(itr = lst.begin(); itr != lst.end(); ++itr){
      if(tmp != *itr){
        output_data[output_count] = tmp;
        output_count++;
      }
      tmp = *itr;
    }
    if(tmp != output_data[output_count-1]){
        output_data[output_count] = tmp;
        output_count++;
    }
	  

	
  } else if (operation == "mode") {
	// use the list sort algorithm
    lst.sort();
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    std::list<std::string>::iterator current = lst.begin();
    ++current;
    std::list<std::string>::iterator previous = lst.begin();
    for (; current != lst.end(); ++current, ++previous) {
      if (*current == *previous) {
	// if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }
    // save the mode to the output list
    output_count = 1;
    output_data[0] = mode;
	  
	  
	  

	  
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
