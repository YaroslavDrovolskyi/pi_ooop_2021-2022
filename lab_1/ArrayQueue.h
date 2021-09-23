#pragma once


#ifndef _ARRAYQUEUE_
#define _ARRAYQUEUE_

template <typename T>
class ArrayQueue {
private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;

	void increase_capacity();

public:
	ArrayQueue(std::size_t size = 10);
	void push(T item);
	T pop();
	std::size_t get_size();
	bool is_empty();
	~ArrayQueue();
};


#endif // _ARRAYQUEUE_

template <typename T>
ArrayQueue<T>::ArrayQueue(std::size_t size) {
	assert(size > 0);

	this->data_ = new T[size];
	this->capacity_ = size;
	this->size_ = 0;
}

template <typename T>
void ArrayQueue<T>::push(T item) {
	if (this->size_ == this->capacity_) {
		increase_capacity();
	}

	this->data_[size_] = item;
	this->size_++;
}

template <typename T>
void ArrayQueue<T>::increase_capacity() {
	assert(this->size_ == this->capacity_);

	T* new_memory = new T[2 * this->capacity_];
	this->capacity_ *= 2;
	std::copy(this->data_, this->data_ + this->size_, new_memory); // std::end, std::begin
	delete[]this->data_;
	this->data_ = new_memory;
}

template <typename T>
T ArrayQueue<T>::pop() {
	assert(this->size_ > 0 && "Try to pop from empty queue");

	T result = this->data_[0];
	for (std::size_t i = 0; i < size_ - 1; i++) {
		this->data_[i] = this->data_[i + 1];
	}
	this->size_--;
	return result;
}

template <typename T>
std::size_t ArrayQueue<T>::get_size() {
	return this->size_;
}

template <typename T>
bool ArrayQueue<T>::is_empty() {
	return this->size_ == 0;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete[] this->data_;
}