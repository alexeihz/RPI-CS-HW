#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>

#include "board.h"


// ============================================================================
// CONSTRUCTOR
Board::Board(const std::string& filename, bool inverse) {

  // open up the file
  std::ifstream istr(filename);
  assert (istr.good());
  
  // Regular mode: Find the path that matches the input cell labels
  if (!inverse) {
    std::string s;
    int row = 0;
    // read each row
    while (istr >> s) {
      board.push_back(std::vector<int>());
      // read each cell/column
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // we represent unlabeled cells with -1
          board[row].push_back(-1);
        } else {
          int foo = atoi(std::string(1,s[i]).c_str());
          assert (foo >= 0 && foo <= 4);
          board[row].push_back(foo);
        }
      }
      assert (board[row].size() == board[0].size());
      row++;
    }
    // all of the edges are currently unknown, which we represent with -1
    horizontal = std::vector<std::vector<int> >(board.size()+1,std::vector<int>(board[0].size(),-1));
    vertical   = std::vector<std::vector<int> >(board.size(),std::vector<int>(board[0].size()+1,-1));
	
	
	
	// rows = board.size();
	// cols = board[row].size();
  }

  // Inverse mode: Find a cell labeling whose solution is the input path
  else {
    // read the horizontal edge data
    char str[1000];
    int row = 0;
    std::string s;
    while (1) {
      // note: we use getline here because we want to handle the
      // blank line between horizontal and vertical edge data
      istr.getline(str,1000);
      s = str;
      if (s == "") break;
      horizontal.push_back(std::vector<int>());
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // no edge is represented with the value zero
          horizontal[row].push_back(0);
        } else {
          // edge is represented with the value 1
          assert (s[i] == '-');
          horizontal[row].push_back(1);
        }
      }
      assert (horizontal[row].size() == horizontal[0].size());
      row++;
    }
    assert (horizontal.size() >= 2);
    // read the vertical edge data
    row = 0;
    while (istr >> s) {
      vertical.push_back(std::vector<int>());
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // no edge is represented with the value zero
          vertical[row].push_back(0);
        } else {
          // edge is represented with the value 1
          assert (s[i] == '|');
          vertical[row].push_back(1);
        }
      }
      assert (vertical[row].size() == horizontal[0].size()+1);
      row++;
    }
    assert (vertical.size() +1 == horizontal.size());
    // note that the cell data dimensions are slightly different than
    // the horizontal and vertical edge data.  The vertical data has
    // an extra column, and the horizontal data has an extra row.
    board = std::vector<std::vector<int> >(horizontal.size()-1,std::vector<int>(horizontal[0].size(),-1));
  }
}


// ============================================================================
// SMALL HELPER ROUTINES FOR ASCII ART PRINTING CHARACTERS
char vChar(int i)  {
  if (i == -1) return '?';
  if (i == 0) return ' ';
  assert (i == 1); return '|';
}
char hChar(int i) {
  if (i == -1) return '?';
  if (i == 0) return ' ';
  assert (i == 1); return '-';
}
char valueChar(int i) {
  if (i == -1) return ' ';
  if (i == 0) return '0';
  if (i == 1) return '1';
  if (i == 2) return '2';
  if (i == 3) return '3';
  assert (i == 4); return '4';
}


// ============================================================================
// PRINT AN ASCII ART REPRESENTATION OF THE CURRENT BOARD
// Note: Yes, this function exceeds normal line width.  
void Board::print() const {
  // loop over each row of the board
  for (int j = 0; j < board.size(); j++) {
    assert (board[0].size() == board[j].size());
    // what is the rightmost vertical edge for this row?
    char right = vChar(vertical[j][board[j].size()]);
    // print the horizontal edges above the current row
    for (int i=0; i<board[j].size(); i++) { char top =hChar(horizontal[j][i]); std::cout<<"+" + std::string(5,top);                 } std::cout<<"+"<<std::endl; 
    // loop over the cells in the row
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"     ";                            } std::cout<<right<<std::endl;
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"  "<<valueChar(board[j][i])<<"  "; } std::cout<<right<<std::endl;
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"     ";                            } std::cout<<right<<std::endl;
  }
  // print the horizontal edges below the bottom row
  for   (int i=0; i<board[0].size(); i++) { char top =hChar(horizontal[board.size()][i]); std::cout<<"+" + std::string(5,top);      } std::cout<<"+"<<std::endl;
}


