#pragma once

#ifndef _LINKEDQUEUE_
#define _LINKEDQUEUE_

#include <cassert>

template <typename T>
class LinkedQueue {
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

	Node* begin_;
	Node* end_;
	std::size_t size_;

public:
	LinkedQueue();
	void push(T data);
	T pop();
	std::size_t get_size();
	bool is_empty();
	~LinkedQueue();
};

template <typename T>
LinkedQueue<T>::LinkedQueue() {
	this->begin_ = nullptr;
	this->end_ = nullptr;
	this->size_ = 0;
}

template <typename T>
void LinkedQueue<T>::push(T data) {
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
LinkedQueue<T>::~LinkedQueue() {
	Node* to_delete = this->begin_;
	while (to_delete) {
		this->begin_ = this->begin_->next;
		delete to_delete;
		to_delete = this->begin_;
	}
}

#endif // _LINKEDQUEUE_
