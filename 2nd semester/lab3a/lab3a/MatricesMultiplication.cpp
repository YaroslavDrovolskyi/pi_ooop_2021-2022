#include <exception>

#include "MatricesMultiplication.h"



template <typename T>
MultiplyStrassen<T>::MultiplyStrassen(const Matrix<T>& a, const Matrix<T>& b, std::size_t min_size_for_recursion) :
	matrix1(a), matrix2(b), min_size_for_recursion(min_size_for_recursion), is_launched_before(false)
{

}


template <typename T>
uint64_t MultiplyStrassen<T>::getNextExpOfTwo(uint64_t n){
	assert(n >= 0);
	uint64_t result = 2;
	while (result < n) {
		result *= 2;
	}

	return result;
}


template <typename T>
Matrix<T> MultiplyStrassen<T>::getResult() const {
	if (!is_launched_before) {
		throw std::logic_error("Calling getResult() before multiply()");
	}

	return this->result;
}
