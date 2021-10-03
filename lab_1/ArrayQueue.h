#pragma once


#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

template <typename T>
class ArrayQueue {
private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;

	void increase_capacity();

public:
	ArrayQueue(std::size_t size_ = 10);
	ArrayQueue(const ArrayQueue<T>& other);
	void push(const T& item);
	T pop();
	std::size_t get_size();
	bool is_empty();
	void print();
	~ArrayQueue();
};



template <typename T>
ArrayQueue<T>::ArrayQueue(std::size_t size_) {
	assert(size_ > 0);

	this->data_ = new T[size_];
	this->capacity_ = size_;
	this->size_ = 0;
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& other) {
	this->capacity_ = other.capacity_;
	this->size_ = other.size_;
	this->data_ = new T[this->capacity_];
	std::copy(other.data_, other.data_ + other.size_, this->data_);
}

template <typename T>
void ArrayQueue<T>::push(const T& item) {
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
void ArrayQueue<T>::print() {
	if (this->size_ == 0) {
		std::cout << "Queue is empty" << std::endl;
	}
	else {
		for (std::size_t i = 0; i < this->size_; i++) {
			std::cout << this->data_[i] << std::endl;
		}
	}
}
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete[] this->data_;
}




#endif // _ARRAY_QUEUE_
