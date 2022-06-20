/*!
	\file
	\brief File with implemenation of classes derived from MatricesMultiplicator class
*/


#include <exception>
#include <thread>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include "MatricesMultiplication.h"


/*!
	Constructor

	\param[in] A is left matrix
	\paran[in] B is right matrix
*/
template <typename T>
UsualMultiply<T>::UsualMultiply(const Matrix<T>& A, const Matrix<T>& B) :
	matrix1(A), matrix2(B), result(A.getSize(), 0), is_launched_before(false)
{

}

template <typename T>
Matrix<T> UsualMultiply<T>::multiply() {
	if (this->matrix1.getSize() != this->matrix2.getSize()) {
		throw std::invalid_argument("multiply(): matrices are not the same size");
	}

	std::size_t size = matrix1.getSize();

	for (std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			for (std::size_t k = 0; k < size; k++) {
//				this->result.item(i,j) += matrix1.item(i, k) * matrix2.item(k,j);
				this->result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
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


/*!
	Constructor

	\param[in] a is left matrix
	\paran[in] b is right matrix
	]param[in] min_size_for_recursion it is size when algo stops divide task to a smaller tasks, and perform usual multiplying
*/
template <typename T>
MultiplyStrassen<T>::MultiplyStrassen(const Matrix<T>& a, const Matrix<T>& b, std::size_t min_size_for_recursion) :
	matrix1(a), matrix2(b), result(a.getSize()), min_size_for_recursion(min_size_for_recursion), is_launched_before(false)
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
	if (this->matrix1.getSize() != this->matrix2.getSize()) {
		throw std::invalid_argument("multiply(): matrices are not the same size");
	}
	assert(min_size_for_recursion > 2);

	std::size_t size = this->matrix1.getSize();
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
	MultiplyStrassen<T>(A, B, min_size_for_recursion)
{

}


template <typename T>
Matrix<T> MultiplyStrassenOneThreaded<T>::multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) {
	assert(A.getSize() == B.getSize());

	if (A.getSize() < this->min_size_for_recursion) { // use simple matrix multiplication
		UsualMultiply<T> calc(A, B);
		return calc.multiply();
	}
	else {
		std::size_t size = A.getSize() / 2;
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


		Matrix<T> c11 = (p1 + p4) + (p7 - p5);
		Matrix<T> c12 = p3 + p5;
		Matrix<T> c21 = p2 + p4;
		Matrix<T> c22 = (p1 - p2) + (p3 + p6);


		return Matrix<T>::mergeMatrices(c11, c12, c21, c22);		
	}
}


template <typename T>
MultiplyStrassenMultiThreaded<T>::MultiplyStrassenMultiThreaded(const Matrix<T>& A, const Matrix<T>& B, std::size_t min_size_for_recursion) :
	MultiplyStrassen<T>(A, B, min_size_for_recursion), 
	max_threads_number(std::thread::hardware_concurrency()),
	active_threads_count(1)
{

}



template <typename T>
Matrix<T> MultiplyStrassenMultiThreaded<T>::multiplyImpl(const Matrix<T>& A, const Matrix<T>& B) {
	assert(A.getSize() == B.getSize());

	if (A.getSize() < this->min_size_for_recursion) { // use simple matrix multiplication
		UsualMultiply<T> calc(A, B);
		return calc.multiply();
	}
	else {
		std::size_t size = A.getSize() / 2;
		Matrix<T> a11 = A.getSubmatrix(0, 0, size); //get_part_of_matrix(A, 0, 0, size);
		Matrix<T> a12 = A.getSubmatrix(0, size, size); //get_part_of_matrix(A, 0, size, size);
		Matrix<T> a21 = A.getSubmatrix(size, 0, size); //get_part_of_matrix(A, size, 0, size);
		Matrix<T> a22 = A.getSubmatrix(size, size, size); //get_part_of_matrix(A, size, size, size);


		Matrix<T> b11 = B.getSubmatrix(0, 0, size); //get_part_of_matrix(A, 0, 0, size);
		Matrix<T> b12 = B.getSubmatrix(0, size, size); //get_part_of_matrix(A, 0, size, size);
		Matrix<T> b21 = B.getSubmatrix(size, 0, size); //get_part_of_matrix(A, size, 0, size);
		Matrix<T> b22 = B.getSubmatrix(size, size, size); //get_part_of_matrix(A, size, size, size);




		Matrix<T> p1(1), p2(1), p3(1), p4(1), p5(1), p6(1);
		std::thread t1, t2, t3, t4, t5, t6;

		std::vector<std::thread*> active_threads;

		// p1
		if (active_threads_count < this->max_threads_number) {
			t1 = std::thread([&]() {
				p1 = multiplyImpl(a11 + a22, b11 + b22);
			});

			active_threads_count++;
			active_threads.push_back(&t1);
		}
		else {
			p1 = multiplyImpl(a11 + a22, b11 + b22);
		}

		// p2
		if (active_threads_count < this->max_threads_number) {
			t2 = std::thread([&]() {
				p2 = multiplyImpl(a21 + a22, b11);
			});

			active_threads_count++;
			active_threads.push_back(&t2);
		}
		else {
			p2 = multiplyImpl(a21 + a22, b11);
		}

		// p3
		if (active_threads_count < this->max_threads_number) {
			t3 = std::thread([&]() {
				p3 = multiplyImpl(a11, b12 - b22);
			});

			active_threads_count++;
			active_threads.push_back(&t3);
		}
		else {
			p3 = multiplyImpl(a11, b12 - b22);
		}

		// p4
		if (active_threads_count < this->max_threads_number) {
			t4 = std::thread([&]() {
				p4 = multiplyImpl(a22, b21 - b11);
			});

			active_threads_count++;
			active_threads.push_back(&t4);
		}
		else {
			p4 = multiplyImpl(a22, b21 - b11);
		}

		// p5
		if (active_threads_count < this->max_threads_number) {
			t5 = std::thread([&]() {
				p5 = multiplyImpl(a11 + a12, b22);
			});

			active_threads_count++;
			active_threads.push_back(&t5);
		}
		else {
			p5 = multiplyImpl(a11 + a12, b22);
		}

		// p6
		if (active_threads_count < this->max_threads_number) {
			t6 = std::thread([&]() {
				p6 = multiplyImpl(a21 - a11, b11 + b12);
			});

			active_threads_count++;
			active_threads.push_back(&t6);
		}
		else {
			p6 = multiplyImpl(a21 - a11, b11 + b12);
		}

		Matrix<T> p7 = multiplyImpl(a12 - a22, b21 + b22);

		// join all active threads
		for (auto& active_thread : active_threads) {
			active_thread->join();
		}

//		std::cout << "Number of active threads:   " << active_threads_count << std::endl;

		Matrix<T> c11 = (p1 + p4) + (p7 - p5);
		Matrix<T> c12 = p3 + p5;
		Matrix<T> c21 = p2 + p4;
		Matrix<T> c22 = (p1 - p2) + (p3 + p6);


		return Matrix<T>::mergeMatrices(c11, c12, c21, c22);
	}
}


/*!
	Function that apply all matrices multiplicators (usual, strassens) on random int matrices. \n
	It multiply matrices and check if result is correct (if it is the same with usual naive algrithm) \n
	It will print time of algo's work in console

	\param[in] size is size of matrices, on which we will test algorithms
	\param[in] number_of_tests is number of test to perform. It must be > 0

*/
bool testMultiplication(std::size_t size, std::size_t number_of_tests) {
	if (number_of_tests <= 0) {
		throw std::invalid_argument("testMultiplication(): number_of_tests must be > 0");
	}

	for (std::size_t i = 0; i < number_of_tests; i++) {
		Matrix<int> m1 = Matrix<int>::generateRandom(size);
		Matrix<int> m2 = Matrix<int>::generateRandom(size);

		// create multiplicators
		UsualMultiply<int> calc_usual(m1, m2);
		MultiplyStrassenOneThreaded<int> calc_one_th(m1, m2, 64);
		MultiplyStrassenMultiThreaded<int> calc_multi_th(m1, m2, 128);

		// run algorithms
		std::cout << "Test number: " << i + 1 << std::endl;
		uint64_t start_time = clock();
		calc_usual.multiply();
		std::cout << "Simple multiply, N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;


		start_time = clock();
		calc_one_th.multiply();
		std::cout << "One-threaded Strassen, N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;


		start_time = clock();
		calc_multi_th.multiply();
		std::cout << "Multi-threaded Strassen, N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s\n\n\n\n\n" << std::endl;


		if (!(calc_usual.getResult() == calc_one_th.getResult())) {
			std::cout << "Usual and Strassen (one-threaded) resukls are not the same";
			return false;
		}

		if (!(calc_one_th.getResult() == calc_multi_th.getResult())) {
			std::cout << "Strassen (one-threaded) and Strassen (,ulti-threaded) results are not the same";
			return false;
		}
	}

	return true;
}


/*!
	Function that measure productivity of matrices multiplicators (usual, strassens) on random int matrices. \n
	It will print time of algo's work in console and in file with name filename
	It will apply algorithms until their time will be bigger than min_time_limit

	\param[in] min_time_limit is time in ms. It must at least 200
	\param[in] filename is name of file where need to write benchmark results

*/
void bencmarkMultiplication(uint64_t min_time_limit, const std::string& filename) {
	if (min_time_limit < 200) {
		throw std::invalid_argument("bencmarkMultiplication(): min_time_limit must be >= 200");
	}

	std::ofstream file(filename);

	uint64_t usual_time = 0;
	uint64_t strassen_one_time = 0;
	uint64_t strassen_multi_time = 0;

	uint64_t min_time = 0;
	std::size_t cur_size = 64;

	while (min_time <= min_time_limit) {

		file << "SIZE = " << cur_size << "\n\n";
		std::cout << "SIZE = " << cur_size << "\n\n";

		Matrix<int> m1 = Matrix<int>::generateRandom(cur_size);
		Matrix<int> m2 = Matrix<int>::generateRandom(cur_size);


		if (usual_time <= min_time_limit) {
			usual_time = clock();
			UsualMultiply<int> calc_usual(m1, m2);
			calc_usual.multiply();
			usual_time = clock() - usual_time;

//			output += std::string("Usual multiply: ") + std::to_string(static_cast<double>(usual_time) / 1000) + std::string("\n");
			file << "Usual multiply: " << static_cast<double>(usual_time) / 1000 << " s \n";
			std::cout << "Usual multiply: " << static_cast<double>(usual_time) / 1000 << " s \n";

		}

		if (strassen_one_time <= min_time_limit) {
			strassen_one_time = clock();
			MultiplyStrassenOneThreaded<int> calc_one_th(m1, m2, 64);
			calc_one_th.multiply();
			strassen_one_time = clock() - strassen_one_time;

			file << "Strassen (one-threaded): " << static_cast<double>(strassen_one_time) / 1000 << " s \n";
			std::cout << "Strassen (one-threaded): " << static_cast<double>(strassen_one_time) / 1000 << " s \n";
		}

		if (strassen_multi_time <= min_time_limit) {
			strassen_multi_time = clock();
			MultiplyStrassenMultiThreaded<int> calc_multi_th(m1, m2, 128);
			calc_multi_th.multiply();
			strassen_multi_time = clock() - strassen_multi_time;

			file << "Strassen (multi-threaded): " << static_cast<double>(strassen_multi_time) / 1000 << " s \n";
			std::cout << "Strassen (multi-threaded): " << static_cast<double>(strassen_multi_time) / 1000 << " s \n";
		}
		file << "\n\n\n\n\n";
		std::cout << "\n\n\n\n\n";

		min_time = std::min(std::min(usual_time, strassen_one_time), strassen_multi_time);
		
		if (min_time < 1500) {
			cur_size *= 2;
		}
		else {
			cur_size += 150;
		}

	}

	
	file.close();
}



template class MatricesMultiplicator<int>;
template class MatricesMultiplicator<double>;


template class UsualMultiply<int>;
template class UsualMultiply<double>;

template class MultiplyStrassen<int>;
template class MultiplyStrassen<double>;

template class MultiplyStrassenOneThreaded<int>;
template class MultiplyStrassenOneThreaded<double>;

template class MultiplyStrassenMultiThreaded<int>;
template class MultiplyStrassenMultiThreaded<double>;