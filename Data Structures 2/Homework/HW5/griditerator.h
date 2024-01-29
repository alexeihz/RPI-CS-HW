//griditerator.h

#ifndef GRIDITERATOR_H
#define GRIDITERATOR_H

#include "grid.h"
#include "node.h"
#include <cassert>

//template <class T>


template <class T>
class GridIterator {
	public:
		GridIterator<T>(Node<T>* pointer);
		GridIterator<T>();
		
		T& operator * ();
		GridIterator<T> operator ++ (int);
		bool operator==(const GridIterator<T>& r) const;
		bool operator!=(const GridIterator<T>& r) const;

		GridIterator<T>& left();
		GridIterator<T>& right();
		GridIterator<T>& up();
		GridIterator<T>& down();
		
		template <class> friend class Grid;		
	private:
		Node<T>* ptr;
		int spiral_count;
		int spiral_width;
		int spiral_height;
		int height_count;
		int width_count;
		int size_count1;
		int size_count2;
		bool lefty;
		bool downy;
		bool spiral_first;
		bool snek;
};


//Constructor
template <class T>
GridIterator<T>::GridIterator(Node<T>* pointer){
	ptr = pointer;
	lefty = false;
	snek = false;
	downy = false;
	spiral_first = false;
	spiral_count = 0;
	spiral_width = 0;
	spiral_height = 0;
	height_count = 0;
	width_count = 0;
	size_count1 = 0;
	size_count2 = 0;
}

//default constructor
template <class T>
GridIterator<T>::GridIterator(){
	ptr = NULL;
}

//sets the ptr to the left of the iterator to the ptr and returns the iterator
template <class T>
GridIterator<T>& GridIterator<T>::left(){
	ptr = ptr -> left;
	return *this;
}

//sets the ptr to the right of the iterator to the ptr and returns the iterator
template <class T>
GridIterator<T>& GridIterator<T>::right(){
	ptr = ptr -> right;
	return *this;
}

//sets the ptr above the iterator to the ptr and returns the iterator
template <class T>
GridIterator<T>& GridIterator<T>::up(){
	ptr = ptr -> up;
	return *this;
}

//sets the ptr below the iterator to the ptr and returns the iterator
template <class T>
GridIterator<T>& GridIterator<T>::down(){
	ptr = ptr -> down;
	return *this;
}

//dereference operator overloader
template <class T>
T& GridIterator<T>::operator*(){
	return ptr -> value;
}

//operator++(int) overloader
template <class T>
GridIterator<T> GridIterator<T>::operator++(int){
	GridIterator<T> temp(*this);
	//snakes through the grid
	if(snek == true){
		if(ptr -> right == NULL && lefty == false){
			ptr = ptr -> down;
			//lefty tells me if im moving to the left (true) or right (false) in the grid
			lefty = true;
		}
		else if(ptr -> left == NULL && lefty == true){
			ptr = ptr -> down;
			lefty = false;
		}
		else if(lefty == true){
			ptr = ptr -> left;
		}
		else if(lefty == false){
			ptr = ptr -> right;
		}
	}
	//spirals through the grid
	else if(snek == false){
		//checks to see if th first spiral has been done and if not runs until it has
		if(spiral_first==false){
			if(ptr->right==NULL && lefty == false && downy == false){
				ptr = ptr -> down;
				//size_count2 counts the height of the grid
				size_count2++;
				//size_count1 counts the width of the grid
				size_count1++;
				//downy tells me if im moving to the down (true) or up (false) in the grid
				downy = true;
			}
			
			else if(ptr->down==NULL && lefty == false && downy == true){
				ptr = ptr -> left;
				size_count1++;
				size_count2++;
				lefty = true;
			}
			
			else if(ptr-> left == NULL && lefty == true && downy == true){
				ptr = ptr -> up;
				downy = false;
				spiral_first=true;
			}
			
			else if(lefty == true && downy == true){
				ptr = ptr -> left;
				//also keeps track of the grid's width
				spiral_width++;
				size_count1++;
			}
			
			else if(lefty == false && downy == false){
				ptr = ptr -> right;
			}
			
			else if (lefty == false && downy == true){
				ptr = ptr -> down;
				//also keeps track of the grid's height
				spiral_height++;
				size_count2++;
				
			}	
			//spiral_count counts the number of slots in the grid
			spiral_count++;			
			
		}
		else{
			//the grid's sizes
			int size = size_count1 * size_count2;
			//prevents the spiral from wrapping over itself
			if(width_count == spiral_width -1 && lefty == false && downy == false && spiral_count < size){
				ptr = ptr -> down;
				downy = true;
				width_count = 0;
				spiral_width = spiral_width - 1;
			}
			
			else if(height_count == spiral_height -1 && lefty == false && downy == true && spiral_count < size){
				ptr = ptr -> left;
				lefty = true;
				height_count=0;
				spiral_height = spiral_height -1;
			}
			
			else if(width_count == spiral_width -1 && lefty == true && downy == true && spiral_count < size){
				ptr = ptr -> up;
				downy = false;
				width_count = 0;
				spiral_width = spiral_width - 1;
			}
			
			else if(height_count == spiral_height -1 && lefty == true && downy == false && spiral_count < size){
				ptr = ptr -> right;
				lefty = false;
				height_count=0;
				spiral_height = spiral_height -1;
			}
			
			
			//increments through the grid in a spiral shape
			else if(lefty == true && downy == true && spiral_count < size){
				ptr = ptr -> left;
				width_count++;
			}
			
			else if(lefty == true && downy == false && spiral_count < size){
				ptr = ptr -> up;
				height_count++;
			}
			
			else if(lefty == false && downy == false && spiral_count < size){
				ptr = ptr -> right;
				width_count++;
			}
			
			else if (lefty == false && downy == true && spiral_count < size){
				ptr = ptr -> down;
				height_count++;
			}
			spiral_count++;
			if(spiral_count >= size){
				ptr = NULL;
			}
			
		}
	}
    return temp;
}
//operator== overloader
template <class T>
bool GridIterator<T>::operator==(const GridIterator<T>& r) const {
    return ptr == r.ptr; 
}

//operator!= overloader
template <class T>
bool GridIterator<T>::operator!=(const GridIterator<T>& r) const {
    return ptr != r.ptr; 
}

#endif