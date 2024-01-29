class Matrix{
public:
	Matrix(); 
	Matrix(unsigned int rowsCount,unsigned int colsCount, double fill);
	Matrix(const Matrix& neo);
	~Matrix();
	
	bool operator==(const Matrix& neo);
	bool operator!=(const Matrix& neo);
	int num_rows() const;
	int num_cols() const;
	void clear();
	bool get(unsigned int row_check, unsigned int column_check, double& num) const;
	bool set(unsigned int row_check, unsigned int column_check, double num);
	void multiply_by_coefficient(const double num);
	bool swap_row(unsigned int source_row, unsigned int target_row);
	void transpose();
	bool add(const Matrix& b);
	bool subtract(const Matrix& b);
	double* get_row(unsigned int num);
	double* get_col(unsigned int num);
	Matrix* quarter();
	Matrix operator=(const Matrix& neo);
	void resize(unsigned int numRows, unsigned int numCols, double fill);
private:
	unsigned int rows;
	unsigned int columns;
	double **array;
};

std::ostream& operator<< (std::ostream& out, const Matrix& neo);