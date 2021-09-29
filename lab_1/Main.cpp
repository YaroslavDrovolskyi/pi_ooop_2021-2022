#include <iostream>
#include <vector>

#include "ArrayDeque.h"
#include"ArrayStack.h"
#include "ArrayQueue.h"

#include "LinkedStack.h"
#include "LinkedQueue.h"

#include"LinkedDeque.h"

#include "ArrayPriorityQueue.h"
#include "LinkedPriorityQueue.h"

#include"Tests.h"


int main() {
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<int>, int>([]() { return generate_random(); }) << std::endl;

	std::cout << "TestStack (array): " << TestStack<ArrayStack<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<int>, int>([]() { return generate_random(); }) << std::endl;

	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<int>, int>([]() { return generate_random(); }) << std::endl;

	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<int>, int>([]() { return generate_random(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<int>, int>([]() { return generate_random(); }) << std::endl;

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

