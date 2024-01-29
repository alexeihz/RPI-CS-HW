#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "board.h"


int main(int argc, char* argv[]) {

  // Handle the command line arguments
  assert (argc >= 2);

  // Default values
  bool loop_analysis = false;
  bool all_solutions = false;
  bool single_loop = false;
  bool inverse = false;
  bool ascii_art = true;
  
  // puzzle file (regular or inverse) is always first argument
  std::string puzzle_file = argv[1];
  
  // loop through the optional arguments
  for (int i = 2; i < argc; i++) {
    if (std::string(argv[i]) == "--all_solutions") {
      all_solutions = true;
    } else if (std::string(argv[i]) == "--loop_analysis") {
      loop_analysis = true;
    } else if (std::string(argv[i]) == "--single_loop") {
      loop_analysis = true;
      single_loop = true;
    } else if (std::string(argv[i]) == "--inverse") {
      inverse = true;
    } else if (std::string(argv[i]) == "--no_ascii_art") {
      ascii_art = false;
    } else {
      std::cerr << "UNKNOWN OPTION: " << argv[i] << std::endl;
      assert(0);
    }
  }
  // the inverse and all_solutions flags should not be used together
  if (inverse) { assert (!all_solutions); }
  

  if (!inverse) {

    // ------------------------------------------------------------------------
    // Regular mode: Find the path that matches the input cell labels
    Board b(puzzle_file);
	Board c(puzzle_file);

    std::vector<Board> solutions;
    std::vector<Board> multiloop_solutions;


    // --------------------------
    // FILL IN YOUR SOLVER HERE
    b.zeroEdges();
    b.fourEdges();
	c.zeroEdges();
    c.fourEdges();
	int horizontal_value, vertical_value;
	
	int works = b.single_loop_recursion(0,0,0,0,c) + b.single_loop_recursion(0,0,0,1,c) + b.single_loop_recursion(0,0,1,0,c) + b.single_loop_recursion(0,0,1,1,c);
	
    c.print();
    // --------------------------
    
    
    if (solutions.size() + multiloop_solutions.size() == 0) {
      std::cout << "No Solutions" << std::endl;
    }
    else if (all_solutions) {
      if (loop_analysis) {
        std::cout << "Found " << solutions.size() << " Single Loop Solution(s)";
        if (!single_loop) {
          std::cout << " and " << multiloop_solutions.size() << " Multi-Loop Solution(s)";
        }
        std::cout << std::endl;
      } else {
        std::cout << "Found " << solutions.size() << " Solution(s)" << std::endl;
      }
    }

  } else {

    // ------------------------------------------------------------------------
    // Inverse mode: Find a cell labeling whose solution is the input path
    Board b(puzzle_file, true);

    
    // --------------------------
    // FILL IN YOUR INVERSE GENERATOR HERE
    b.labelAllCells();
    // --------------------------

    
    if (ascii_art) {
      b.print();
    } else {
      b.printPuzzle();
    }
    
 }
}
