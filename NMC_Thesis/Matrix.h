//This is the header file for the Matrix class. This class will be used in the operaitons related to neural networks. 


#pragma once

#include <vector>
typedef float matrix_t;


class Matrix {
public:
	//Constructor of the class. This creares an object with zero rows and zero cols
	Matrix(int rows = 0, int cols = 0, matrix_t val = 0);

	//Implementation of the init function  belonging to the Matrix class

	//& is used in order to modify an object witouht creating a copy. This will improve memory managment 
	Matrix& init(int rows, int cols, matrix_t val = 0);

	Matrix& fill(matrix_t val);

	void print() const;

	// Inplace operations. These are operators which modify exisiting objects and do not create new ones. 
	//Addition operator
	Matrix& operator+=(const Matrix& other);

	//Multiplication
	Matrix& operator*=(matrix_t value); // Dot product.
	Matrix& multiply_inplace(const Matrix& other); // Element by element.

	//Unlike in - place operators(which modify * this), these return a new matrix with the result of the operation.
	 // Operators that'll return new matrix.
	//Operators overload
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(matrix_t value) const;
	Matrix transpose() const;
	Matrix multiply(const Matrix& other) const;


	//These functions are getter and setter methods for accessing and modifying elements in a matrix.

	matrix_t at(int row, int col) const;
	void set(int row, int col, matrix_t value);


	//The functions you listed provide various operations on matrices, including summation, randomization,
	//activation functions, and element-wise transformations.
	matrix_t sum() const;
	Matrix& randomize(matrix_t min = 0, matrix_t max = 1);
	Matrix& sigmoid();
	Matrix& square();


	//Meaning: This function returns a modifiable reference to the vector data. This allows the caller to modify the underlying vector.
	std::vector<matrix_t>& data();
	//This function returns a read-only reference to the vector. It ensures that the caller cannot modify the contents of the vector.
	const std::vector<matrix_t>& data() const;


	//These functions return a reference to the underlying matrix data stored in a std::vector<matrix_t>
	//Is used to inspect and modify the data of the matrix

	int rows() const;
	int cols() const;

private:
	int _rows, _cols;
	std::vector<matrix_t> _data;
};