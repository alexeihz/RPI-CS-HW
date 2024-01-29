#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <cctype>
#include "tetris.h"

//Default constructor
Tetris::Tetris(){
	width = 0;
	data = NULL;
	heights = NULL;
}

//constructor
Tetris::Tetris(int num){
	width=num;
	data = new char *[width];
	heights = new int [width];
	for(int i = 0; i<width; i++){
		data[i]= new char [0];
		heights[i] = 0;
	}
}

int Tetris::get_width() const{
	return width;
}

int Tetris::get_max_height() const{
	int max_height = 0;
	//gets and returns the maximum height of all the columns
	for(int i=0;i<get_width();++i){
		if(heights[i] > max_height){
			max_height = heights[i];
		}
	}
	return max_height;
}

int Tetris::count_squares(){
	int count = 0;
	//counts the number squares taken up by pieces in the tetris board
	for(int i =0; i<width; ++i){
		for(int j = 0; j<heights[i]; ++j){
			if(data[i][j] != ' '){
				++count;
			}
		}
	}
	return count;
}

void Tetris::destroy(){
	//deletes the board
	for(int i=0; i<width; ++i){
		delete[] data[i];
	}
	delete[] data;
	delete[] heights;
	width = 0;
}

void Tetris::remove_left_column(){
	//allocate space for multidimentional array with proper new size and array with heights for the columns
	int new_width = width - 1;
	char **tempdata = new char *[new_width];
	int *tempheights = new int [new_width];
	//fills tempdata array with proper info from data array
	for(int i = 1; i < width; i++){
		tempdata[i-1] = new char[heights[i]];
		for(int j = 0; j < heights[i]; j++){
			tempdata[i-1][j] = data[i][j];
		}
		tempheights[i-1] = heights[i];
	}
	destroy();
	//sets new multidimentional array to data array and array with heights for the columns
	width = new_width;
	data = tempdata;
	heights = tempheights;
}

void Tetris::add_left_column(){
	//allocate space for multidimentional array with proper new size and array with heights for the columns
	int new_width = width + 1;
	char **tempdata = new char *[new_width];
	int *tempheights = new int [new_width];
	//fills tempdata array with proper info from data array
	for(int i = 0; i < width; i++){
		tempdata[i+1] = new char[heights[i]];
		for(int j = 0; j < heights[i]; j++) {
			tempdata[i+1][j] = data[i][j];
		}
		tempheights[i+1] = heights[i];
	}
	tempdata[0] = new char[0];
	tempheights[0] = 0;
	destroy();
	
	//sets new multidimentional array to data array and array with heights for the columns
	width = new_width;
	data = tempdata;
	heights = tempheights;
}

void Tetris::remove_right_column(){
	//allocate space for multidimentional array with proper new size and array with heights for the columns
	int new_width = width - 1;
	char **tempdata = new char *[new_width];
	int *tempheights = new int [new_width];
	//fills tempdata array with proper info from data array
	for(int i = 0; i < new_width; i++){
		tempdata[i] = new char[heights[i]];
		for(int j = 0; j < heights[i]; j++){
			tempdata[i][j] = data[i][j];
		}
		tempheights[i] = heights[i];
	}
	destroy();
	
	//sets new multidimentional array to data array and array with heights for the columns
	width = new_width;
	data = tempdata;
	heights = tempheights;
}

void Tetris::add_right_column(){
	//allocate space for multidimentional array with proper new size and array with heights for the columns
	int new_width = width + 1;
	char **tempdata = new char *[new_width];
	int *tempheights = new int [new_width];
	//fills tempdata array with proper info from data array
	for(int i = 0; i < width; i++){
		tempdata[i] = new char[heights[i]];
		for(int j = 0; j < heights[i]; j++) {
			tempdata[i][j] = data[i][j];
		}
		tempheights[i] = heights[i];
	}
	tempdata[new_width-1] = new char[0];
	tempheights[new_width-1] = 0;
	destroy();
	
	//sets new multidimentional array to data array and array with heights for the columns
	width = new_width;
	data = tempdata;
	heights = tempheights;
}

