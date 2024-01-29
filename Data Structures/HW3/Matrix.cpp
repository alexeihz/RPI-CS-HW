#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

//Default constructor
Matrix::Matrix(){
  rows = 0;
  columns = 0;
  array = NULL;
}

//De-constructor
Matrix::~Matrix(){
	clear();
}

//constructor
Matrix::Matrix(unsigned int rowsCount, unsigned int colsCount, double fill){
	if(rowsCount==0 || colsCount==0){
		rows = 0;
		columns = 0;
		array = NULL;
	}
	else{
		rows = rowsCount;
		columns = colsCount;
		array = new double *[rows];
		for(unsigned int i = 0; i<rows;++i){
			array[i] = new double [columns];
			for(unsigned int j = 0; j<columns; ++j){
				array[i][j] = fill;
			}
		}
	}
}

//copy constructor
Matrix::Matrix(const Matrix& neo){
	if(neo.num_rows()==0 || neo.num_cols()==0){
		rows = 0;
		columns = 0;
		array = NULL;
	}
	else{
		rows = neo.num_rows();
		columns = neo.num_cols();
		array = new double *[rows];
		for(unsigned int i = 0; i<rows;++i){
			array[i] = new double [columns];
			for(unsigned int j = 0; j<columns; ++j){
				array[i][j] = neo.array[i][j];
			}
		}
	}
}

//overloads == operator
bool Matrix::operator==(const Matrix& neo){
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<columns; ++j){
			if(array[i][j]!=neo.array[i][j]){
				return false;
			}
		}
	}
	return true;
}

//overloads != operator
bool Matrix::operator!=(const Matrix& neo){
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<columns; ++j){
			if(array[i][j]==neo.array[i][j]){
				return false;
			}
		}
	}
	return true;
}

//returns number of rows
int Matrix::num_rows() const{
	return rows;
}

//returns number of columns
int Matrix::num_cols() const{
	return columns;
}


//clears matrix
void Matrix::clear(){
	for(unsigned int i=0; i<rows; ++i){
		delete[] array[i];
	}
	delete[] array;
	rows=0;
	columns=0;
}

//returns true and sets num to the value at the row and column. if otherwise it returns false
bool Matrix::get(unsigned int row_check, unsigned int column_check, double& num) const{
	if(row_check<rows && column_check<columns){
		num = array[row_check][column_check];
		return true;
	}
	return false;
}

//returns true and sets the value at the row and column to num. if otherwise ir returns false
bool Matrix::set(unsigned int row_check, unsigned int column_check, double num){
	if(row_check<rows && column_check<columns){
		array[row_check][column_check] = num;
		return true;
	}
	return false;
}

//multiplies all the numbers in the matrix by a coefficient
void Matrix::multiply_by_coefficient(const double num){
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<columns; ++j){
			array[i][j] *= num;
		}
	}
}

//returns true if both source_row and target_row are in the matrix and swaps them. if otherwise returns false
bool Matrix::swap_row(unsigned int source_row, unsigned int target_row){
	if(source_row<rows && target_row<rows){
		double temp1[columns];
		double temp2[columns];
		for(unsigned int i=0; i<rows; ++i){
			if(i==source_row){
				for(unsigned int j=0;j<columns; ++j){
					temp1[j] = array[i][j];
				}
			}
			if(i==target_row){
				for(unsigned int j=0;j<columns; ++j){
					temp2[j] = array[i][j];
				}
			}
		}
		
		for(unsigned int i=0; i<rows; ++i){
			if(i==source_row){
				for(unsigned int j=0;j<columns; ++j){
					array[i][j] = temp2[j];
				}
			}
			if(i==target_row){
				for(unsigned int j=0;j<columns; ++j){
					array[i][j] = temp1[j];
				}
			}
		}
		return true;
	}
	return false;
}

//flips the rows and columns
void Matrix::transpose(){
	double temp[rows*columns + 2];
	Matrix flip(columns,rows,121);
	int count = 0;
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<columns; ++j){
			temp[count] = array[i][j];
			++count;
		}
	}
	count=0;
	for(unsigned int i=0; i<columns; ++i){
		for(unsigned int j=0; j<rows; ++j){
			flip.array[i][j] = temp[count];
			++count;
		}
	}
	clear();
	*this = flip;
	
}

//adds the elements of 2 matrices together and returns true if the matrices are equal in size. returns false otherwise
bool Matrix::add(const Matrix& b){
	if (rows == b.num_rows() && columns == b.num_cols()){
		for(unsigned int i=0; i<rows; ++i){
			for(unsigned int j=0; j<columns; ++j){
				array[i][j] += b.array[i][j];
			}
		}
		return true;
	}
	return false;
}

