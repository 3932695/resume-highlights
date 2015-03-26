#ifndef MATRIX_H
#define MATRIX_H
//======================================================================
//  FILE:               matrix.h
//  PROGRAMMER:         Rick Decker
//  PURPOSE:            Declaration of the Matrix class
//  UPDATE HISTORY:     1.1 	5/29/13		combined .h and .cpp into one file
//						1.0     7/14/5
//======================================================================

//----------------------------------- NOTES ------------------------------------
/*
	Chris' driver program doesn't use the - overload or scalar multiplication,
	so they can be removed here and in matrix.cpp.  Also, the output function
	is used only for debugging so could also be eliminated.
*/
#include <iostream>
#include <cassert>

using namespace std;

class Matrix {
public:
	//-------------------- ctors, dtor, assignment overload --------------------
	
	Matrix();
	Matrix(int r, int c);
	Matrix(int r, int c, const double* array);
	Matrix(const Matrix & other);
	
	~Matrix();
	
	Matrix& operator= (const Matrix & other);
	
	//----------------------- matrix arithmetic overloads ----------------------
	
	Matrix operator+ (const Matrix & other) const;
	Matrix operator- (const Matrix & other) const;
	Matrix operator* (const Matrix & other) const;
	Matrix operator* (double scalar) const;
	
	//----------------------------- matrix operators ---------------------------
	
	Matrix invert() const;
	Matrix transpose() const;
	
	//-------------------------------- inspectors ------------------------------
	
	int getRows() const;
	int getCols() const;
	double getElement(int i) const;
	double getElement(int r, int c) const;
	void display() const;
	
private:
	int rows;		// number of rows in this matrix
	int cols;		// number of columns in this matrix
	double* data;	// the elements of this matrix (row-major order)
	
	void swapRows(int i, int j);
	void multiply(int row, double scalar);
	void linComb(int i, int j, double scalar);
};

//============================================================================
//
//                 MATRIX MEMBER FUNCTION DEFINITIONS 
//
//============================================================================

/**********************************************************************
	Default ctor: make a 0 by 0 matrix.
**********************************************************************/
Matrix::Matrix() : rows(0), cols(0), data(NULL)
{}

/**********************************************************************
	Zero ctor: make an r by c zero matrix.
**********************************************************************/
Matrix::Matrix(int r, int c) : rows(r), cols(c), data(new double[rows * cols]) {
	for (int i = 0; i < rows * cols; i++) {
		data[i] = 0.0;
	}
}

/**********************************************************************
	Array ctor: make a r by c matrix with data (in row-major order)
	from a specified array of doubles.
	PRE: The array size is r * c
**********************************************************************/
Matrix::Matrix(int r, int c, const double* array) 
	: rows(r), cols(c), data(new double[rows * cols]) {
	for (int i = 0; i < rows * cols; i++) { 
		data[i] = array[i];
	}
}
	
/**********************************************************************
	Copy ctor
**********************************************************************/
Matrix::Matrix(const Matrix & other) 
	: rows(other.rows), cols(other.cols), data(new double[rows * cols]) {
	for (int i = 0; i < rows * cols; i++) {
		data[i] = other.data[i];
	}
}
	
/**********************************************************************
	Dtor: kill the data array
**********************************************************************/
Matrix::~Matrix() {

	delete[] data;
}
	
/**********************************************************************
	Assignment overload
**********************************************************************/
Matrix& Matrix::operator= (const Matrix & other) {

	if (this != &other) {	// no need to assign to ourself
		rows = other.rows;
		cols = other.cols;
		delete[] data;
		data = new double[rows * cols];
		for (int i = 0; i < rows * cols; i++) {
			data[i] = other.data[i];
		}
	}
	return *this;
}
	
/**********************************************************************
	Addition overload
	PRE; the dimensions of self and other match
	POST: this matrix is unchanged
	RETURNS: a copy of self + other.
**********************************************************************/
Matrix Matrix::operator+ (const Matrix & other) const {
	
	assert((rows == other.rows) && (cols == other.cols));
	
	Matrix r(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		r.data[i] = data[i] + other.data[i];
	}
	return r;
}
	
/**********************************************************************
	Subtraction overload
	PRE; the dimensions of self and other match
	POST: this matrix is unchanged
	RETURNS: a copy of self - other.
**********************************************************************/
Matrix Matrix::operator- (const Matrix & other) const {
	
	assert((rows == other.rows) && (cols == other.cols));
	
	Matrix r(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		r.data[i] = data[i] - other.data[i];
	}
	return r;
}
	
/**********************************************************************
	Matrix multiplication overload
	PRE: we can multiply, i.e., cols == other.rows
	POST: this matrix is unchanged
	RETURNS: a copy of self * other.
**********************************************************************/
Matrix Matrix::operator* (const Matrix & other) const {

	assert(cols == other.rows);
	
	Matrix r(rows, other.cols);
	for (int i = 0; i < rows * other.cols; i++) {
		double entry = 0.0;
		int start1 = (i / other.cols) * cols;	// row start index in *this of i
		int start2 = i % other.cols;			// col start index in other of i
		for (int j = 0; j < cols; j++) {
			entry += data[start1 + j] * other.data[start2 + j * other.cols];
		}
		r.data[i] = entry;
	}
	return r;
}

