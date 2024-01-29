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
  // std::priority_queue<std::string,std::vector<std::string> > pq(input_data,input_data+input_count);
  
  std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);

  if (operation == "sort") {
  } else if (operation == "remove_dups") {
  } else if (operation == "mode") {
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
