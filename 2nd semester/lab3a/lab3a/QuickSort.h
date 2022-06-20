/*!
	\file
	\brief Header file for template QuickSort classes
*/

#pragma once
#include <functional>
#include <string>
#include <fstream>
#include <vector>

/*!
	\brief Base class for all QuickSort algorithm subclasses
*/
template <typename T, typename Comparator>
class QuickSort {
protected:
	std::vector<T>* arr;
	std::function<Comparator> comparator;
	
	virtual std::size_t partition(std::size_t low, std::size_t high); // Lomuto's partition scheme
	virtual void sortImpl(std::size_t low, std::size_t high);
	virtual void runSortImplForSubarrays(std::size_t low, std::size_t high, std::size_t left, std::size_t right) = 0;
public:
	QuickSort(Comparator comp); ///< Constructor
	virtual void sort(std::vector<T>* arr, std::size_t low, std::size_t high); ///< Main function. low, high - start/end indexes of subarray to sort
};


/*!
	\brief Class that implement one-threaded QuickSort algorithm
*/
template <typename T, typename Comparator>
class QuickSortOneThreaded : public QuickSort<T, Comparator> {
private:
	virtual void runSortImplForSubarrays(std::size_t low, std::size_t high, std::size_t left, std::size_t right) override;

public:
	QuickSortOneThreaded(Comparator comparator);
};

/*!
	\brief Class that implement multi-threaded QuickSort algorithm
*/
template <typename T, typename Comparator>
class QuickSortMultiThreaded : public QuickSort<T, Comparator> {
private:
	std::size_t max_threads_number;
	std::size_t active_threads_count;

	virtual void runSortImplForSubarrays(std::size_t low, std::size_t high, std::size_t left, std::size_t right) override;

public:
	QuickSortMultiThreaded(Comparator comparator);
};


bool comparatorAscend(int a, int b);
bool comparatorDescend(int a, int b);

template <typename T> 
void printArray(const std::vector<T>& vec);


template<typename T, typename Comparator>
bool isSorted(const std::vector<T>& arr, std::size_t low, std::size_t high, Comparator comparator);


std::vector<int> randomIntArray(std::size_t size);

template <typename Comparator>
std::vector<int> randomIntSortedArray(std::size_t size, Comparator comparator);

template <typename Comparator>
std::vector<int> randomIntAlmostSortedArray(std::size_t size, Comparator comparator);


bool testQuickSort(std::size_t size, std::size_t number_of_tests);
void bencmarkQuickSort(uint64_t min_time_limit, const std::string& filename);
uint64_t applyBechmarkSorting(QuickSort<int, bool(int, int)>& sorter, std::vector<int>& arr, std::ofstream& file, std::string algo_name);

