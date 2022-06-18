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
class UsualMultiply : public MatricesMultiplicator<T> 
{
private:
	Matrix<T> matrix1;
	Matrix<T> matrix2;
	Matrix<T> result;

	bool is_launched_before;

public:
	UsualMultiply(const Matrix<T>& A, const Matrix<T>& B);
	virtual Matrix<T> multiply() override;
	virtual Matrix<T> getResult() const override;

	virtual ~UsualMultiply() {};

};

template <typename T>
class MultiplyStrassen : public MatricesMultiplicator<T>
{
protected:
	Matrix<T> matrix1;
	Matrix<T> matrix2;
	Matrix<T> result;

	std::size_t min_size_for_recursion;
	bool is_launched_before;

	uint64_t getNextExpOfTwo(uint64_t n);
	virtual Matrix<T> multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) = 0; // we will override it in subclasses

public:
	MultiplyStrassen(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion = 32);
	virtual Matrix<T> multiply() override;
	virtual Matrix<T> getResult() const override;

	virtual ~MultiplyStrassen() {};
};



template <typename T>
class MultiplyStrassenOneThreaded : public MultiplyStrassen<T>
{
private:
	virtual Matrix<T> multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) override;

public:
	MultiplyStrassenOneThreaded(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion = 32);
};


