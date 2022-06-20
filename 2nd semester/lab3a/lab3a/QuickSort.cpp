#include <iostream>
#include <thread>
#include <stdexcept>
#include <random>
#include <functional>
#include <algorithm>
#include "QuickSort.h"


template <typename T, typename Comparator>
QuickSort<T, Comparator>::QuickSort(Comparator comparator) :
	comparator(comparator),
	arr(nullptr)
{

}

// Lomuto's partition scheme
template <typename T, typename Comparator>
std::size_t QuickSort<T, Comparator>::partition(std::size_t low, std::size_t high) {
	std::size_t pivot_index = (high + low) / 2;
	T pivot = (*arr)[pivot_index];
	std::size_t i = low;

	for (std::size_t j = low; j <= high; j++) {
		if (comparator((*arr)[j], pivot) || ((*arr)[j] == pivot)) { // <=
			if (j == pivot_index) {
				pivot_index = i;
			}
			else if (i == pivot_index) {
				pivot_index = j;
			}
			std::swap((*arr)[j], (*arr)[i]);
			i++;
		}
	}

	if (i != low) {
		i--;
	}

	if (i != pivot_index) {
		std::swap((*arr)[pivot_index], (*arr)[i]);
		pivot_index = i;
	}

	return pivot_index;
}

template <typename T, typename Comparator>
void QuickSort<T, Comparator>::sort(std::vector<T>* arr, std::size_t low, std::size_t high) {
	if (!arr) {
		throw std::invalid_argument("sort(): pointer on array can't be a nullptr");
	}
	if (low > high) {
		throw std::invalid_argument("sort(): low index must be <= high index");
	}
	if (high >= arr->size()) {
		throw std::out_of_range("sort(): high index out of range");
	}

	this->arr = arr;

	sortImpl(low, high);
}


template <typename T, typename Comparator>
void QuickSort<T, Comparator>::sortImpl(std::size_t low, std::size_t high) {
	if (low >= high) {
		return;
	}


	std::size_t pi = partition(low, high); // pi - pivot index

	std::size_t left = pi;
	// move right border of left array (because items that = pivot is in middle and we don't need to sort them)
	while ((*arr)[left] == (*arr)[pi] && left != low) {
		left--;
	}

	if (left != high && left != pi) {
		left++;
	}


	std::size_t right = pi;
	// move left border of right array (because items that = pivot is in middle and we don't need to sort them)
	while ((*arr)[right] == (*arr)[pi] && right != high) {
		right++;
	}

	if (right != low && right != pi) {
		right--;
	}

	runSortImplForSubarrays(low, high, left, right);
	/*
	if (left == 0) {
		sortImpl(right + 1, high);
	}
	else {
		sortImpl(low, left - 1);
		sortImpl(right + 1, high);
	}
	*/
}


// one-threaded quick sort

template <typename T, typename Comparator>
QuickSortOneThreaded<T, Comparator>::QuickSortOneThreaded(Comparator comparator) :
	QuickSort<T, Comparator>(comparator)
{

}


template <typename T, typename Comparator>
void QuickSortOneThreaded<T, Comparator>::runSortImplForSubarrays(std::size_t low, std::size_t high, std::size_t left, std::size_t right) {
	if (left == 0) {
		this->sortImpl(right + 1, high);
	}
	else {
		this->sortImpl(low, left - 1);
		this->sortImpl(right + 1, high);
	}
}

template <typename T, typename Comparator>
QuickSortMultiThreaded<T, Comparator>::QuickSortMultiThreaded(Comparator comparator) :
	QuickSort<T, Comparator>(comparator),
	max_threads_number(std::thread::hardware_concurrency()), 
	active_threads_count(1)
{

}

template <typename T, typename Comparator>
void QuickSortMultiThreaded<T, Comparator>::runSortImplForSubarrays(std::size_t low, std::size_t high, std::size_t left, std::size_t right) {
	if (left == 0) {
		this->sortImpl(right + 1, high);
	}
	else {
		std::thread* t{ nullptr };
		if (active_threads_count < max_threads_number) {
			t = new std::thread(&QuickSortMultiThreaded<T, Comparator>::sortImpl, this, low, left - 1);

			active_threads_count++;
		}
		else {
			this->sortImpl(low, left - 1);
		}
		
		this->sortImpl(right + 1, high);


		if (t) {
			t->join();
			delete t;
			
			active_threads_count--;
		}
	}
}



std::vector<int> randomIntArray(std::size_t size) {
	static std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(-100000, 100000);

	std::vector<int> arr(size);
	for (std::size_t i = 0; i < size; i++) {
		arr[i] = dis(gen);
	}

	return arr;
}

template <typename Comparator>
std::vector<int> randomIntSortedArray(std::size_t size, Comparator comparator) {
	std::vector<int> arr = randomIntArray(size);
	std::sort(arr.begin(), arr.end(), comparator);

	return arr;
}

