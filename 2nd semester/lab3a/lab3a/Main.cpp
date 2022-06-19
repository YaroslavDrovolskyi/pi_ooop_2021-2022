#include <iostream>
#include <ctime>
#include "Matrix.h"
#include "MatricesMultiplication.h"

int main() {
//	Matrix<int> m(5, 5);
//	m.printBracketsForm();

	

	const std::size_t SIZE = 513;
//	Matrix<int> m1 = Matrix<int>::generateRandom(SIZE);
//	Matrix<int> m2 = Matrix<int>::generateRandom(SIZE);


	testMultiplication(SIZE, 10);

/*
	UsualMultiply<int> calc_usual(m1, m2);
	MultiplyStrassenOneThreaded<int> calc_one_th(m1, m2);
	MultiplyStrassenMultiThreaded<int> calc_multi_th(m1, m2);



	uint64_t start_time = clock();
	calc_usual.multiply();
	std::cout << "Simple multiply, N = " << SIZE << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;


	start_time = clock();
	calc_one_th.multiply();
	std::cout << "One-threaded Strassen, N = " << SIZE << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;


	start_time = clock();
	calc_multi_th.multiply();
	std::cout << "Multi-threaded Strassen, N = " << SIZE << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;

	std::cout << (calc_usual.getResult() == calc_one_th.getResult()) << std::endl;
	std::cout << (calc_one_th.getResult() == calc_multi_th.getResult()) << std::endl;
*/
//	m1.printBracketsForm();
	std::cout << std::endl;
//	m2.printBracketsForm();

//	std::cout << std::endl << "===================== RESULT ====================" << std::endl;
	
//		std::cout << (cacl_usual.multiply() == calc.multiply()) << std::endl;

//	calc.multiply();
	
	
//	cacl_usual.getResult().printBracketsForm();
//
//	MatricesMultiplicator<int> a;

//	MatrixMultiplyShtrassen<int> b;
	return 0;
}