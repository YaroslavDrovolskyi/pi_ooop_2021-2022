#include "pch.h"
#include "CppUnitTest.h"
#include <algorithm>


#include "../lab3a/Matrix.h"
#include "../lab3a/Matrix.cpp"

#include "../lab3a/MatricesMultiplication.h"
#include "../lab3a/MatricesMultiplication.cpp"

#include "../lab3a/QuickSort.h"
#include "../lab3a/QuickSort.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(MatricesMultiplicationTests)
	{
	public:
		
		TEST_METHOD(testMultiply)
		{
			// test correct input
			Assert::IsTrue(testMultiplication(128, 100));


			// test initialization by matrix with not the same sizes
			try {
				UsualMultiply<int> usual(Matrix<int>(10, 0), Matrix<int>(100, 0));
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				MultiplyStrassenOneThreaded<int> strassen_one(Matrix<int>(10, 0), Matrix<int>(100, 0));
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				MultiplyStrassenMultiThreaded<int> strassen_multi(Matrix<int>(10, 0), Matrix<int>(100, 0));
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}


			// test getting result before algo launching
			try {
				UsualMultiply<int> usual(Matrix<int>(10, 0), Matrix<int>(10, 0));
				usual.getResult();
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				MultiplyStrassenOneThreaded<int> strassen_one(Matrix<int>(10, 0), Matrix<int>(10, 0));
				strassen_one.getResult();
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}


			try {
				MultiplyStrassenMultiThreaded<int> strassen_multi(Matrix<int>(10, 0), Matrix<int>(10, 0));
				strassen_multi.getResult();
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

		}

		TEST_METHOD(testMatrix)
		{
			Matrix<int> m(10, 0);
			Assert::IsTrue(10 == m.getSize());

			 // test getting submatrix
			Matrix<int> submatrix = m.getSubmatrix(0, 0, 5);
			Assert::IsTrue(5 == submatrix.getSize());

			try {
				m.getSubmatrix(4, 0, 10);
			}
			catch (const std::exception& e) {
				// if we there, test is not failed
			}


			// test expanding matrix
			Matrix<int> expanded_m = m.getExpandedCopy(50);
			Assert::IsTrue(50 == expanded_m.getSize());

			try {
				m.getExpandedCopy(5);
			}
			catch (const std::exception& e) {
				// if we there, test is not failed
			}


			// test merging matrices
			Matrix<int> a11(50, 0), a12(50, 0), a21(50, 0), a22(50, 0);
			Matrix<int> merged_matrix = Matrix<int>::mergeMatrices(a11, a12, a21, a22);

			Assert::IsTrue(100 == merged_matrix.getSize());

			try {
				Matrix<int>::mergeMatrices(a11, a12, Matrix<int>(5, 0), a22);
			}
			catch (const std::exception& e) {
				// if we there, test is not failed
			}
		}
	};




	TEST_CLASS(QuickSortTests) {
		TEST_METHOD(testSorting) {
			// test correct input
			Assert::IsTrue(testQuickSort(1000, 1000));

			// test incorrect input
			std::vector<int> vec = randomIntArray(5000);
			QuickSortOneThreaded<int, bool(int, int)> sorter_one(comparatorAscend);
			QuickSortMultiThreaded<int, bool(int, int)> sorter_multi(comparatorAscend);
			

			// test when subarray is nullptr
			try {
				sorter_one.sort(nullptr, 0, 1000);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				sorter_multi.sort(nullptr, 0, 1000);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}



			// test when subarray bounds indexes are not correct
			try {
				sorter_one.sort(&vec, 1000, 1);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				sorter_multi.sort(&vec, 1000, 1);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}


			// test when subarray high bound >= size 
			try {
				sorter_one.sort(&vec, 0, 5001);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}

			try {
				sorter_multi.sort(&vec, 0, 5001);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}
		}

		TEST_METHOD(testisSorted) {
			std::vector<int> vec = randomIntArray(5000);

			std::sort(vec.begin(), vec.end(), comparatorAscend);
			Assert::IsTrue(isSorted(vec, 0, vec.size() - 1, comparatorAscend));

			// test when subarray bounds indexes are not correct
			try {
				isSorted(vec, 1000, 1, comparatorAscend);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}


			// test when subarray bounds indexes are not correct
			try {
				isSorted(vec, 0, 5001, comparatorAscend);
			}
			catch (const std::exception& e) {
				// if we there, test test doesn't failed
			}
		}
	};
}
