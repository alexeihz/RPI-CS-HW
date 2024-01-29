#include <vector>

template <class T> 
class Table {

public:   
	//constructor
	Table<T>(unsigned int rows, unsigned int cols,const T& val);
	//copy constructor
	Table<T>(const Table& t);
	//overloaded operator=
	Table<T>& operator=(const Table& t);
	//destructor
	~Table<T>();
	void clear();
	
	//accessors
	T get(unsigned row, unsigned col) const;
	unsigned numRows() const;
	unsigned numColumns() const;
	
	//modifiers
	void push_back_row(std::vector<T>& new_row);
	void pop_back_column();
	void push_back_column(std::vector<T>& new_col);
	void pop_back_row();
	void set(unsigned int row, unsigned int col, T val);
	
	void push_back_columns(Table& new_t);
	void push_back_rows(Table& new_t);
	
	void print();
private:
	//private methods	
	void create(unsigned rows, unsigned cols, const T& val);
	void copy(const Table& t); 
	
	//private variables
	unsigned int rows_;
	unsigned int cols_;
	T** values;
};

//creates a table
template <class T>
void Table<T>::create(unsigned rows, unsigned cols, const T& val){
	rows_ = rows;
	cols_ = cols;
	values = new T *[rows];
	for(unsigned i = 0; i<rows; i++){
		values[i] = new T [cols];
		for(unsigned j = 0; j< cols; j++){
			values[i][j] = val;
		}
	}
}

//copies a table
template <class T>
void Table<T>::copy(const Table &t){
	//if statement handles copying of an empty table
	if(t.values == NULL){
		this -> rows_ = 0;
		this -> cols_ = 0;
		this -> values = NULL;		
	}
	else{
		this -> rows_ = t.rows_;
		this -> cols_ = t.cols_;
		this -> values = new T *[rows_];
		for(unsigned i = 0; i<rows_; i++){
			this -> values[i] = new T [cols_];
			for(unsigned j = 0; j< cols_; j++){
				this -> values[i][j] = t.values[i][j];
			}
		}
	}
}

//constructor
template <class T> 
Table<T>::Table(unsigned rows, unsigned cols, const T& val){
	create(rows, cols, val);
}

//copy constructor
template <class T>
Table<T>::Table(const Table &t){
	copy(t);
}

//overloaded operator=
template <class T>
Table<T>& Table<T>::operator=(const Table<T>& t){
	clear();
	this->copy(t);
	return *this;
}

//destructor
template <class T>
Table<T>::~Table(){
	clear();
}

//gets individual entries in the table
//if the value is out of bounds of the table, prints error and exits
template <class T>
T Table<T>::get(unsigned row, unsigned col) const{
	if(row >= rows_ || col >= cols_){
		std::cerr << "Value is out of bounds of the table" << std::endl;
		exit(1);
	}
	return values[row][col];
}

//returns the number of rows in the table
template <class T>
unsigned Table<T>::numRows() const{
	return rows_;
}

//returns the number of columns in the table
template <class T>
unsigned Table<T>::numColumns() const{
	return cols_;
}

//sets individual entries in the table
//if the value is out of bounds of the table, prints error and exits
template <class T>
void Table<T>::set(unsigned row, unsigned col, T val){
	if(row >= rows_ || col >= cols_){
		std::cerr << "Value out of bounds of the table" << std::endl;
		exit(1);
	}
	values[row][col] = val;
}

