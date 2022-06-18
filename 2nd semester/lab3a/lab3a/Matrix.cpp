#include <exception>

#include "Matrix.h"


template <typename T>
Matrix<T>::Matrix(std::size_t size) : size(size)
{
	if (size <= 0) {
		throw std::invalid_argument("Matrix<T>::Matrix():   size must be > 0");
	}

	this->matrix = new T* [size];
	for (std::size_t i = 0; i < size; i++) {
		this->matrix[i] = new T[size];
	}
}

template <typename T>
Matrix<T>::Matrix(std::size_t size, T init_value) : 
	Matrix(size) // init empty matrix
{
	for (std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			this->matrix[i][j] = init_value;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) { // copy constructor
	this->size = other.size;

	this->matrix = new T* [size];
	for (std::size_t i = 0; i < size; i++) {
		this->matrix[i] = new T[size];

		std::copy(other.matrix[i], other.matrix[i] + other.size, this->matrix[i]);
	}
}

template <typename T>
void Matrix<T>::print() {
	for (std::size_t i = 0; i < this->size; i++) {
		for (std::size_t j = 0; j < this->size; j++) {
			std::cout << this->matrix[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
void Matrix<T>::printBracketsForm() {
	std::cout << "{";
	for (std::size_t i = 0; i < this->size; i++) {
		std::cout << "{";
		for (std::size_t j = 0; j < this->size; j++) {
			std::cout << this->matrix[i][j];
			if (j < this->size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "}";
		if (i < this->size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "}";
}

template <typename T>
Matrix<T>::~Matrix() {
	for (std::size_t i = 0; i < this->size; i++) {
		delete[] this->matrix[i];
	}
	delete[]this->matrix;
}


// create instances of necessary classes
template class Matrix<int>;
template class Matrix<double>;
