#include <iostream>

#include "ArrayDeque.h"
#include"ArrayStack.h"
#include "ArrayQueue.h"

#include "LinkedStack.h"
#include "LinkedQueue.h"



int main() {
	
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

	return 0;
}