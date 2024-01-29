#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {

  int size;
  while (cin >> size) {
    // Read in the board size and create an empty board
    Sudoku board(size);

    // Read in and set the known positions in the board
    char c;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {      
        cin >> c;
        if (c != '.') {
          board.Set(i,j,c-'0');
        }
      }
    }
    
    // The iterative solving routine 
    while (1) {
      
      // Is the puzzle is already solved?
      if (board.IsSolved()) {
        cout << "\nPuzzle is solved:" << endl;
        board.Print();
        break;
      }
      
      // Is the puzzle impossible?
      if (board.Impossible()) {
        cout << "\nCannot solve this puzzle:" << endl;
        board.Print();
        break;
      }
      
      // Try to reduce the number of choices in one or more board cells
      // by propagating known values within each row, column, and quadrant
      int changed = 0;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (board.KnownValue(i,j))
            changed += board.Propagate(i,j);
        }
      }
      
      // If nothing changed this iteration, give up
      if (changed == 0) {
        cout << "\nPuzzle is too difficult for this solver!" << endl;
        board.Print();
        break;      
      }
    }
  }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
  // set the size
  size = s;
  quadrant_size = (int)sqrt(size);
  assert (quadrant_size*quadrant_size == s);

  
  // You need to finish this function!
  set<int> possible_numbers;
  for(unsigned int i = 1; i <= size; i++){
    possible_numbers.insert(i);
  }

  vector<set<int> > row;
  for(unsigned int i = 1; i <= size; i++){
    row.push_back(possible_numbers);
  }

  for(unsigned int i = 1; i <= size; i++){
    board.push_back(row); 
  }
}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
  // make sure the value is one of the legal values
  assert (board[i][j].find(value) != board[i][j].end());
  board[i][j].clear();
  board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
  return (board[i][j].size() == 1);
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {


  // You need to write this function
  for(unsigned int row = 0; row < board.size(); row++){
    for(unsigned int col = 0; col < board[row].size(); col++){
      if(board[row][col].size() != 1){
        return false;
      }
    }
  }
  return true;
}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j].size() == 0) 
        return true;
    }
  }
  return false;
}

// print out the solution
void Sudoku::Print() const {
  int solved = IsSolved();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int count = size+1;
      for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
        count--;
        cout << *itr;
      }
      if (!solved) {
        // if it's not solved, print out spaces to separate the values
        for (int k = 0; k < count; k++) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {
  int counter = 0;
  //std::cout << "propagating from: " << i << "," << j << "\n";

  if(board[i][j].size() == 1){
    //std::cout << "SKDHFJSHDFJSHDF\n";
    //Remove it from the others in the row
    for(unsigned int col = 0; col < board[i].size(); col++){
      //std::cout << "Checking row " << i << " col " << col << " " << board[i].size() << "\n";
      if(col == j)
        continue;
      if(board[i][col].erase(*(board[i][j].begin())))
        counter++;
    }
    //std::cout << "Finished row\n";
    //Remove it from the others in the column
    for(unsigned int row = 0; row < board.size(); row++){
      //std::cout << "Checking col...\n";
      if(row == i)
        continue;
      if(board[row][j].erase(*(board[i][j].begin())))
        counter++;
    }
    //std::cout << "Finished col\n";
    //Remove it from the others in the quadrant
    if(quadrant_size > 1){
        int rows = quadrant_size;
        int cols = quadrant_size;
        //Get the upper left corner of the board
        int upper_left_row;
        int upper_left_col;

        upper_left_row = i - i % quadrant_size;
        upper_left_col = j - j % quadrant_size;
        //Go from the upper left corner over the entire board
        for(unsigned int row = 0; row < rows; row++){
          for(unsigned int col = 0; col < cols; col++){
            //std::cout << "Checking square " << upper_left_row + row << "," <<upper_left_col + col << "\n";
            if(upper_left_row + row == i && upper_left_col + col == j)
              continue;

            if(board[upper_left_row + row][upper_left_col + col].erase(*(board[i][j].begin())))
              counter++;
          }
        }
    }

    //std::cout << "Finished quadrant\n";
  }
  //std::cout << "Removed: " << counter << "\n";
  return counter;
}