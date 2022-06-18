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




public:
	Matrix(std::size_t size);
	Matrix(std::size_t size, T init_value);
	Matrix(const Matrix<T>& other);
	~Matrix();

	void print();

	void printBracketsForm();

	
};


#endif // _MATRIX_H_