// print the non-ascii art version of the cell count data
// (can be used as input for the regular Slitherlink puzzle solver)
void Board::printPuzzle() const {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      if (board[j][i] == -1) {
        // unlabeled cells represented with .
        std::cout << ".";
      } else {
        std::cout << board[j][i];
      }
    }
    std::cout << std::endl;
  }
}


// print the non-ascii art version of the path data
// (can be used as input for the inverse Slitherlink puzzle generator)
void Board::printInverse() const {
  for (int j = 0; j < horizontal.size(); j++) {
    for (int i = 0; i < horizontal[j].size(); i++) {
      // it's an error to print a path with unknown edges
      assert (horizontal[j][i] != -1);
      if (horizontal[j][i] == 0) {
        // 'no edge' represented with .
        std::cout << ".";
      } else {
        assert (horizontal[j][i] == 1);
        // 'edge present' represented with -
        std::cout << "-";
      }
    }
    std::cout << std::endl;
  }
  // blank line between the data
  std::cout << std::endl;
  for (int j = 0; j < vertical.size(); j++) {
    for (int i = 0; i < vertical[j].size(); i++) {
      assert (vertical[j][i] != -1);
      if (vertical[j][i] == 0) {
        // 'no edge' represented with .
        std::cout << ".";
      } else {
        assert (vertical[j][i] == 1);
        // 'edge present' represented with |
        std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
}


// ============================================================================
// NAIVE SOLVER METHODS

void Board::zeroEdges() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      // cells labeled with 0 should have all edges set to 0 (no edge)
      if (board[j][i] == 0) {
        horizontal[j][i] = 0;
        horizontal[j+1][i] = 0;
        vertical[j][i] = 0;
        vertical[j][i+1] = 0;
      }
    }
  }
}

void Board::fourEdges() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      // cells labeled with 4 should have all edges set to 1 (edge present)
      if (board[j][i] == 4) {
        horizontal[j][i] = 1;
        horizontal[j+1][i] = 1;
        vertical[j][i] = 1;
        vertical[j][i+1] = 1;
      }
    }
  }
}


// ============================================================================
// NAIVE GENERATOR METHODS

void Board::labelAllCells() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[0].size(); i++) {
      // simply label all cells to match their edge count (not very interesting)
      board[j][i] = countEdges(j,i);
    }
  }
}


// helper function for naive generator method
int Board::countEdges(int j, int i) {
  int answer = 0;
  if (horizontal[j][i]   ==  1) answer++;
  if (horizontal[j+1][i] ==  1) answer++;
  if (vertical[j][i]   ==  1) answer++;
  if (vertical[j][i+1] ==  1) answer++;
  return answer;
}


