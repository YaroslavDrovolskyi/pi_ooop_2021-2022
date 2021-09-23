#include <iostream>

#include"ArrayStack.h"
#include "LinkedStack.h"

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
	std::cout << std::endl;


	return 0;
}