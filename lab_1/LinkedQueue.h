#pragma once

#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <cassert>

template <typename T>
class LinkedQueue {
private:

	class Node {
	public:
		T data;
		Node* next;

		Node(const T& data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
	};

	Node* begin_;
	Node* end_;
	std::size_t size_;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>& other);
	void push(const T& data);
	T pop();
	std::size_t get_size();
	bool is_empty();
	void print();
	~LinkedQueue();
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
	this->begin_ = nullptr;
	this->end_ = nullptr;
	this->size_ = 0;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other) {
	this->size_ = other.size_;
	if (!other.begin_) {
		this->begin_ = this->end_ = nullptr;
	}
	else {
		this->end_ = this->begin_ = new Node(other.begin_->data);
		Node* current = other.begin_->next;
		while (current) {
			this->end_->next = new Node(current->data);
			this->end_ = this->end_->next;
			current = current->next;
		}
	}
}

template <typename T>
void LinkedQueue<T>::push(const T& data) {
	Node* new_node = new Node(data);
	if (!this->begin_) { // queue is empty
		this->begin_ = new_node;
	}
	else {
		this->end_->next = new_node;
	}
	this->end_ = new_node;

	this->size_++;
}

template <typename T>
T LinkedQueue<T>::pop() {
	assert(this->begin_ && "Try to pop from empty queue");

	T result = this->begin_->data;
	Node* to_delete = this->begin_;
	this->begin_ = this->begin_->next;

	if (!this->begin_) {
		this->end_ = nullptr; // because queue is empty after pop
	}

	delete to_delete;
	this->size_--;
	return result;
}

template <typename T>
std::size_t LinkedQueue<T>::get_size() {
	return this->size_;
}

template <typename T>
bool LinkedQueue<T>::is_empty() {
	return !this->begin_;
}

template <typename T>
void LinkedQueue<T>::print() {
	if (!this->begin_) {
		std::cout << "Queue is empty\n";
	}
	else {
		Node* current = this->begin_;
		while (current) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
	Node* to_delete = this->begin_;
	while (to_delete) {
		this->begin_ = this->begin_->next;
		delete to_delete;
		to_delete = this->begin_;
	}
	this->end_ = nullptr;
}

#endif // _LINKED_QUEUE_
