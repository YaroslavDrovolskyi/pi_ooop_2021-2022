/*!
	\file
	\brief Header file for classes derived from MatricesMultiplicator class
*/

#pragma once
#include <string>
#include "Matrix.h"


/*!
	\brief Interface (abstract class) for all matrices multiplicators
*/
template <typename T>
class MatricesMultiplicator
{
public:
	virtual Matrix<T> multiply() = 0; ///< Perform multiplying
	virtual Matrix<T> getResult() const = 0; ///< Returns result of multiplying. \warning call only after .multiply()
	virtual ~MatricesMultiplicator() {};
};

/*!
	\brief Class that implement usual multiplying for matrices
*/
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

/*!
	\brief Base class for all Strassen algorithm subclasses
*/
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


/*!
	\brief Class that implement one-threaded Strassen algorithm
*/
template <typename T>
class MultiplyStrassenOneThreaded : public MultiplyStrassen<T>
{
private:
	virtual Matrix<T> multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) override;

public:
	MultiplyStrassenOneThreaded(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion = 32);
};

/*!
	\brief Class that implement multi-threaded Strassen algorithm
*/
template <typename T>
class MultiplyStrassenMultiThreaded : public MultiplyStrassen<T>
{
private:
	std::size_t max_threads_number;
	std::size_t active_threads_count;
	virtual Matrix<T> multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) override;

public:
	MultiplyStrassenMultiThreaded(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion = 32);
};


bool testMultiplication(std::size_t size, std::size_t number_of_tests);
void bencmarkMultiplication(uint64_t min_time_limit, const std::string& filename);

