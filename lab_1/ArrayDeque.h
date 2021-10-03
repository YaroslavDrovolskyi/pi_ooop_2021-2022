#pragma once

#ifndef _ARRAY_DEQUE_
#define _ARRAY_DEQUE_

#include <cassert>


template <typename T>
class ArrayDeque {
private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;

	void increase_capacity();

public:
	ArrayDeque(std::size_t size_ = 10);
	ArrayDeque(const ArrayDeque<T>& other);
	void push_back(const T& data);
	T pop_front();
	void push_front(const T& data);
	T pop_back();
	std::size_t get_size();
	bool is_empty();
	void print();
	~ArrayDeque();
};

template <typename T>
ArrayDeque<T>::ArrayDeque(std::size_t size_) {
	assert(size_ > 0);

	this->data_ = new T[size_];
	this->capacity_ = size_;
	this->size_ = 0;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(const ArrayDeque<T>& other) {
	this->capacity_ = other.capacity_;
	this->size_ = other.size_;
	this->data_ = new T[this->capacity_];
	std::copy(other.data_, other.data_ + other.size_, this->data_);
}

template <typename T>
void ArrayDeque<T>::increase_capacity() {
	assert(this->size_ == this->capacity_);

	T* new_memory = new T[2 * this->capacity_];
	this->capacity_ *= 2;
	std::copy(this->data_, this->data_ + this->size_, new_memory); // std::end, std::begin
	delete[]this->data_;
	this->data_ = new_memory;
}

template <typename T>
void ArrayDeque<T>::push_back(const T& data) {
	if (this->size_ == this->capacity_) {
		increase_capacity();
	}

	this->data_[size_] = data;
	this->size_++;
}

template <typename T>
T ArrayDeque<T>::pop_front() {
	assert(this->size_ > 0 && "Try to pop from empty deque");

	T result = this->data_[0];
	for (std::size_t i = 0; i < size_ - 1; i++) {
		this->data_[i] = this->data_[i + 1];
	}
	this->size_--;
	return result;
}

template <typename T>
void ArrayDeque<T>::push_front(const T& data) {
	if (this->size_ == this->capacity_) {
		increase_capacity();
	}

	for (std::size_t i = this->size_; i > 0; i--) {
		this->data_[i] = this->data_[i - 1];
	}
	this->data_[0] = data;
	this->size_++;
}

template <typename T>
T ArrayDeque<T>::pop_back() {
	assert(this->size_ > 0 && "Try to pop from empty deque");

	this->size_--;
	return this->data_[size_];
}

template <typename T>
std::size_t ArrayDeque<T>::get_size() {
	return this->size_;
}

template <typename T>
bool ArrayDeque<T>::is_empty() {
	return this->size_ == 0;
}

template <typename T>
void ArrayDeque<T>::print() {
	if (this->size_ == 0) {
		std::cout << "Deque is empty" << std::endl;
	}
	else {
		for (std::size_t i = 0; i < this->size_; i++) {
			std::cout << this->data_[i] << std::endl;
		}
	}
}

template <typename T>
ArrayDeque<T>::~ArrayDeque() {
	delete[] this->data_;
}



#endif // _ARRAY_DEQUE_
