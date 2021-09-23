#pragma once

#ifndef _LINKEDSTACK_
#define _LINKEDSTACK_

#include <cassert>

template <typename T>
class LinkedStack {
private:

	class Node {
	public:
		T data;
		Node* next;

		Node(T data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
	};

	Node* top;

public:
	LinkedStack();
	void push(T data);
	T pop();
	T peek();
	bool is_empty();
	~LinkedStack();
};


template <typename T>
LinkedStack<T>::LinkedStack() {
	this->top = nullptr;
}

template <typename T>
void LinkedStack<T>::push(T data) {
	Node* new_node = new Node(data, this->top);
	this->top = new_node;
}

template <typename T>
T LinkedStack<T>::pop() {
	assert(this->top && "Try to pop from empty stack");

	T result = this->top->data;
	Node* to_delete = this->top;
	this->top = this->top->next;
	delete to_delete;

	return result;
}

template <typename T>
T LinkedStack<T>::peek() {
	assert(this->top && "Try to peek from empty stack");

	return this->top->data;
}

template <typename T>
bool LinkedStack<T>::is_empty() {
	return !this->top;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
	Node* to_delete = this->top;
	while (to_delete) {
		this->top = this->top->next;
		delete to_delete;
		to_delete = this->top;
	}
	std::cout << "Destructor for LinkedStack\n";
}

#endif // _LINKEDSTACK_