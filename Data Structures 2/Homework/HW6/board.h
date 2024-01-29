#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <cassert>

class Board {
public:

  // CONSTRUCTOR
  Board(const std::string& filename, bool inverse=false);

  // PRINT FUNCTIONS
  void print() const;
  void printPuzzle() const;
  void printInverse() const;

  // NAIVE SOLVER METHODS
  void zeroEdges();
  void fourEdges();
  
  // NAIVE GENERATOR METHOD 
  void labelAllCells();

  
  int single_loop_recursion(int row, int col, int horizontal_value, int vertical_value, Board& b);
	
  
private:

  // helper function for labelAllCells
  int countEdges(int i, int j);

  // REPRESENTATION
	std::vector<std::vector<int> > board;
	std::vector<std::vector<int> > horizontal;
	std::vector<std::vector<int> > vertical;
  
 int row, col;
};


#endif
