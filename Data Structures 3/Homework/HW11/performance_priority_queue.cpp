#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();


void priority_queue_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
   std::priority_queue<std::string,std::vector<std::string> > pq(input_data,input_data+input_count);
   
    

  if (operation == "sort") {
	  //adds elements of the queue to the output_data from the bottom
	output_count = input_count;
    for (int i = output_count-1; i >=0 ; --i){
		output_data[i] = pq.top();
		pq.pop();
	}
  } else if (operation == "remove_dups_same_order") {
	  //Impossible
	  exit(0);
  } else if (operation == "remove_dups_any_order") {
	  //checks the top of the queue and only adds to the output_data if the next word in the queue doesn't match the previous one
	std::string word;
	int count = 0;
	while(true){
		word = pq.top();
		pq.pop();
		if(pq.empty()){
			output_data[count] = word;
			break;
		}		
		if(word != pq.top()){
			output_data[count] = word;
			count++;
		}
	}
	output_count = count+1;
	  
	  
	  
	  
	  
  } else if (operation == "mode") {
	  //pops through the queue, counting the number of each word that is found, until the queue is empty
	  //when the count is greater than the max, the max is replaced by the count and output_data[0] becomes the word
	std::string word;
	std::string word2 = pq.top();
	pq.pop();
	output_data[0] = word2;
	int max = 1;
	int count = 1;
	while(pq.empty() == false){
		word = pq.top();
		if(word == word2){
			count++;
			if(count > max){
				max = count;
				output_data[0] = word;
			}
			word2 = word;
		}
		else{
			count = 1;
			word2 = word;
		}
		pq.pop();
	}
	output_count = 1;
	  
	  
	  
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