/**********************************************************************
	Scalar multiplication overload (scalar must come second)
	POST: This matrix is unchanged
	RETURNS: a copy of self * scalar
**********************************************************************/
Matrix Matrix::operator* (double scalar) const {

	Matrix r(rows, cols);
	for (int i = 0; i < rows * cols; i++) {
		r.data[i] = scalar * data[i];
	}
	return r;
}
	
/**********************************************************************
	Make the inverse of this matrix, usiing Gauss-Jordan elimination.
	PRE: this matrix is square
	POST: this matrix is unchanged.
	RETURNS: a copy of the inverse of this matrix.
**********************************************************************/
Matrix Matrix::invert() const {

	assert(rows == cols);
	
	int i = 0;
	int j = 0;
	int N = rows;
	double element = 0.0;
	
	Matrix r = *this;
	
	// Construct an identity matrix of the same size as this one.
	Matrix inv(N, N);
	for (i = 0; i < N; i++)
		inv.data[i * (N + 1)] = 1.0;
		
	for (i = 0; i < N; i++) {
		// Find a row at or below row i with a nonzero value in column i
		for (j = i; (r.data[i + j * N] == 0.0) && (j < N); j++) {}
		
		if (j >= N) {	// failed to find a nonzero element in column i
			cout << "**** Attempted to invert a singular matrix. Nothing further is valid" << endl;
			return r;
		}
		// Found a nonzero element at [i,j]: swap rows to put it row i
		r.swapRows(i, j); inv.swapRows(i, j);
		
		// Reduce it to 1 by dividing everything in row i by data[i,i]
		element = 1.0 / r.data[i + i * N];
		r.multiply(i, element); inv.multiply(i, element);
		
		// Reduce so that every other element in col i is zero.
		for (j = 0; j < N; j++) {
			element = r.data[i % N + j * N];
			if ((j != i) && (element != 0.0)) {
				r.linComb(j, i, -element); inv.linComb(j, i, -element);
			}
		}
	}
	return inv;
}
	
/**********************************************************************
	Make the transpose of this matrix.
	POST: this matrix is unchanged.
	RETURNS: a copy of the transpose of this matrix.
**********************************************************************/
Matrix Matrix::transpose() const {

	Matrix r(cols, rows);
	for (int i = 0; i < rows * cols; i++) {
		r.data[i] = data[i / rows + (i % rows) * cols];
	}
	return r;
}

/**********************************************************************
	Get the number of rows.
	POST: this matrix is unchanged.
	RETURNS: the number of rows in this matrix.
**********************************************************************/
int Matrix::getRows() const {

	return rows;
}

/**********************************************************************
	Get the number of columns.
	POST: this matrix is unchanged.
	RETURNS: tthe number of columns in this matrix.
**********************************************************************/
int Matrix::getCols() const {

	return cols;
}

/**********************************************************************
	Get the element at index i in row-major order.
	PRE: 0 <= i < rows * cols
	POST: this matrix is unchanged.
	RETURNS: the element in index in this matrix.
**********************************************************************/
double Matrix::getElement(int i) const {

	assert((0 <= i) && (i < rows * cols));
	
	return data[i];
}

/**********************************************************************
	Get the element at row r and column c of this matrix.
	PRE: [r, c] is a valid position in this matrix
	POST: this matrix is unchanged.
	RETURNS: the element in position [r, c] in this matrix.
**********************************************************************/
double Matrix::getElement(int r, int c) const {

	assert((0 <= r) && (r < rows) && (0 <= c) && (c < cols));
	
	return data[c + r * cols];
}

/**********************************************************************
	Print this matrix on standard output. For diagnostic purposes only.
	PRE: none
	POST: this matrix is unchanged.
**********************************************************************/
void Matrix::display() const {
	int cols = getCols();
	
	cout << "-------------------------------------------" << endl;
	for (int i = 0; i < getRows() * cols; i++) {
		cout << "\t" << getElement(i);
		if (i % cols == cols - 1) {
			cout << endl;
		}
	}
	cout << "-------------------------------------------" << endl;
}

/**********************************************************************
	PRIVATE utility: Interchange rows i and j of this matrix.
	PRE: i and j are in range (i.e., in [0, rows - 1]).
**********************************************************************/
void Matrix::swapRows(int i, int j) {

	assert((i >= 0) && (j >= 0) && (i < rows) && (j < rows));
	
	if (i != j) {	// only need to swap if i and j are different
		for (int c = 0; c < cols; c++) {
			double temp = data[c + i * cols];
			data[c + i * cols] = data[c + j * cols];
			data[c + j * cols] = temp;
		}
	}
}

/**********************************************************************
	PRIVATE utility: multiply row's contents by scalar.
	PRE: row is in range (i.e., in [0, rows - 1]).
**********************************************************************/
void Matrix::multiply(int row, double scalar) {

	assert((0 <= row) && (row < rows));
	
	for (int c = 0; c < cols; c++) {
		data[c + row * cols] *= scalar;
	}
}

/**********************************************************************
	PRIVATE utility: do one row reduction
	PRE: i, j are in range (i.e., in [0, rows - 1]) AND matrix is square.
	POST: row i = row i + s * row j
**********************************************************************/
void Matrix::linComb(int i, int j, double scalar) {

	assert(rows == cols);
	
	if (i == j)		// do nothing if i, j are the same row
		return;
	
	int coli = i * rows;
	int colj = j * rows;
	for (int k = 0; k < cols; k++) {
		data[k + coli] += scalar * data[k + colj];
	}
}
#endif


