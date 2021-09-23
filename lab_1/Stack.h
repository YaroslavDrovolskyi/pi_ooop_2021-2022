#pragma once


#ifndef _STACK_
#define _STACK_

#include <cassert>

template <typename T>
class ArrayStack {
private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;

	void increase_capacity();
public:
	ArrayStack(std::size_t size = 10);
	void push(T item);
	T pop();
	T peek();
	bool is_empty();

};

template <typename T>
ArrayStack<T>::ArrayStack(std::size_t size) {
	assert(size > 0);

	this->data_ = new T[size];
	this->capacity_ = size;
	this->size_ = 0;
}


template <typename T>
void ArrayStack<T>::push(T item) {
	if (this->size_ = this->capacity_) {
		increase_capacity();
	}
	
	this->data_[this->size] = item;
	this->size_++;
}


template <typename T>
void ArrayStack<T>::increase_capacity() {
	assert(this->size_ == this->capacity);

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





#endif // _STACK_