int Board::single_loop_recursion(int row, int col, int horizontal_value, int vertical_value, Board& b){
	int done = 0;
	int minus = 0;
	// for(int j = 0; j< board.size(); j++){
		// for(int i = 0; i < board[0].size(); i++){
			// if(horizontal[j][i] ==1 && horizontal[j][i] == 1 && vertical[j][i] == 1){
				// return 0;
			// }
			// if(i != 0 && horizontal[j][i] == 1 && horizontal[j][i] == 1 && vertical[j][i] == 1){
				// return 0;
			// }
			// if(horizontal[j][i] == -1 || horizontal[j+1][i] == -1 || vertical[j][i+1] == -1 || vertical[j][i] == -1){
				// done = 1;
			// }
			
		// }
	// }
	// if(done == 0){
		// return 1;
	// }
	

	//Board b(*this);

	
	if(row == board.size() && col == board[0].size()){
		
		//if(board[row-1][col-1] != 0 && board[row-1][col-1] != 4){
			//std::cout << "in " <<std::endl;
			b.horizontal[row][col] = horizontal_value;
			b.vertical[row][col] = vertical_value;
		//}
		//row = 0;
		col = 0;
	}
	
	else if(row == board.size()){
		if(board[row-1][col] != 0 && board[row-1][col] != 4){
			
			b.horizontal[row][col] = horizontal_value;
			b.vertical[row-1][col] = vertical_value;
			
		}
		//row = 0;
	}
	
	else if(col == board[0].size()){
		if(board[row][col-1] != 0 && board[row][col-1] != 4){
			b.horizontal[row][col] = horizontal_value;
			b.vertical[row][col] = vertical_value;
		}
		col = 0;
	}
	
	else{
		if(board[row][col] != 0 && board[row][col] != 4){
			b.horizontal[row][col] = horizontal_value;
			b.vertical[row][col] = vertical_value;
		}
	}
	int j = row;
	int i = col;
	
	// if(i == board[0].size()-1 && j==board.size()- 1){
				// if(vertical[j][i+1]==-1 && horizontal[j+1][i]==-1){
					// return b.single_loop_recursion(j+1,i+1,0,0,b) + b.single_loop_recursion(j+1,i+1,0,1,b) + b.single_loop_recursion(j+1,i+1,1,0,b) + b.single_loop_recursion(j+1,i+1,1,1,b);
				// }
				// else if (vertical[j][i+1]!=-1 && horizontal[j+1][i]==-1){
					// return b.single_loop_recursion(j+1,i+1,0,vertical[j][i+1],b) + b.single_loop_recursion(j+1,i+1,1,vertical[j][i+1],b);
				// }
				// else if (horizontal[j+1][i]!=-1 && vertical[j+1][i]==-1){
					// return b.single_loop_recursion(j+1,i+1,horizontal[j+1][i],0,b) + b.single_loop_recursion(j+1,i+1,horizontal[j+1][i],1,b);
				// }
			// }
			
			if(i == board[0].size()-1){
				//std::cout << i+1 << std::endl;
				if(vertical[j][i+1]==-1){
					return b.single_loop_recursion(j,i+1,horizontal[j][i],0,b) + b.single_loop_recursion(j,i+1,horizontal[j][i],1,b);
				}
				
				else{
					return b.single_loop_recursion(j,i+1,horizontal[j][i],vertical[j][i],b);
				}
			}
			
			
			if(j==board.size() - 1){
				if(horizontal[j+1][i]==-1){
					return b.single_loop_recursion(j+1,i,0,vertical[j][i],b) + b.single_loop_recursion(j+1,i,1,vertical[j][i],b);
				}
				
				else{
					return b.single_loop_recursion(j+1,i,horizontal[j][i],vertical[j][i],b) + b.single_loop_recursion(j+1,i,horizontal[j][i],vertical[j][i],b);
				}
			}
	
	
	
	for (int j = row; j < board.size();j++) {
		for (int i = col; i < board[j].size();i++){			
			if(horizontal[j][i] == -1){
				if(vertical[j][i] == -1){
					return b.single_loop_recursion(j,i,0,0,b) + b.single_loop_recursion(j,i,1,0,b) + b.single_loop_recursion(j,i,0,1,b) + b.single_loop_recursion(j,i,1,1,b);
					
				}
				else{
					return b.single_loop_recursion(j,i,0,vertical[j][i],b) + b.single_loop_recursion(j,i,1,vertical[j][i],b);
				}
			}
			
			else if(horizontal[j][i] != -1){
				if(vertical[j][i] == -1){
					return b.single_loop_recursion(j,i,horizontal[j][i],0,b) + b.single_loop_recursion(j,i,horizontal[j][i],1,b);
					
				}
			}
		}
	}
	return 0;
}
