//grid.h

#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <cmath>
#include <list>
#include <iomanip>

#include "node.h"
#include "griditerator.h"


template <class T>
class Grid {
	public:
		typedef GridIterator<T> iterator;
		
		Grid<T>(int w, int h, T val = T());
		Grid<T>();
		Grid<T>(const Grid<T>& grid);
		~Grid<T>();
		
		
		void set(int col, int row, T val);
		
		void join(Grid<T>& grid);
		void stack(Grid<T>& grid);
		
		void lift(iterator itr, Grid<T>& grid);
		void chop(iterator itr, Grid<T>& grid);
		
		
		T get(int col, int row) const;
		int getWidth() const;
		int getHeight() const;
		int getSize() const;
		
		
		iterator begin_upper_left() const;
		iterator begin_upper_right() const;
		iterator begin_lower_left() const;
		iterator begin_lower_right() const;
		
		
		void reset(T val);
		
		
		void print() const;
		
		void clear();
		
		iterator end_snake() const;
		iterator begin_snake() const;
		
		iterator begin_spiral() const;
		iterator end_spiral() const;
		
		iterator end() const;
		
		
	private:
		// variables
		int width, height;
		Node<T>* upper_left;
		Node<T>* upper_right;
		Node<T>* lower_left;
		Node<T>* lower_right;
	
	
};


// CPP
template <class T>
Grid<T>::Grid(const Grid<T>& grid){
	grid.width = width;
	grid.height = height;
}

//creates a row
template <class T>
Node<T>* create_row(int width, T val) {
	//Sets the beginning of the row to val
	Node<T>* head = new Node<T>;
	head -> value = val;
	Node<T>* prev = head;
	//links the nodes together in a row
	for(int i = 1; i<width; i++){
		Node<T>* current = new Node<T>;
		current -> value = val;
		current -> left = prev;
		prev -> right = current;
		prev = current;
	}
	return head;
}

//stacks rows on top of one another and links them together
template <class T>
void stack_rows(Node<T>* row1, Node<T>* row2) {
	while(row1 != NULL){
		row1 -> down = row2;
		row2 -> up = row1;
		row1 = row1 -> right;
		row2 = row2 -> right;
	}
}

//finds the upper right node of a grid
template <class T>
Node<T>* find_upper_right(Node<T>* start) {
	if(start == NULL){
		return start;
	}
	Node<T>* top_right = start;
	while(start -> right != NULL){
		start = start -> right;
	}
	while(start -> up != NULL){
		start = start -> up;
	}
	top_right = start;
	return top_right;
}

//finds the upper left node of a grid
template <class T>
Node<T>* find_upper_left(Node<T>* start) {
	if(start == NULL){
		return start;
	}
	Node<T>* top_left = start;
	while(start -> left != NULL){
		start = start -> left;
	}
	while(start -> up != NULL){
		start = start -> up;
	}
	top_left = start;
	return top_left;
}

//finds the lower right node of a grid
template <class T>
Node<T>* find_lower_right(Node<T>* start) {
	if(start == NULL){
		return start;
	}
	Node<T>* bottom_right = start;
	while(start -> right != NULL){
		start = start -> right;
	}
	while(start -> down != NULL){
		start = start -> down;
	}
	bottom_right = start;
	return bottom_right;
}

//finds the lower left node of a grid
template <class T>
Node<T>* find_lower_left(Node<T>* start) {
	if(start == NULL){
		return start;
	}
	Node<T>* bottom_left = start;
	while(start -> left != NULL){
		start = start -> left;
	}
	while(start -> down != NULL){
		start = start -> down;
	}
	bottom_left = start;
	return bottom_left;
}

//constructor
template <class T>
Grid<T>::Grid(int w, int h, T val){
	width=w;
	height=h;
	Node<T>* row1 = create_row<T>(w, val);
	
	for(int i = 0; i < h-1; i++){
		Node<T>* row2 = create_row<T>(w, val);
		stack_rows<T>(row1,row2);
		row1=row2;
	}
	upper_left  = find_upper_left<T>(row1);
	upper_right = find_upper_right<T>(row1);
	lower_right = find_lower_right<T>(row1);
	lower_left  = find_lower_left<T>(row1);
}

//default constructor
template <class T>
Grid<T>::Grid(){
	width = 0;
	height = 0;
}

//destructor
template <class T>
Grid<T>::~Grid(){
	clear();
}

//sets a value at a point in the grid
template <class T>
void Grid<T>::set(int col, int row, T val){
	Node<T>* node = upper_left;
	for (int i = 0; i < col; i++){
		node = node -> right;
	}
	for (int j = 0; j < row; j++){
		node = node -> down;
	}
	node->value = val;
}

//joins a grid to the right of another grid
template <class T>
void Grid<T>::join(Grid<T>& grid){
	Node<T>* connect1 = upper_right;
	Node<T>* connect2 = grid.upper_left;
	for(int i = 0; i< height; i++){
		connect1 -> right = connect2;
		connect2 -> left = connect1;
		connect1 = connect1 -> down;
		connect2 = connect2 -> down;
	}
	upper_right = grid.upper_right;
	lower_right = grid.lower_right;
	width += grid.getWidth();
	
	grid.upper_left = grid.upper_right = grid.lower_left = grid.lower_right = NULL;
	grid.width = grid.height = 0;	
}

//adds a grid on the top of another grid
template <class T>
void Grid<T>::stack(Grid<T>& grid){
	stack_rows<T>(grid.lower_left,upper_left);
	upper_left = grid.upper_left;
	upper_right = grid.upper_right;
	height += grid.getHeight();
	
	grid.upper_left = grid.upper_right = grid.lower_left = grid.lower_right = NULL;
	grid.width = grid.height = 0;
}

