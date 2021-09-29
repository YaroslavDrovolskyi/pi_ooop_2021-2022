#pragma once

#ifndef _LINKEDDEQUE_
#define _LINKEDDEQUE_

#include <iostream>
#include <cassert>


template <typename T>
class LinkedDeque {
private:
	class Node {
	public:
		T data;
		Node* prev;
		Node* next;

		Node(T data, Node* prev = nullptr, Node* next = nullptr) {
			this->data = data;
			this->prev = prev;
			this->next = next;
		}
	};

	Node* begin;
	Node* end;
	std::size_t size_;


public:
	LinkedDeque();
	void push_back(T data);
	T pop_back();
	void push_front(T data);
	T pop_front();
	std::size_t get_size();
	bool is_empty();
	~LinkedDeque();

};

template <typename T>
LinkedDeque<T>::LinkedDeque() {
	this->begin = this->end = nullptr;
	this->size_ = 0;
}

template <typename T>
void LinkedDeque<T>::push_back(T data) {
	Node* new_node = new Node(data, this->end);
	if (this->end) {
		this->end->next = new_node;
	}
	else { // deque is empty
		this->begin = new_node;
	}
	this->end = new_node;
	this->size_++;
}

template <typename T>
T LinkedDeque<T>::pop_back() {
	assert(this->size_ > 0 && "Try to pop from empty deque");

	Node* to_remove = this->end; 
	T result = to_remove->data;
	if (this->end->prev) {
		this->end->prev->next = nullptr;
	}
	else { // it was only 1 item in deque
		this->begin = nullptr;
	}
	this->end = this->end->prev;

	
	delete to_remove;
	this->size_--;
	return result;
}

template <typename T>
void LinkedDeque<T>::push_front(T data) {
	Node* new_node = new Node(data, nullptr, this->begin);
	if (this->begin) {
		this->begin->prev = new_node;
	}
	else { // deque is empty
		this->end = new_node;
	}
	this->begin = new_node;
	this->size_++;
}

template <typename T>
T LinkedDeque<T>::pop_front() {
	assert(this->size_ > 0 && "Try to pop from empty deque");

	Node* to_remove = this->begin;
	T result = this->begin->data;
	if (this->begin->next) {
		this->begin->next->prev = nullptr;
	}
	else { // 1 item in deque
		this->end = nullptr;
	}
	this->begin = this->begin->next;

	delete to_remove;
	this->size_--;
	return result;
}

template <typename T>
std::size_t LinkedDeque<T>::get_size() {
	return this->size_;
}

template <typename T>
bool LinkedDeque<T>::is_empty() {
	return this->size_ == 0;
}

template <typename T>
LinkedDeque<T>::~LinkedDeque() {
	while (this->begin) {
		Node* current = this->begin;
		this->begin = this->begin->next;
		delete current;
	}
	this->end = nullptr;
}


#endif // _LINKEDDEQUE_
