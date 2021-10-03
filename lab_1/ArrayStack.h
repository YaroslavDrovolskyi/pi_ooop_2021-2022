#pragma once


#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

#include <cassert>

template <typename T>
class ArrayStack {
private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;

	void increase_capacity();
public:
	ArrayStack(std::size_t size_ = 10);
	ArrayStack(const ArrayStack<T>& other);
	void push(const T& item);
	T pop();
	T peek();
	bool is_empty();
	void print();
	~ArrayStack();
};

template <typename T>
ArrayStack<T>::ArrayStack(std::size_t size_) {
	assert(size_ > 0);

	this->data_ = new T[size_];
	this->capacity_ = size_;
	this->size_ = 0;
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other) {
	this->capacity_ = other.capacity_;
	this->size_ = other.size_;
	this->data_ = new T[this->capacity_];
	std::copy(other.data_, other.data_ + other.size_, this->data_);
}

template <typename T>
void ArrayStack<T>::push(const T& item) {
	if (this->size_ == this->capacity_) {
		increase_capacity();
	}
	
	this->data_[size_] = item;
	this->size_++;
}


template <typename T>
void ArrayStack<T>::increase_capacity() {
	assert(this->size_ == this->capacity_);

	T* new_memory = new T[2 * this->capacity_];
	this->capacity_ *= 2;
	std::copy(this->data_, this->data_ + this->size_, new_memory); // std::end, std::begin
	delete[]this->data_;
	this->data_ = new_memory;
}

template <typename T>
T ArrayStack<T>::pop() {
	assert(this->size_ > 0 && "Try to pop from empty stack");
	this->size_--;
	return this->data_[this->size_];
}

template <typename T>
T ArrayStack<T>::peek() {
	assert(this->size_ > 0 && "Try to peek from empty stack");
	return this->data_[this->size_ - 1];
}

template <typename T>
bool ArrayStack<T>::is_empty() {
	return this->size_ == 0;
}

template <typename T>
void ArrayStack<T>::print() {
	if (this->size_ == 0) {
		std::cout << "Stack is empty" << std::endl;
	}
	else {
		for (std::size_t i = 0; i < this->size_; i++) {
			std::cout << this->data_[i] << std::endl;
		}
	}
}


template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete[] this->data_;
}





#endif // _ARRAY_STACK_