//lifts off the section of the grid above the iterator
template <class T>
void Grid<T>::lift(iterator itr, Grid<T>& grid){
	Node<T>* top = itr.ptr;
	while (top->left != NULL)
		top = top->left;
	Node<T>* bottom = top->up;
	
	Node<T>* current_top = top;
	Node<T>* other_bottom = bottom;
	while (current_top != NULL){
		other_bottom->down = NULL;
		current_top->up = NULL;
		other_bottom = other_bottom->right;
		current_top = current_top->right;
	}
	grid.upper_left = find_upper_left<T>(bottom);
	grid.upper_right = find_upper_right<T>(bottom);
	grid.lower_left = find_lower_left<T>(bottom);
	grid.lower_right = find_lower_right<T>(bottom);
	
	upper_left = find_upper_left(top);
	upper_right = find_upper_right(top);
	
	int i = 0;
	while(top != NULL){
		top = top->down;
		i++;
	}
	
	grid.width = width;
	grid.height = height - i;
	height = i;
	
}

//chops off all the right side of the grid after the iterator
template <class T>
void Grid<T>::chop(iterator itr, Grid<T>& grid){
	Node<T>* left_side = itr.ptr;
	while (left_side->up != NULL)
		left_side = left_side->up;
	
	left_side = left_side -> left;
	Node<T>* right_side = left_side ->right;
	
	Node<T>* current_left = left_side;
	Node<T>* other_right = right_side;
	while (current_left != NULL){
		other_right->left = NULL;
		current_left->right = NULL;
		other_right = other_right->down;
		current_left = current_left->down;
	}
	
	grid.upper_left = find_upper_left<T>(right_side);
	grid.upper_right = find_upper_right<T>(right_side);
	grid.lower_left = find_lower_left<T>(right_side);
	grid.lower_right = find_lower_right<T>(right_side);
	
	upper_left = find_upper_left(left_side);
	upper_right = find_upper_right(left_side);
	
	int i = 0;
	while(left_side != NULL){
		left_side = left_side->left;
		i++;
	}
	
	grid.width = width-i;
	grid.height = height;
	width = i;
}

//gets the value at a point in the grid
template <class T>
T Grid<T>::get(int col, int row) const{
	Node<T>* node = upper_left;
	for (int i = 0; i < col; i++){
		node = node -> right;
	}
	for (int j = 0; j < row; j++){
		node = node -> down;
	}
	return node->value;
	
}

//returns the width of the grid
template <class T>
int Grid<T>::getWidth() const{
	return width;
}

//returns the height of the grid
template <class T>
int Grid<T>::getHeight() const{
	return height;
}
//returns the size of the grid
template <class T>
int Grid<T>::getSize() const{
	return width * height;
}

//returns the iterator to the upper left of the grid 
template <class T>
typename Grid<T>::iterator Grid<T>::begin_upper_left() const{
	iterator itr(upper_left);
	return itr;
}

//returns the iterator to the upper right of the grid 
template <class T>
typename Grid<T>::iterator Grid<T>::begin_upper_right() const{
	iterator itr(upper_right);
	return itr;
}

//returns the iterator to the lower left of the grid 
template <class T>
typename Grid<T>::iterator Grid<T>::begin_lower_left() const{
	iterator itr(lower_left);
	return itr;
}

//returns the iterator to the lower right of the grid 
template <class T>
typename Grid<T>::iterator Grid<T>::begin_lower_right() const{
	iterator itr(lower_right);
	return itr;
}

//returns the beginning of the snake iterator
template <class T>
typename Grid<T>::iterator Grid<T>::begin_snake() const{
	iterator itr(upper_left);
	itr.snek = true;
	return itr;
}

//returns the end of the snake iterator
template <class T>
typename Grid<T>::iterator Grid<T>::end_snake() const{
	return NULL;
}
//returns the beginning of the spiral iterator
template <class T>
typename Grid<T>::iterator Grid<T>::begin_spiral() const{
	iterator itr(upper_left);
	itr.snek = false;
	return itr;
}
//returns the end of the spiral iterator
template <class T>
typename Grid<T>::iterator Grid<T>::end_spiral() const{
	return NULL;
}

template <class T>
typename Grid<T>::iterator Grid<T>::end() const{
	return NULL;
}

//resets all the values to a certain value
template <class T>
void Grid<T>::reset(T val){
	for(int i = 0; i < height; i++){
		for(int j =0; j< width; j++){
			set(j,i,val);
		}
	}
}

//prints the grid
template <class T>
void Grid<T>::print() const{
	Node<T>* node = upper_left;
	Node<T>* node2 = upper_left;
	for(int i =0; i<height; i++){
		for(int j = 0; j< width; j++){
			if(j == width -1){
				std::cout << std::setw(4) << node->value << std::endl;
			}
			else{
				std::cout << std::setw(4) << node->value;
				node = node -> right;
			}
		}
		node = node2 -> down;
		node2 = node;
	}
}

//clears and deletes the Nodes from the grid
template <class T>
void Grid<T>::clear(){
	if (upper_left == NULL)
		return;
	Node<T>* node = upper_left;
	Node<T>* node2 = upper_left -> down;
	for(int i =0; i<height; i++){
		for(int j = 0; j< width; j++){
			Node<T>* tmp = node -> right;
			delete node;
			node = tmp;
		}
		delete node;
		node = node2;
		if (i < height-1){
			node2 = node -> down;
		}
	}
	width = 0;
	height = 0;
	upper_left = upper_right = lower_left = lower_right = NULL;
}

#endif
