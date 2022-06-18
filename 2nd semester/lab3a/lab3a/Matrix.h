#pragma once

#include <iostream>
#include <cassert>

#ifndef _MATRIX_H_
#define _MATRIX_H_

template <typename T>
class Matrix {
private:
	T** matrix;
	std::size_t size;

	void allocateMatrix();
	void deleteMatrix();


public:
	Matrix(std::size_t size);
	Matrix(std::size_t size, T init_value);
	Matrix(const Matrix<T>& other);
	~Matrix();

	Matrix<T>& operator=(const Matrix<T>& other);
	friend bool operator== (const Matrix<T>&a, const Matrix<T>&b);
	friend Matrix<T> operator+ (const Matrix<T>& a, const Matrix<T>& b);
	friend Matrix<T> operator- (const Matrix<T>& a, const Matrix<T>& b);


	Matrix<T> getSubmatrix(std::size_t start_row, std::size_t start_col, std::size_t size) const;
	Matrix<T> getExpandedCopy(std::size_t new_size) const;
	void print() const;
	void printBracketsForm() const;

	static Matrix<T> mergeMatrices(const Matrix<T>& a11, const Matrix<T>& a12, const Matrix<T>& a21, const Matrix<T>& a22);

	
};



//Matrix rand_matrix(std::size_t size = 5);



//Matrix usual_multiply(const Matrix& a, const Matrix& b);

//Matrix strassen_multiply(const Matrix& A, const Matrix& B, std::size_t min_size_for_recursion = 32);
//Matrix strassen_multiply_impl(const Matrix& A, const Matrix& B, std::size_t min_size_for_recursion);
//bool test_strassen(std::size_t matrix_size = 100, int N = 10);


#endif // _MATRIX_H_


