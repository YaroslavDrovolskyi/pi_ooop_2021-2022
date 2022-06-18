#pragma once
#include "Matrix.h"

template <typename T>
class MatricesMultiplicator
{
public:
	virtual Matrix<T> multiply() = 0;
	virtual Matrix<T> getResult() const = 0;
	virtual ~MatricesMultiplicator() {};
};


template <typename T>
class MultiplyStrassen : public MatricesMultiplicator<T>
{
private:
	Matrix<T> matrix1;
	Matrix<T> matrix2;
	Matrix<T> result;

	std::size_t min_size_for_recursion;
	bool is_launched_before;

	uint64_t getNextExpOfTwo(uint64_t n);
	//

public:
	MultiplyStrassen(const Matrix<T>& a, const Matrix<T>& b, std::size_t min_size_for_recursion = 32);
	virtual Matrix<T> multiply() override;
	virtual Matrix<T> getResult() const override;

	virtual ~MultiplyStrassen() {};
};


