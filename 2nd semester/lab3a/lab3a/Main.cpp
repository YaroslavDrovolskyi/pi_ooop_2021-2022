#include <iostream>
#include <ctime>
#include <algorithm>
#include "Matrix.h"
#include "MatricesMultiplication.h"
#include "QuickSort.h"

int main() {
//	Matrix<int> m(5, 5);
//	m.printBracketsForm();

	

	const std::size_t SIZE = 1e6;

//	std::vector<int> vec = randomIntArray(SIZE);
//	std::sort(vec.begin(), vec.end());
//	std::cout << "sorted" << std::endl;
//	testQuickSort(SIZE, 10);
	bencmarkQuickSort(5000, "benchmark_quicksort.txt");
/*
	std::vector<int> vec = randomIntArray(SIZE);

	printArray(vec);

	QuickSortMultiThreaded<int, bool(int, int)> sorter(comparatorAscend);
	sorter.sort(&vec, 0, SIZE - 1);
	printArray(vec);

	std::cout << std::endl << "Is sorted: " << std::boolalpha << isSorted(vec, 0, SIZE - 1, comparatorAscend) << std::noboolalpha;
*/
//	std::cout << testMultiplication(SIZE, 1000) << std::endl;
//	bencmarkMultiplication(15000, "multiplication_bechmark.txt");


 /*
	Matrix<int> m1 = Matrix<int>::generateRandom(4);
	Matrix<int> m2 = Matrix<int>::generateRandom(4);

	UsualMultiply<int> calc_usual(m1, m2);
	MultiplyStrassenOneThreaded<int> calc_one_th(m1, m2);
	MultiplyStrassenMultiThreaded<int> calc_multi_th(m1, m2);


	m1.printBracketsForm();
	std::cout << std::endl;
	m2.printBracketsForm();
	std::cout << std::endl;

	calc_multi_th.multiply().printBracketsForm();


*/


/*
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