//subtracts the elements of one matrix from another and returns true if the matrices are equal in size. returns false otherwise
bool Matrix::subtract(const Matrix& b){
	if (rows == b.num_rows() && columns == b.num_cols()){
		for(unsigned int i=0; i<rows; ++i){
			for(unsigned int j=0; j<columns; ++j){
				array[i][j] -= b.array[i][j];
			}
		}
		return true;
	}
	return false;
}

//returns a row from the matrix
double* Matrix::get_row(unsigned int num){
	if(num<rows){
		double * p = new double[rows];
		int count = 0;
		for(unsigned int i = 0; i<rows; ++i){
			for (unsigned int j=0; j<columns; ++j){
				if(i==num){
					p[count] = array[i][j];
					count++;
				}
			}
		}
		return p;
	}
	else{
		double * p = NULL;
		return p;
	}
}

//returns a column from the matrix
double* Matrix::get_col(unsigned int num){
	if(num<rows){
		double * p = new double[columns];
		int count = 0;
		for(unsigned int i = 0; i<rows; ++i){
			for (unsigned int j=0; j<columns; ++j){
				if(j==num){
					p[count] = array[i][j];
					count++;
				}
			}
		}
		return p;
	}
	else{
		double * p = NULL;
		return p;
	}
}

//returns a matrix array of the 4 corners of the original matrix
Matrix* Matrix::quarter(){
	Matrix* corners = new Matrix[4];
	unsigned int numOfCols = (columns+1)/2;
	unsigned int numOfRows = (rows+1)/2;
	
	Matrix upperLeft(numOfRows,numOfCols,999);
	Matrix lowerLeft(upperLeft);
	Matrix lowerRight(lowerLeft);
	Matrix upperRight(lowerRight);
	
	for(unsigned int i = 0; i<numOfRows; ++i){
		for(unsigned int j = 0; j<numOfCols; ++j){
			upperLeft.set(i,j,array[i][j]);
		}
	}		
	
	for(unsigned int i = 0; i<numOfRows; ++i){
		for(unsigned int j = 0; j<numOfCols; ++j){
			int temp1 = j + numOfCols;
			upperRight.set(i,j,array[i][temp1]);
		}
	}	
	for(unsigned int i = 0; i<numOfRows; ++i){
		for(unsigned int j = 0; j<numOfCols; ++j){
			int temp1 = i + numOfRows-1;
			lowerLeft.set(i,j,array[temp1][j]);
		}
	}		
	for(unsigned int i = 0; i<numOfRows; ++i){
		for(unsigned int j = 0; j<numOfCols; ++j){
			int temp1 = i + numOfRows-1;
			int temp2 = j + numOfCols;
			lowerRight.set(i,j,array[temp1][temp2]);
		}
	}		
	corners[0] = upperLeft;
	corners[1] = upperRight;
	corners[2] = lowerLeft;
	corners[3] = lowerRight;
	
	return corners;
	
}

//overloads the = operator
Matrix Matrix::operator=(const Matrix& neo){
	if(neo.num_rows()==0 || neo.num_cols()==0){
		rows = 0;
		columns = 0;
		array = NULL;
	}
	else{
		rows = neo.num_rows();
		columns = neo.num_cols();
		array = new double *[rows];
		for(unsigned int i = 0; i<rows;++i){
			array[i] = new double [columns];
			for(unsigned int j = 0; j<columns; ++j){
				array[i][j] = neo.array[i][j];
			}
		}
	}
	return neo;	
}
	
//overloads the << operator
std::ostream& operator<< (std::ostream& out, const Matrix& m){
	out << m.num_rows();
	out << " x ";
	out << m.num_cols();
	out << ":" << std::endl;
	out<<"[";
	for(unsigned int i=0; i<m.num_rows(); ++i){
		for(unsigned int j=0; j<m.num_cols(); ++j){
			if(j==0 && i==0){
				out<<" ";
			}
			else if (j==0){
				out<<"  ";
			}
			else{
				out<<" ";
			}
			double num;
			m.get(i,j,num);
			out << num;
			//out << " ";
		}
		if(i<m.num_rows()-1){
			out<<std::endl;
		}
		
	}
	out<<" ]"<<std::endl;
	return out;
}

//resizes the matrix and fills any open spaces with a fill number
void Matrix::resize(unsigned int numRows, unsigned int numCols, double fill){
	Matrix flip(numRows,numCols,fill);
	for(unsigned int i=0; i<numRows; ++i){
		for(unsigned int j=0; j<numCols; ++j){
			if(i>=rows || j>=columns){
				flip.array[i][j] = fill;
			}
			else{
				flip.array[i][j] = array[i][j];
			}
		}
	}
	clear();
	*this = flip;
}