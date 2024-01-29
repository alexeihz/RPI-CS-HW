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
  // std::unordered_set<std::string> ht(input_count);
  // OR 
  // std::unordered_map<std::string,int> ht(input_count);

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
