#include <exception>

#include "MatricesMultiplication.h"

template <typename T>
UsualMultiply<T>::UsualMultiply(const Matrix<T>& A, const Matrix<T>& B) :
	matrix1(A), matrix2(B), result(A.size, 0), is_launched_before(false)
{

}

template <typename T>
Matrix<T> UsualMultiply<T>::multiply() {
	if (this->matrix1.size != this->matrix2.size) {
		throw std::invalid_argument("multiply(): matrices are not the same size");
	}

	for (std::size_t i = 0; i < matrix1.size; i++) {
		for (std::size_t j = 0; j < matrix2.size; j++) {
			for (std::size_t k = 0; k < matrix1.size; k++) {
				this->result.matrix[i][j] += matrix1.matrix[i][k] * matrix1.matrix[k][j];
			}
		}
	}

	is_launched_before = true;
	return this->result;
}

template <typename T>
Matrix<T> UsualMultiply<T>::getResult() const {
	if (!is_launched_before) {
		throw std::logic_error("Calling getResult() before multiply()");
	}

	return this->result;
}

template <typename T>
MultiplyStrassen<T>::MultiplyStrassen(const Matrix<T>& a, const Matrix<T>& b, std::size_t min_size_for_recursion) :
	matrix1(a), matrix2(b), result(a.size), min_size_for_recursion(min_size_for_recursion), is_launched_before(false)
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



template <typename T>
Matrix<T> MultiplyStrassen<T>::multiply() {
	if (this->matrix1.size != this->matrix2.size) {
		throw std::invalid_argument("multiply(): matrices are not the same size");
	}
	assert(min_size_for_recursion > 2);

	std::size_t size = this->matrix1.size;
	std::size_t new_size = getNextExpOfTwo(size);

	if (size == new_size) {
		this->result = multiplyImpl(matrix1, matrix2);
	}
	else {
		Matrix<T> expanded_a = matrix1.getExpandedCopy(new_size);
		Matrix<T> expanded_b = matrix2.getExpandedCopy(new_size);
		Matrix<T> expanded_result = multiplyImpl(expanded_a, expanded_b);

		this->result = expanded_result.getSubmatrix(0, 0, size);
	}

	is_launched_before = true;
	return this->result;
}



template <typename T>
MultiplyStrassenOneThreaded<T>::MultiplyStrassenOneThreaded(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion) :
	MultiplyStrassen(A, B, min_size_for_recursion)
{

}


template <typename T>
Matrix<T> MultiplyStrassenOneThreaded<T>::multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) {
	assert(A.size == B.size);

	if (A.size < this->min_size_for_recursion) { // use simple matrix multiplication
		UsualMultiply<T> calc(A, B);
		return calc.multiply();
	}
	else {
		std::size_t size = A.size / 2;
		Matrix<T> a11 = A.getSubmatrix(0, 0, size); //get_part_of_matrix(A, 0, 0, size);
		Matrix<T> a12 = A.getSubmatrix(0, size, size); //get_part_of_matrix(A, 0, size, size);
		Matrix<T> a21 = A.getSubmatrix(size, 0, size); //get_part_of_matrix(A, size, 0, size);
		Matrix<T> a22 = A.getSubmatrix(size, size, size); //get_part_of_matrix(A, size, size, size);


		Matrix<T> b11 = B.getSubmatrix(0, 0, size); //get_part_of_matrix(A, 0, 0, size);
		Matrix<T> b12 = B.getSubmatrix(0, size, size); //get_part_of_matrix(A, 0, size, size);
		Matrix<T> b21 = B.getSubmatrix(size, 0, size); //get_part_of_matrix(A, size, 0, size);
		Matrix<T> b22 = B.getSubmatrix(size, size, size); //get_part_of_matrix(A, size, size, size);

		Matrix<T> p1 = multiplyImpl(a11 + a22, b11 + b22);
		Matrix<T> p2 = multiplyImpl(a21 + a22, b11);
		Matrix<T> p3 = multiplyImpl(a11, b12 - b22);
		Matrix<T> p4 = multiplyImpl(a22, b21 - b11);
		Matrix<T> p5 = multiplyImpl(a11 + a12, b22);
		Matrix<T> p6 = multiplyImpl(a21 - a11, b11 + b12);
		Matrix<T> p7 = multiplyImpl(a12 - a22, b21 + b22);

		/*
		Matrix p1 = strassen_multiply_impl(sum(a11, a22), sum(b11, b22), min_size_for_recursion);
		Matrix p2 = strassen_multiply_impl(sum(a21, a22), b11, min_size_for_recursion);
		Matrix p3 = strassen_multiply_impl(a11, subtract(b12, b22), min_size_for_recursion);
		Matrix p4 = strassen_multiply_impl(a22, subtract(b21, b11), min_size_for_recursion);
		Matrix p5 = strassen_multiply_impl(sum(a11, a12), b22, min_size_for_recursion);
		Matrix p6 = strassen_multiply_impl(subtract(a21, a11), sum(b11, b12), min_size_for_recursion);
		Matrix p7 = strassen_multiply_impl(subtract(a12, a22), sum(b21, b22), min_size_for_recursion);
		*/

		Matrix<T> c11 = (p1 + p4) + (p7 - p5);
		Matrix<T> c12 = p3 + p5;
		Matrix<T> c21 = p2 + p4;
		Matrix<T> c22 = (p1 - p2) + (p3 + p6);


		return Matrix<T>::mergeMatrices(c11, c12, c21, c22);		
	}
}



template class MatricesMultiplicator<int>;
template class MatricesMultiplicator<double>;


template class UsualMultiply<int>;
template class UsualMultiply<double>;

template class MultiplyStrassen<int>;
template class MultiplyStrassen<double>;

template class MultiplyStrassenOneThreaded<int>;
template class MultiplyStrassenOneThreaded<double>;