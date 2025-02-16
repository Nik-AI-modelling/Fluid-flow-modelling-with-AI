#ifdef SINGLE_SOURCE_IMPL

#include <stdlib.h>
#include <math.h>

//In this code, the author uses size_t a lot! This is unsgined integer type that is used to represent sizes, such as 
//indices and the number of elements.
//Adv: Guaranted to be non-negative since it's unsigned. Ideal for representing sizes. 
//it's defined in the stdlib.h.


//The code uses a lot of return *this; 
//This is used to allow chained operations 
//Matrix A, B, C
//A+=B+=C;

//Internally, _data stores it as a vector

Matrix::Matrix(int rows, int cols, matrix_t val)
	: _rows(rows), _cols(cols), _data(rows* cols, val)
{}

Matrix& Matrix::init(int rows, int cols, matrix_t val) {
	this->_rows = rows;
	this->_cols = cols;
	this->_data = std::vector<matrix_t>(rows * cols, val);
	return *this;
}


//To access element (row, col), we use function below. 
//index = row * _cols + col
//at(2, 2) → 2 * 3 + 2 = 8 → returns 9

matrix_t Matrix::at(int row, int col) const {
	return _data[row * _cols + col];
}

void Matrix::set(int row, int col, matrix_t value) {
	_data[row * _cols + col] = value;
}

Matrix& Matrix::fill(matrix_t val) {
	for (size_t i = 0; i < _data.size(); i++) {
		_data[i] = val;
	}
	return *this;
}

Matrix& Matrix::randomize(matrix_t min, matrix_t max) {

	assert(max > min);
	for (size_t i = 0; i < _data.size(); i++) {
		matrix_t val = (matrix_t)((float)rand() / (float)RAND_MAX) * (max - min) + min;
		_data[i] = val;
	}
	return *this;
}

matrix_t Matrix::sum() const {
	matrix_t total = 0;
	for (size_t i = 0; i < _data.size(); i++) {
		total += _data[i];
	}
	return total;
}

//!!!!!!//This applies the sigmoid activation funciton element-wise to a matrix. 
//The scope of the function is limited only to the file where it's applied i.e. Matrix.cpp
//Inline the function. This replaces funciton calls with function's code to optimise performance. 
static inline matrix_t sigmoid(matrix_t x) {
	return 1.f / (1.f + expf(-x));
}

//This function uses the advatage of newly created inline function
Matrix& Matrix::sigmoid() {
	for (size_t i = 0; i < _data.size(); i++) {
		_data[i] = ::sigmoid(_data[i]);
	}
	return *this;
}


//Find square of the matrix
Matrix& Matrix::square() {
	for (size_t i = 0; i < _data.size(); i++) {
		_data[i] = _data[i] * _data[i];
	}
	return *this;
}


std::vector<matrix_t>& Matrix::data() {
	return _data;
}


const std::vector<matrix_t>& Matrix::data() const {
	return _data;
}

int Matrix::rows() const {
	return _rows;
}

int Matrix::cols() const {
	return _cols;
}


void Matrix::print() const {
	printf("[\n");
	for (int r = 0; r < _rows; r++) {
		printf("  ");
		for (int c = 0; c < _cols; c++) {
			if (c != 0) printf(", ");
			// negative number has extra '-' character at the start.
			matrix_t val = at(r, c);
			if (val >= 0) printf(" %.6f", val);
			else printf("%.6f", val);
		}
		printf("\n");
	}
	printf("]\n");
}


//This defines overloaded operator += for a Matrix class. 
//This function overloads  the +-operator for objects of type Matrix. 
//Essentially, it adds one matrix to another. Operator overloading performs operations on objects 
//Return Type: Matrix& (Reference to *this)
//This function modifies the calling object(*this) directly.
//It returns a reference to* this, meaning the same object that called the operator is returned.

Matrix& Matrix::operator+=(const Matrix& other) {
	bool cond = (_rows == other._rows && _cols == other._cols);
	assert(_rows == other._rows && _cols == other._cols);
	for (size_t i = 0; i < _data.size(); i++) {
		_data[i] += other._data[i];
	}
	return *this;
}


Matrix& Matrix::operator*=(matrix_t value) {
	for (size_t i = 0;i < _data.size();i++) {
		_data[i] *= value;
	}

	//It returns a reference to the current object. 
	return *this; 

Matrix& Matrix::multiply_inplace(const Matrix & other) {
		assert(_rows == other._rows && _cols == other._cols);
		for (size_t i = 0; i < _data.size(); i++) {
			_data[i] *= other._data[i];
		}
		return *this;
}

//Matrix A, B, C;
//C = A - B; // A and B remain unchanged, and a new Matrix is assigned to C.

//Return Type: Matrix
//This function returns a new Matrix object.
//It does not modify the calling object(*this).

Matrix Matrix::operator-(const Matrix& other) const {
	assert(_rows == other._rows && _cols == other._cols);
	Matrix m(this->_rows, this->_cols);
	for (size_t i = 0; i < _data.size(); i++) {
		m._data[i] = this->_data[i] - other._data[i];
	}
	return m;
}


// (r1 x c1) * (r2 x c2) =>
//   assert(c1 == r2), result = (r1 x c2)
//Ensures that the number of columns in this (_cols)matches the number of rows in other(_rows).
//Matrix Multiplication Rule :
//If Matrix A has dimensions(r1 × c1) and Matrix B has dimensions(r2 × c2), then :

//	Multiplication is only valid if c1 == r2.
//	The resulting matrix will have dimensions r1 × c2.


Matrix Matrix::operator*(const Matrix& other) const {

	assert(this->_cols == other._rows);

	Matrix m(this->_rows, other._cols);

	int n = _cols; // Max Width or a row.
	for (int r = 0; r < m._rows; r++) {
		for (int c = 0; c < m._cols; c++) {

			matrix_t val = 0;
			for (int i = 0; i < n; i++) {
				val += this->at(r, i) * other.at(i, c);
			}
			m.set(r, c, val);
		}
	}

	return m;
}

Matrix Matrix::operator*(matrix_t value) const {
	Matrix m(_rows, _cols);
	std::vector<matrix_t>& m_data = m.data();
	for (size_t i = 0; i < _data.size(); i++) {
		m_data[i] = _data[i] * value;
	}
	return m;
}

Matrix Matrix::transpose() const {
	Matrix m(_cols, _rows);
	for (int r = 0; r < _rows; r++) {
		for (int c = 0; c < _cols; c++) {
			m.set(c, r, at(r, c));
		}
	}
	return m;
}


Matrix Matrix::multiply(const Matrix& other) const {
	assert(_rows == other._rows && _cols == other._cols);
	Matrix m(_rows, _cols);
	for (size_t i = 0; i < _data.size(); i++) {
		m._data[i] = _data[i] * other._data[i];
	}
	return m;
}

#endif // SINGLE_SOURCE_IMPL