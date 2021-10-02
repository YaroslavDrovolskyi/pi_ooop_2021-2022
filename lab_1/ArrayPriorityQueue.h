#pragma once


#ifndef _ARRAY_PRIORITY_QUEUE_
#define _ARRAY_PRIORITY_QUEUE_

#include <iostream>
#include <cassert>

template <typename T>
class ArrayPriorityQueue {
private:
	class Node {
	public:
		std::size_t priority;
		T data;

		Node() {};
		Node(std::size_t priority, const T& data) {
			this->priority = priority;
			this->data = data;
		}
	};


	Node* data_;
	std::size_t size_;
	std::size_t capacity_;
	
	void increase_capacity();
public:
	ArrayPriorityQueue(std::size_t size = 10);
	void push(std::size_t priority, const T& data);
	T pop();
	T peek();
	bool is_empty();
	~ArrayPriorityQueue();

	void print(); // for testing
};

template <typename T>
ArrayPriorityQueue<T>::ArrayPriorityQueue(std::size_t size) {
	assert(size > 0);

	this->data_ = new Node[size];
	this->capacity_ = 10;
	this->size_ = 0;
}

template<typename T>
void ArrayPriorityQueue<T>::push(std::size_t priority, const T& data) {
	if (this->size_ == this->capacity_) {
		increase_capacity();
	}

	// search place to insert
	std::size_t position = 0;
	while (position < this->size_ && priority <= this->data_[position].priority) { // less items -> further
		position++;
	}
	// shift other items
	for (std::size_t i = this->size_; i > position; i--) {
		this->data_[i] = this->data_[i - 1];
	}

	this->data_[position] = Node(priority, data);
	this->size_++;
}

template <typename T>
void ArrayPriorityQueue<T>::increase_capacity() {
	assert(this->size_ == this->capacity_);

	Node* new_memory = new Node [2 * this->capacity_];
	this->capacity_ *= 2;
	std::copy(this->data_, this->data_ + this->size_, new_memory);
	delete[] this->data_;
	this->data_ = new_memory;
}

template <typename T>
T ArrayPriorityQueue<T>::pop() {
	assert(this->size_ > 0 && "Try to pop from empty priority queue");

	T result = this->data_[0].data;
	// shift other items
	for (std::size_t i = 0; i < this->size_ - 1; i++) {
		this->data_[i] = this->data_[i + 1];
	}
	this->size_--;
	return result;
}


template <typename T>
T ArrayPriorityQueue<T>::peek() {
	assert(this->size_ >=0 && "Try to peek from empty priority queue");

	return this->data_[0].data;
}

template <typename T>
bool ArrayPriorityQueue<T>::is_empty() {
	return this->size_ == 0;
}

template <typename T>
ArrayPriorityQueue<T>::~ArrayPriorityQueue() {
	delete[] this->data_;
}

template <typename T>
void ArrayPriorityQueue<T>::print() {
//	std::cout << "\n\n\nsize = " << this->size_ << "   caapcity = " << this->capacity_ << std::endl;
	if (this->size_ == 0) {
		std::cout << "Priority queue is empty";
	}
	else {
		for (size_t i = 0; i < this->size_; i++) {
			std::cout << this->data_[i].priority << "   " << this->data_[i].data << std::endl;
		}
	}
	std::cout << std::endl;
}




#endif // _ARRAY_PRIORITY_QUEUE_