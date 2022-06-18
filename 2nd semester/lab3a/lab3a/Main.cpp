#include <iostream>
#include "Matrix.h"
#include "MatricesMultiplication.h"

int main() {
	Matrix<int> m(5, 5);
	m.printBracketsForm();


	Matrix<int> m1 = Matrix<int>::generateRandom(5);
	Matrix<int> m2 = Matrix<int>::generateRandom(5);

	MultiplyStrassenOneThreaded<int> calc(m1, m2);

	m1.printBracketsForm();
	std::cout << std::endl;
	m2.printBracketsForm();

	std::cout << std::endl << "===================== RESULT ====================" << std::endl;
	calc.multiply();
	calc.getResult().printBracketsForm();
//
//	MatricesMultiplicator<int> a;

//	MatrixMultiplyShtrassen<int> b;
	return 0;
}