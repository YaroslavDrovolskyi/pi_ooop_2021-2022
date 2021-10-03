#pragma once

#ifndef _TESTS_
#define _TESTS_

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#include "Graph.h"

int get_random_int(std::size_t max = 100000) {
	assert(max > 0);
	return rand() % max;
}

template <typename Q, typename T, typename Callable>
bool TestQueue(Callable generate_random) {
	Q queue;
	std::vector<T> values;
	for (std::size_t i = 0; i < 10000; i++) {
		T val = generate_random();
		values.push_back(val);
		queue.push(val);

		assert(values.size() == queue.get_size());
		assert((values.size() == 0) == queue.is_empty());
	}

	while (!queue.is_empty()) {
		assert(values[0] == queue.pop());
		values.erase(values.begin());

		assert(values.size() == queue.get_size());
		assert((values.size() == 0) == queue.is_empty());
	}

	return true;
}


template <typename S, typename T, typename Callable>
bool TestStack(Callable generate_random) {
	S stack;
	std::vector<T> values;
	for (std::size_t i = 0; i < 10000; i++) {
		T val = generate_random();
		values.push_back(val);
		stack.push(val);

		assert(values[values.size() - 1] == stack.peek());
		assert((values.size() == 0) == stack.is_empty());
	}

	while (!stack.is_empty()) {
		assert(values[values.size() - 1] == stack.peek());
		assert(values[values.size() - 1] == stack.pop());
		values.pop_back();

		assert((values.size() == 0) == stack.is_empty());
	}

	return true;
}

template <typename D, typename T, typename Callable>
bool TestDeque(Callable get_random_data) {
	D deque;
	std::vector<T> values;
	for (std::size_t i = 0; i < 10000; i++) {
		T val = get_random_data();
		values.push_back(val);
		deque.push_back(val);
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());

		val = get_random_data();
		values.insert(values.begin(), val);
		deque.push_front(val);
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());
	}


	while (!deque.is_empty()) {
		assert(values[values.size() - 1] == deque.pop_back());
		values.pop_back();
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());

		assert(values[0] == deque.pop_front());
		values.erase(values.begin());
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());
	}

	return true;
}

template <typename T>
struct Container{
	std::size_t priority;
	T data;

	Container(std::size_t priority, const T& data) {
		this->priority = priority;
		this->data = data;
	}
};

template <typename T>
bool compare_priority(const Container<T>& a, const Container<T>& b) {
	return a.priority > b.priority;
}

template <typename PQ, typename T, typename Callable>
bool TestPriorityQueue(Callable get_random_data) {
	PQ p_queue;
	std::vector<Container<T>> values;
	for (std::size_t i = 0; i < 100000; i++) {
		T val = get_random_data();
		std::size_t priority = rand() % 1000;

		p_queue.push(priority, val);
		values.push_back(Container<T>(priority, val));
	}

	std::stable_sort(values.begin(), values.begin() + values.size(), [](const Container<T>& a, const Container<T>& b) {return compare_priority(a, b); });

	while (!p_queue.is_empty()) {
		assert(values[0].data == p_queue.peek());
		assert(values[0].data == p_queue.pop());
		values.erase(values.begin());

		assert((values.size() == 0) == p_queue.is_empty());
	}
	assert(p_queue.is_empty());

	return true;
}


template <typename S, typename Callable>
S get_random_stack(std::size_t size, Callable get_random_data) {
	S stack;
	for (std::size_t i = 0; i < size; i++) {
		stack.push(get_random_data());
	}
	return stack;
}

template <typename Q, typename Callable>
Q get_random_queue(std::size_t size, Callable get_random_data) {
	Q queue;
	for (std::size_t i = 0; i < size; i++) {
		queue.push(get_random_data());
	}
	return queue;
}

template <typename D, typename Callable>
D get_random_deque(std::size_t size, Callable get_random_data) {
	D deque;
	for (std::size_t i = 0; i < size; i++) {
		deque.push_back(get_random_data());
	}
	return deque;
}

template <typename PQ, typename Callable>
PQ get_random_priority_queue(std::size_t size, Callable get_random_data) {
	PQ p_queue;
	for (std::size_t i = 0; i < size; i++) {
		p_queue.push(get_random_int(1000), get_random_data());
	}
	return p_queue;
}


#endif // _TESTS_