template <typename Comparator>
std::vector<int> randomIntAlmostSortedArray(std::size_t size, Comparator comparator) {
	std::vector<int> arr = randomIntSortedArray(size, comparator);

	// combine
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(0, 1);
	for (std::size_t i = 0; i < arr.size(); i+=2) {
		bool need_combine = static_cast<bool>(dis(gen));

		if (need_combine) {
			std::swap(arr[i], arr[arr.size() - 1 - i]);
		}
	}

	return arr;
}


template<typename T, typename Comparator>
bool isSorted(const std::vector<T>& arr, std::size_t low, std::size_t high, Comparator comparator) {
	if (low > high) {
		throw std::invalid_argument("isSorted(): low index must be <= high index");
	}
	if (high >= arr.size()) {
		throw std::out_of_range("isSorted(): high index out of range");
	}


	for (std::size_t i = low; i < high; i++) {
		if (!comparator(arr[i], arr[i + 1]) && (arr[i] != arr[i + 1])) {
			return false;
		}
	}

	return true;
}

template <typename T> 
void printArray(const std::vector<T>& vec) {
	if (vec.empty()) {
		std::cout << "Array is empty" << std::endl;
		return;
	}

	for (const auto& item : vec) {
		std::cout << item << " ";
	}

	std::cout << std::endl;
}

bool comparatorAscend(int a, int b) {
	return a < b;
}

bool comparatorDescend(int a, int b) {
	return a > b;
}



bool testQuickSort(std::size_t size, std::size_t number_of_tests) {
	if (size <= 0) {
		throw std::invalid_argument("testMultiplication(): size must be > 0");
	}
	if (number_of_tests <= 0) {
		throw std::invalid_argument("testMultiplication(): number_of_tests must be > 0");
	}

	for (std::size_t i = 0; i < number_of_tests; i++) {
		// 
		std::vector<int> arr_random_1 = randomIntArray(size);
		std::vector<int> arr_random_2 { arr_random_1 };

		std::vector<int> arr_almost_sorted_1 = randomIntAlmostSortedArray(size, comparatorAscend);
		std::vector<int> arr_almost_sorted_2{ arr_almost_sorted_1 };

		std::vector<int> arr_revert_sorted_1 = randomIntSortedArray(size, comparatorDescend);
		std::vector<int> arr_revert_sorted_2{ arr_revert_sorted_1 };


		// create sorters
		QuickSortOneThreaded<int, bool(int, int)> one_th_sorter(comparatorAscend);
		QuickSortMultiThreaded<int, bool(int, int)> multi_th_sorter(comparatorAscend);

		// run algorithms
		std::cout << "Test number: " << i + 1 << std::endl << std::endl;

		std::cout << "Random arrays" << std::endl;
		uint64_t start_time = clock();
		one_th_sorter.sort(&arr_random_1, 0, size - 1);
		std::cout << "Quick sort (one-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;

		start_time = clock();
		multi_th_sorter.sort(&arr_random_2, 0, size - 1);
		std::cout << "Quick sort (multi-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s\n" << std::endl;


		std::cout << "Almost sorted arrays" << std::endl;
		start_time = clock();
		one_th_sorter.sort(&arr_almost_sorted_1, 0, size - 1);
		std::cout << "Quick sort (one-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;

		start_time = clock();
		multi_th_sorter.sort(&arr_almost_sorted_2, 0, size - 1);
		std::cout << "Quick sort (multi-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s\n" << std::endl;


		std::cout << "Revert-sorted arrays" << std::endl;
		start_time = clock();
		one_th_sorter.sort(&arr_revert_sorted_1, 0, size - 1);
		std::cout << "Quick sort (one-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s" << std::endl;

		start_time = clock();
		multi_th_sorter.sort(&arr_revert_sorted_2, 0, size - 1);
		std::cout << "Quick sort (multi-threaded), N = " << size << ", time: " << static_cast<double>(clock() - start_time) / 1000 << " s\n\n\n\n\n" << std::endl;


		if (!isSorted(arr_random_1, 0, size - 1, comparatorAscend)) {
			std::cout << "QuickSort (one-threaded) result is incorrect (array isn't sorted)";
			return false;
		}

		if (!isSorted(arr_random_2, 0, size - 1, comparatorAscend)) {
			std::cout << "QuickSort (multi-threaded) result is incorrect (array isn't sorted)";
			return false;
		}
	}

	return true;
}

// create instrances classes and functions templates

template class QuickSort<int, bool(int, int)>;
template class QuickSort<double, bool(double, double)>;

template class QuickSortOneThreaded<int, bool(int, int)>;
template class QuickSortOneThreaded<double, bool(double, double)>;

template class QuickSortMultiThreaded<int, bool(int, int)>;
template class QuickSortMultiThreaded<double, bool(double, double)>;

template std::vector<int> randomIntSortedArray(std::size_t, bool(int, int));
template std::vector<int> randomIntAlmostSortedArray(std::size_t, bool(int, int));


template bool isSorted(const std::vector<int>& arr, std::size_t low, std::size_t high, bool(int, int));
template bool isSorted(const std::vector<double>& arr, std::size_t low, std::size_t high, bool(double, double));


template void printArray<int>(const std::vector<int>&);



