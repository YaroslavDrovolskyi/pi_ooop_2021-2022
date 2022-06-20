/*!
	\file
	\brief Filewith implementation of template class Matrix
*/

#include <exception>
#include <random>
#include "Matrix.h"


/*!
	Constructor. It creates matrix [size x size]
	\param[in] size is number of cols and number of rows
*/
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

/*!
	Constructor. It creates matrix [size x size] and init all cells with value init_value
	\param[in] size is number of cols and number of rows
	\param[in] init_value is initial value of all cells
*/
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

/*!
	Copy Constructor
*/
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) { // copy constructor
	this->size = other.size;

	this->matrix = new T* [size];
	for (std::size_t i = 0; i < size; i++) {
		this->matrix[i] = new T[size];

		std::copy(other.matrix[i], other.matrix[i] + other.size, this->matrix[i]);
	}
}


/*!
	It prints matrix as a rectangle
*/
template <typename T>
void Matrix<T>::print() const {
	for (std::size_t i = 0; i < this->size; i++) {
		for (std::size_t j = 0; j < this->size; j++) {
			std::cout << this->matrix[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*!
	It prints matrix in brackets form: {{<row[1] items>}, {<row[2] items>}, ..., {<row[size] items>}} \n
	This form is suitable for Wolfram (for example)
*/
template <typename T>
void Matrix<T>::printBracketsForm() const {
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
	std::cout << "}" << std::endl;
}


/*!
	Getter for size

	\returns size of matrix
*/
template <typename T>
inline std::size_t Matrix<T>::getSize() const {
	return this->size;
}


/*!
	Getter for item in cell (i, j) \n
	It check if indexes are correct

	\returns reference on item in cell (i, j)
*/
template <typename T>
inline T& Matrix<T>::item(std::size_t i, std::size_t j) {
	if (i >= this->size || j >= this->size) {
		throw std::out_of_range("item(): indexes out of bound");
	}

	return this->matrix[i][j];
}

template <typename T>
Matrix<T>::~Matrix() {
	for (std::size_t i = 0; i < this->size; i++) {
		delete[] this->matrix[i];
	}
	delete[]this->matrix;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other){

	// guard self assignment
	if (this == &other) {
		return *this;
	}

	if (size != other.size) {
		deleteMatrix(); // delete two-dimensional heap array

		this->size = other.size;
		allocateMatrix();
	}

	// copy data
	for (std::size_t i = 0; i < size; i++) {
		std::copy(other.matrix[i], other.matrix[i] + other.size, this->matrix[i]);
	}

	return* this;

	// example: https://en.cppreference.com/w/cpp/language/operators#:~:text=forms%3A%5B1%5D-,Assignment%20operator,-The%20assignment%20operator
}

// allocate new two-dimension array [size x size], in which matrix items is stored
template <typename T>
void Matrix<T>::allocateMatrix() {
	this->matrix = new T* [size];
	for (std::size_t i = 0; i < size; i++) {
		this->matrix[i] = new T[size];
	}
}

// delete two-dimension array, in which matrix items is stored
template <typename T>
void Matrix<T>::deleteMatrix() {
	for (std::size_t i = 0; i < this->size; i++) {
		delete[] this->matrix[i];
	}
	delete[]this->matrix;
}


template <typename T>
bool operator== (const Matrix<T>& a, const Matrix<T>& b) {
	if (a.size != b.size) {
		return false;
	}

	std::size_t size = a.size;

	for (std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			if (a.matrix[i][j] != b.matrix[i][j]) {
				return false;
			}
		}
	}

	return true;	
}

template <typename T>
Matrix<T> operator+ (const Matrix<T>& a, const Matrix<T>& b){
	if (a.size != b.size) {
		throw std::invalid_argument("operator+: matrices are not the same size");
	}


	Matrix<T> result(a.size);

	for (std::size_t i = 0; i < a.size; i++) {
		for (std::size_t j = 0; j < a.size; j++) {
			result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
		}
	}

	return result;

}


template <typename T>
Matrix<T> operator- (const Matrix<T>& a, const Matrix<T>& b) {
	if (a.size != b.size) {
		throw std::invalid_argument("operator-: matrices are not the same size");
	}


	Matrix<T> result(a.size);

	for (std::size_t i = 0; i < a.size; i++) {
		for (std::size_t j = 0; j < a.size; j++) {
			result.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
		}
	}

	return result;

}


/*!
	Merge 4 matrices [n x n] into one matrix [2n x 2n]

	\returns new matrix
*/
template <typename T>
Matrix<T> Matrix<T>::mergeMatrices(const Matrix<T>& a11, const Matrix<T>& a12, const Matrix<T>& a21, const Matrix<T>& a22) {
	if (a11.size != a12.size || a12.size != a21.size || a21.size != a22.size) {
		throw std::invalid_argument("mergeMatrices(): matrices are not the same size");
	}

	std::size_t size = 2 * a11.size;
	Matrix<T> result(size);

	for (std::size_t i = 0; i < size; i++) {
		if (i < size / 2) {
			std::copy(a11.matrix[i], a11.matrix[i] + size / 2, result.matrix[i]);
			std::copy(a12.matrix[i], a12.matrix[i] + size / 2, result.matrix[i] + size / 2);
		}
		else {
			std::copy(a21.matrix[i - size / 2], a21.matrix[i - size / 2] + size / 2, result.matrix[i]);
			std::copy(a22.matrix[i - size / 2], a22.matrix[i - size / 2] + size / 2, result.matrix[i] + size / 2);
		}
	}

	return result;
}


/*!
	Generate new square matrix with size size

	\param[in] size is sie of matrix
	\returns new matrix
*/
template <typename T>
Matrix<T> Matrix<T>::generateRandom(std::size_t size) {
	Matrix<T> result(size);


	static std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(-1000, 1000);

	for (std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			result.matrix[i][j] = dis(gen);
		}
	}

	return result;
}


/*!
	Return square submatrix of matrix
	\param[in] start_row is index of first row of submatrix
	\param[in] start_col is index of first col of submatrix
	\param[in] size is size of submatrix 

	\returns corresponding submatrix
*/
template <typename T>
Matrix<T> Matrix<T>::getSubmatrix(std::size_t start_row, std::size_t start_col, std::size_t size) const {
	if (!(start_row + size <= this->size && start_col + size <= this->size)) {
		throw std::out_of_range("getSubmatrix(): incorrect size of submatrix");
	}

	Matrix<T> result(size);

	for (std::size_t i = start_row; i < start_row + size; i++) {
		std::copy(this->matrix[i] + start_col, this->matrix[i] + start_col + size, result.matrix[i - start_row]);
	}

	return result;
}


/*!
	Creates new square matrix with size new_size with '0' padding at right and at bottom
	
	\param[in] size is size of new matrix

	\returns new matrix
*/
template <typename T>
Matrix<T> Matrix<T>::getExpandedCopy(std::size_t new_size) const {
	if (new_size <= this->size) {
		throw std::invalid_argument("getExpandedCopy(): new size must be bigger than matrix own size");
	}

	Matrix result(new_size, 0);

	for (std::size_t i = 0; i < this->size; i++) {
		std::copy(this->matrix[i], this->matrix[i] + this->size, result.matrix[i]);
	}

	return result;
}



// create instances of necessary classes
template class Matrix<int>;
template class Matrix<double>;


// create instances of necessary functions
template bool operator== (const Matrix<int>& a, const Matrix<int>& b);
template bool operator== (const Matrix<double>& a, const Matrix<double>& b);

template Matrix<int> operator+ (const Matrix<int>& a, const Matrix<int>& b);
template Matrix<double> operator+ (const Matrix<double>& a, const Matrix<double>& b);

template Matrix<int> operator- (const Matrix<int>& a, const Matrix<int>& b);
template Matrix<double> operator- (const Matrix<double>& a, const Matrix<double>& b);


