#include <iostream>
#include <ctime>
#include <algorithm>
#include "Matrix.h"
#include "MatricesMultiplication.h"
#include "QuickSort.h"

int main() {
	std::cout << "================  Benchmark matrices multiplication ================" << std::endl;
	bencmarkMultiplication(5000, "multiplication_bechmark.txt");

	std::cout << "\n\n\n\n\n================  Benchmark QuickSort ================" << std::endl;
	bencmarkQuickSort(2500, "benchmark_quicksort.txt");
	return 0;
}