//prints the table
template <class T>
void Table<T>::print(){
	std::cout << "table: " << rows_ << " rows, " << cols_ << " cols" << std::endl;
	for(unsigned i = 0; i < rows_; i++){
		for(unsigned j = 0; j < cols_; j++){
			if(j == cols_ -1){
				std::cout << values[i][j];	
			}
			else{
				std::cout << values[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//deletes everything in the table and frees memory
template <class T>
void Table<T>::clear(){
	if(values != NULL){
		for(unsigned int i=0; i<rows_; ++i){
			delete[] values[i];
		}
		delete[] values;
		rows_=0;
		cols_=0;
		values = NULL;
	}
}

//adds a row to the table
//if the row isn't the same size as existing rows, prints error and exits
template <class T>
void Table<T>::push_back_row(std::vector<T>& new_row){
	if(new_row.size() != cols_){
		std::cerr << "New row not the same size as existing rows" << std::endl;
		exit(1);
	}
	//creates new table with the correct dimensions and copies data over
	Table<T> t(this->rows_ + 1,this->cols_,this -> values[0][0]);
	for(unsigned i = 0; i< this->rows_; i++){
		for(unsigned j = 0; j< this->cols_; j++){
			t.values[i][j] = this->values[i][j];
		}
	}
	//adds in the new row
	for(unsigned i =0; i< cols_; i++){
		t.values[rows_][i] = new_row[i];
	}
	*this = t;
	
}

//removes a row from the table
//if there are no rows, prints error and exits
template <class T>
void Table<T>::pop_back_row(){
	if(rows_==0){
		std::cerr << "There are no rows" << std::endl;
		exit(1);
	}
	if(rows_==1){
		//removing a row results in the a 0 by 0 table
		clear();
	}
	else{
		//creates new table with the correct dimensions and copies data over
		Table<T> t(this->rows_-1,this->cols_,this -> values[0][0]);
		for(unsigned i = 0; i< t.rows_; i++){
			for(unsigned j = 0; j< t.cols_; j++){
				t.values[i][j] = this->values[i][j];
			}
		}
		*this = t;	
	}
}

//removes a column from the table
//if there are no columns, prints error and exits
template <class T>
void Table<T>::pop_back_column(){
	if(cols_==0){
		std::cerr << "There are no columns" << std::endl;
		exit(1);
	}
	if(cols_==1){
		//removing a column results in the a 0 by 0 table
		clear();
	}
	else{
		//creates new table with the correct dimensions and copies data over
		Table<T> t(this->rows_,this->cols_-1,this -> values[0][0]);
		for(unsigned i = 0; i< t.rows_; i++){
			for(unsigned j = 0; j< t.cols_; j++){
				t.values[i][j] = this->values[i][j];
			}
		}
		*this = t;
	}
}

//adds a column to the table
//if the column isn't the same size as existing columns, prints error and exits
template <class T>
void Table<T>::push_back_column(std::vector<T>& new_col){
	if(new_col.size() != rows_){
		std::cerr << "New column not the same size as existing columns" << std::endl;
		exit(1);
	}
	//creates new table with the correct dimensions and copies data over
	Table<T> t(this->rows_,this->cols_+1,this -> values[0][0]);
	for(unsigned i = 0; i< this->rows_; i++){
		for(unsigned j = 0; j< this->cols_; j++){
			t.values[i][j] = this->values[i][j];
		}
	}
	//adds in the new column
	for(unsigned i =0; i< rows_; i++){
		t.values[i][cols_] = new_col[i];
	}
	*this = t;
}

//adds more columns to the table
//if the columns aren't the same size as existing columns, prints error and exits
template <class T>
void Table<T>::push_back_columns(Table& new_t){
	if(new_t.rows_ != rows_){
		std::cerr << "New columns not the same size as existing columns" << std::endl;
		exit(1);
	}
	//creates new table with the correct dimensions and copies data over
	Table<T> t(this->rows_,this->cols_+new_t.cols_,this -> values[0][0]);
	for(unsigned i = 0; i< this->rows_; i++){
		for(unsigned j = 0; j< this->cols_; j++){
			t.values[i][j] = this->values[i][j];
		}
	}
	//adds in the new columns
	for(unsigned i =0; i< rows_; i++){
		for(unsigned j = 0; j < new_t.cols_; j++){
			t.values[i][cols_ + j] = new_t.values[i][j];
		}
		
	}
	*this = t;
}

//adds more rows to the table
//if the rows aren't the same size as existing rows, prints error and exits
template <class T>
void Table<T>::push_back_rows(Table& new_t){
	if(new_t.cols_ != cols_){
		std::cerr << "New rows not the same size as existing rows" << std::endl;
		exit(1);
	}
	//creates new table with the correct dimensions and copies data over
	Table<T> t(this->rows_ + new_t.rows_,this->cols_,this -> values[0][0]);
	for(unsigned i = 0; i< this->rows_; i++){
		for(unsigned j = 0; j< this->cols_; j++){
			t.values[i][j] = this->values[i][j];
		}
	}
	//adds in the new rows
	for(unsigned i =0; i< cols_; i++){
		for(unsigned j = 0; j< new_t.rows_; j++){
			t.values[rows_+j][i] = new_t.values[j][i];
		}
	}
	*this = t;
	
}
