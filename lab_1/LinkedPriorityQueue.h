#pragma once

#ifndef _LINKED_PRIORITY_QUEUE_
#define _LINKED_PRIORITY_QUEUE_

#include <iostream>
#include <cassert>

template <typename T>
class LinkedPriorityQueue {
private:
	class Node {
	public:
		std::size_t priority;
		T data;
		Node* next;

		Node(std::size_t priority, const T& data, Node* next = nullptr) {
			this->priority = priority;
			this->data = data;
			this->next = next;
		}
	};

	Node* begin;
	std::size_t size;

public:
	LinkedPriorityQueue();
	LinkedPriorityQueue(const LinkedPriorityQueue<T>& other);
	void push(std::size_t priority, const T& data);
	T pop();
	T peek();
	bool is_empty();
	void print();
	~LinkedPriorityQueue();
};

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue() {
	this->begin = nullptr;
	this->size = 0;
}

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue(const LinkedPriorityQueue<T>& other) {
	this->size = other.size;
	if (!other.begin) {
		this->begin = nullptr;
	}
	else {
		this->begin = new Node(other.begin->priority, other.begin->data);
		Node* current_new = this->begin;
		Node* current = other.begin->next;
		while (current) {
			current_new->next = new Node(current->priority, current->data);
			current_new = current_new->next;
			current = current->next;
		}
	}
}

template <typename T>
void LinkedPriorityQueue<T>::push(std::size_t priority, const T& data) {
	Node* new_node = new Node(priority, data);

	if (!this->begin) {
		this->begin = new_node;
	}
	else if (priority > this->begin->priority) {
		new_node->next = this->begin;
		this->begin = new_node;
	}
	else {
		Node* current = this->begin;
		while (current->next && priority <= current->next->priority) {
			current = current->next;
		}
		// insert new_node after current
		new_node->next = current->next;
		current->next = new_node;
	}
	this->size++;
}

template <typename T>
T LinkedPriorityQueue<T>::pop() {
	assert(this->size > 0 && "Try to pop from empy priority queue");

	T result = this->begin->data;
	Node* to_delete = this->begin;
	this->begin = this->begin->next;
	delete to_delete;
	this->size--;
	return result;
}

template <typename T>
T LinkedPriorityQueue<T>::peek() {
	assert(this->size > 0 && "Try to peek from empy priority queue");
	return this->begin->data;
} 

template <typename T>
bool LinkedPriorityQueue<T>::is_empty() {
	return this->size == 0;
}

template <typename T>
void LinkedPriorityQueue<T>::print() {
	if (!this->begin) {
		std::cout << "Priority queue is empty";
	}
	else {
		Node* current = this->begin;
		while (current) {
			std::cout << current->priority << "   " << current->data << std::endl;
			current = current->next;
		}
	}
	std::cout << std::endl;
}

template <typename T>
LinkedPriorityQueue<T>::~LinkedPriorityQueue() {
	while (this->begin) {
		Node* current = this->begin;
		this->begin = this->begin->next;
		delete current;
	}
}


#endif // _LINKED_PRIORITY_QUEUE_