/*!
	\file
	\brief File with implemenation of template QuickSort classes
*/

#include <iostream>
#include <thread>
#include <stdexcept>
#include <random>
#include <functional>
#include <algorithm>
#include <fstream>
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


/*!
	Function that apply one/multi - threaded quicksort on different types of random arrays. \n
	Also it check if array sorted correctly \n
	It will print time of algo's work in console

	\param[in] size is size of arrays, on which we will test quicksort
	\param[in] number_of_tests is number of test to perform. It must be > 0

*/
bool testQuickSort(std::size_t size, std::size_t number_of_tests) {
	if (size <= 0) {
		throw std::invalid_argument("testMultiplication(): size must be > 0");
	}
	if (number_of_tests <= 0) {
		throw std::invalid_argument("testMultiplication(): number_of_tests must be > 0");
	}

	for (std::size_t i = 0; i < number_of_tests; i++) {
		// generate arrays
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

/*!
	Function that apply QuickSort to array. \n
	Also it will print result time of algo working in stream file, and in console

	\param[in] sorter is instance of QuickSort class
	\param[in] arr is an array to sort
	\param[in] file is stream to write algo working time
	\param[in] algo_name is name of concrete QuickSort (one/multi - threaded, etc)

	\returns time of algo work

*/
uint64_t applyBechmarkSorting(QuickSort<int, bool(int, int)>& sorter, std::vector<int>& arr, std::ofstream& file, std::string algo_name) {
	uint64_t time = clock();
	sorter.sort(&arr, 0, arr.size() - 1);
	time = clock() - time;

	file << algo_name << static_cast<double>(time) / 1000 << " s \n";
	std::cout << algo_name << static_cast<double>(time) / 1000 << " s \n";


	return time;
}



/*!
	Function that measure productivity of one and multi - threaded quicksort on ddefferent types of random arrays. \n
	It will print time of algo's work in console and in file with name filename
	It will apply algorithms until their time will be bigger than min_time_limit

	\param[in] min_time_limit is time in ms. It must at least 200
	\param[in] filename is name of file where need to write benchmark results

*/
void bencmarkQuickSort(uint64_t min_time_limit, const std::string& filename) {
	if (min_time_limit < 200) {
		throw std::invalid_argument("bencmarkQuickSort(): min_time_limit must be >= 200");
	}

	std::ofstream file(filename);

	uint64_t random_time_one = 0;
	uint64_t random_time_multi = 0;

	uint64_t almost_sorted_time_one = 0;
	uint64_t almost_sorted_time_multi = 0;

	uint64_t revert_sorted_time_one = 0;
	uint64_t revert_sorted_time_multi = 0;

	uint64_t min_time = 0;
	std::size_t cur_size = 1000;

	QuickSortOneThreaded<int, bool(int, int)> one_th_sorter(comparatorAscend);
	QuickSortMultiThreaded<int, bool(int, int)> multi_th_sorter(comparatorAscend);

	

	while (min_time <= min_time_limit) {

		file << "SIZE = " << cur_size << "\n\n";
		std::cout << "SIZE = " << cur_size << "\n\n";

		std::vector<int> arr_random_1 = randomIntArray(cur_size);
		std::vector<int> arr_random_2{ arr_random_1 };

		std::vector<int> arr_almost_sorted_1 = randomIntAlmostSortedArray(cur_size, comparatorAscend);
		std::vector<int> arr_almost_sorted_2{ arr_almost_sorted_1 };

		std::vector<int> arr_revert_sorted_1 = randomIntSortedArray(cur_size, comparatorDescend);
		std::vector<int> arr_revert_sorted_2{ arr_revert_sorted_1 };

		file << "Random arrays" << std::endl;
		std::cout << "Random arrays" << std::endl;
		if (random_time_one <= min_time_limit) {
			random_time_one = applyBechmarkSorting(one_th_sorter, arr_random_1, file, "QuickSort (one-threaded): ");
		}
		if (random_time_multi <= min_time_limit) {
			random_time_multi = applyBechmarkSorting(multi_th_sorter, arr_random_2, file, "QuickSort (multi-threaded): ");
		}
		file << std::endl;
		std::cout << std::endl;


		file << "Almost sorted arrays" << std::endl;
		std::cout << "Almost sorted arrays" << std::endl;
		if (almost_sorted_time_one <= min_time_limit) {
			almost_sorted_time_one = applyBechmarkSorting(one_th_sorter, arr_almost_sorted_1, file, "QuickSort (one-threaded): ");
		}
		if (almost_sorted_time_multi <= min_time_limit) {
			almost_sorted_time_multi = applyBechmarkSorting(multi_th_sorter, arr_almost_sorted_2, file, "QuickSort (multi-threaded): ");
		}
		file << std::endl;
		std::cout << std::endl;


		file << "Revert sorted arrays" << std::endl;
		std::cout << "Revert sorted arrays" << std::endl;
		if (revert_sorted_time_one <= min_time_limit) {
			revert_sorted_time_one = applyBechmarkSorting(one_th_sorter, arr_revert_sorted_1, file, "QuickSort (one-threaded): ");
		}
		if (revert_sorted_time_multi <= min_time_limit) {
			revert_sorted_time_multi = applyBechmarkSorting(multi_th_sorter, arr_revert_sorted_2, file, "QuickSort (multi-threaded): ");
		}
		file << "\n\n\n\n\n\n";
		std::cout << "\n\n\n\n\n\n";


		min_time = std::min(std::min(std::min(random_time_one, random_time_multi), std::min(almost_sorted_time_one, almost_sorted_time_multi)), 
			std::min(revert_sorted_time_one, revert_sorted_time_multi));

		if (min_time < 4500) {
			cur_size *= 2;
		}
		else {
			cur_size += 100000;
		}

	}


	file.close();
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



