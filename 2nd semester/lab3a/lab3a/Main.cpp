#include <iostream>
#include "Matrix.h"
#include "MatricesMultiplication.h"

int main() {
//	Matrix<int> m(5, 5);
//	m.printBracketsForm();


	Matrix<int> m1 = Matrix<int>::generateRandom(1000);
	Matrix<int> m2 = Matrix<int>::generateRandom(1000);

	MultiplyStrassenOneThreaded<int> calc(m1, m2);
	UsualMultiply<int> cacl_usual(m1, m2);

//	m1.printBracketsForm();
	std::cout << std::endl;
//	m2.printBracketsForm();

	std::cout << std::endl << "===================== RESULT ====================" << std::endl;
	std::cout << (cacl_usual.multiply() == calc.multiply()) << std::endl;
//	cacl_usual.getResult().printBracketsForm();
//
//	MatricesMultiplicator<int> a;

//	MatrixMultiplyShtrassen<int> b;
	return 0;
}