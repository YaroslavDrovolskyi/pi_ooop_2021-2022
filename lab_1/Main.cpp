#include <iostream>
#include <vector>

#include "ArrayDeque.h"
#include"ArrayStack.h"
#include "ArrayQueue.h"

#include "LinkedStack.h"
#include "LinkedQueue.h"

#include"LinkedDeque.h"

#include "ArrayPriorityQueue.h"


int generate_random(std::size_t max = 100000) {
	assert(max > 0);
	return rand() % max;
}

template <typename Q, typename T, typename Callable>
bool TestQueue(Callable generate_random) {
	Q queue;
	std::vector<int> values;
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
	std::vector<int> values;
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
bool TestDeque(Callable generate_random) {
	D deque;
	std::vector<int> values;
	for (std::size_t i = 0; i < 10000; i++) {
		T val = generate_random();
		values.push_back(val);
		deque.push_back(val);
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());

		val = generate_random();
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

int main() {
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<int>, int>([]() { return generate_random(); }) << std::endl;

	std::cout << "TestStack (array): " << TestStack<ArrayStack<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<int>, int>([]() { return generate_random(); }) << std::endl;

	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<int>, int>([]() { return generate_random(); }) << std::endl;

	ArrayPriorityQueue<int> p_queue;
	p_queue.print();
	p_queue.push(1, 1);
	p_queue.push(2, 2);
	p_queue.push(1, 3);
	p_queue.push(4, 4);
	p_queue.push(1, 5);
	p_queue.push(1, 6);
	p_queue.push(7, 7);
	p_queue.push(1, 8);
	p_queue.push(1, 9);
	p_queue.push(11, 10);
	p_queue.push(1, 11);
	p_queue.push(18, 12);
	p_queue.print();

	std::cout << "\nPeek:" << p_queue.peek() << std::endl;
	std::cout << "\nPop:" << p_queue.pop() << std::endl;
	p_queue.print();
	std::cout << "\nPeek:" << p_queue.peek() << std::endl;

	return 0;
}