int Tetris::remove_full_rows(){
	int remove_count = 0;
	int full_row = 0;
	for(int i=0; i<heights[i]; ++i){
		//checks if a row is completely filled
		for(int j = 0; j<width && i<heights[j] ; ++j){
			if(data[j][i] != ' '){
				full_row++;
			}
		}
		
		if(full_row==width){
			remove_count++;
			//allocates an array with one less row space in it and fills it with spaces
			char **tempdata = new char *[width];
			for(int k = 0; k<width; k++){
				tempdata[k]= new char [heights[k]-1];
			}
			for(int l = 0; l < width; l++){
				for(int k = 0; k<heights[l]-1; k++){
					tempdata[l][k]= ' ';
				}
			}
			
			//fills tempdata with info from data but without the cleared row
			for(int l=0; l<width; ++l){
				for(int k = 0; k<i; ++k){
					tempdata[l][k] = data[l][k];
				}
			}
			for(int l = 0; l < width; ++l){
				for(int k = i; k<heights[l]-1; ++k){
					tempdata[l][k] = data[l][k+1];
				}
			}
			
			//deletes and reassigns data to tempdata values
			for(int k=0; k<width; ++k){
				delete[] data[k];
			}
			delete[] data;
			
			data = new char *[width];
			for(int k = 0; k<width; k++){
				data[k]= new char [heights[k]-1];
			}
			
			for(int l = 0; l < width; ++l){
				for(int k = 0; k<heights[l]-1; ++k){
					data[l][k] = tempdata[l][k];
				}
			}
			//adjusts heights in each column to be the corret size
			for(int k = 0; k<width; ++k){
				heights[k] -= 1;
			}
			
			for(int k = 0; k < width; k++){
				int temp = 0;
				for(int l = 0; l < heights[k]; l++){
					if(data[k][l] != ' '){
						temp = l;
					}
					if(l == heights[k]-1 && l != temp){
						heights[k] = heights[k] - (l - temp + 1);
					}
				}
			}
			//deletes tempdata
			for(int k=0; k<width; ++k){
				delete[] tempdata[k];
			}
			delete[] tempdata;
			i--;
		}
		
		full_row = 0;
	}
	return remove_count;
}

void Tetris::add_piece(char type, int rotate, int horizontal){
	if(type=='O'){
		add_shape(2, 2, 'O', horizontal);
	}	
	
	if(type=='I'){
		if(rotate == 0 || rotate == 180){
			add_shape(1, 4, 'I', horizontal);
		}
		
		if(rotate == 90 || rotate == 270){
			add_shape(4, 1, 'I', horizontal);
		}
	}
	if(type == 'T'){
		
	}
	if(type == 'Z'){
		
	}
	if(type == 'J'){
		
	}
	if(type == 'L'){
		
	}
	if(type == 'S'){
		
	}
}


void Tetris::add_shape(int width, int height, char c, int horizontal) {
	
	int high_height = 0;
	//defines maximum height
	for (int i = horizontal; i < horizontal + width; ++i) {
		if (high_height < heights[i]) {
			high_height = heights[i];
		}
	}
	
	high_height += height;
	for (int i = horizontal; i < horizontal + width; ++i) {
		//allocates space for new array
		char* temparray = new char [high_height];
		for (int j = 0; j < high_height; ++j) {
			temparray[j] = ' ';
		}
		for (int j = 0; j < heights[i]; ++j) {
			temparray[j] = data[i][j];
		}
		
		for (int j = high_height - height; j < high_height; ++j) {
			temparray[j] = 'O';
		}
		
		delete [] data[i];
		
		//sets new arrays to data and heights array
		data[i] = temparray;
		heights[i] = high_height;
	}
}