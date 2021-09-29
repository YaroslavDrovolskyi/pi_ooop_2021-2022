#include <iostream>
#include <vector>

#include "ArrayDeque.h"
#include"ArrayStack.h"
#include "ArrayQueue.h"

#include "LinkedStack.h"
#include "LinkedQueue.h"

#include"LinkedDeque.h"



template <typename Q>
bool TestQueue() {
	Q queue;
	std::vector<int> values;
	for (std::size_t i = 0; i < 10000; i++) {
		int val = rand() % 100000;
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
//	assert(queue.is_empty());

	return true;
}


template <typename S>
bool TestStack() {
	S stack;
	std::vector<int> values;
	for (std::size_t i = 0; i < 10000; i++) {
		int val = rand() % 100000;
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
//	assert(stack.is_empty());

	return true;
}

template <typename D>
bool TestDeque() {
	D deque;
	std::vector<int> values;
	for (std::size_t i = 0; i < 10000; i++) {
		int val = rand() % 100000;
		values.push_back(val);
		deque.push_back(val);
		assert(values.size() == deque.get_size());
		assert(!deque.is_empty());

		val = rand() % 100000;
		values.insert(values.begin(), val);
		deque.push_front(val);
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());
	}


	while (!deque.is_empty()) {
		assert(values[values.size() - 1] == deque.pop_back());
		values.pop_back();
		assert(values.size() == deque.get_size());
		assert(!deque.is_empty());

		assert(values[0] == deque.pop_front());
		values.erase(values.begin());
		assert(values.size() == deque.get_size());
		assert((values.size() == 0) == deque.is_empty());
	}
//	assert(deque.is_empty());

	return true;
}

int main() {
	/*
	LinkedStack<int> stack1;
	for (std::size_t i = 0; i < 25; i++) {
		int a = rand() % 100;
		stack1.push(a);
		std::cout << a << " ";
	}
	std::cout << std::endl;
	while (!stack1.is_empty()) {
		std::cout << stack1.pop() << " ";
	}
	std::cout << std::endl << std::endl;


	ArrayQueue<int> queue1;
	for (std::size_t i = 0; i < 25; i++) {
		int a = rand() % 100;
		queue1.push(a);
		std::cout << a << " ";
	}
	std::cout << std::endl;
	while (!queue1.is_empty()) {
		std::cout << queue1.pop() << " ";
	}
	std::cout << std::endl << std::endl;

	LinkedQueue<int> queue2;
	for (std::size_t i = 0; i < 25; i++) {
		int a = rand() % 100;
		queue2.push(a);
		std::cout << a << " ";
	}
	std::cout << std::endl;
	while (!queue2.is_empty()) {
		std::cout << queue2.pop() << " ";
	}
	std::cout << std::endl << std::endl;



	std::cout << "\nDeque\n";
	ArrayDeque<int> deque1;
	for (std::size_t i = 0; i < 25; i++) {
		int a = rand() % 100;
		deque1.push_back(a);
		std::cout << a << " ";
	}
	std::cout << std::endl;
	while (!deque1.is_empty()) {
		std::cout << deque1.pop_back() << " ";
	}
	std::cout << std::endl << std::endl;

	for (std::size_t i = 0; i < 25; i++) {
		int a = rand() % 100;
		deque1.push_front(a);
		std::cout << a << " ";
	}
	std::cout << std::endl;
	while (!deque1.is_empty()) {
		std::cout << deque1.pop_front() << " ";
	}
	*/
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<int>>() << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<int>>() << std::endl;

	std::cout << "TestStack (array): " << TestStack<ArrayStack<int>>() << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<int>>() << std::endl;

	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<int>>() << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<int>>() << std::endl;
	return 0;
}

