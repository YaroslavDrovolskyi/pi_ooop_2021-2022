#pragma once

#ifndef _TREE_PRIORITY_QUEUE_
#define _TREE_PRIORITY_QUEUE_

#include <iostream>
#include <cassert>

template <typename T>
class TreePriorityQueue {
private:
	class Node {
		public:
		std::size_t priority;
		T data;
		Node* left;
		Node* right;

		Node(std::size_t priority, const T& data, Node* left = nullptr, Node* right = nullptr) {
			this->priority = priority;
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};

	Node* root;


	void push_impl(Node*& root, std::size_t priority, const T& data);
	void remove_impl(Node* root);
	void print_impl(Node* root);
public:
	TreePriorityQueue();
	void push(std::size_t priority, const T& data);
	T pop();
	T peek();
	bool is_empty();
	void print();
	~TreePriorityQueue();
};

template <typename T>
TreePriorityQueue<T>::TreePriorityQueue() {
	this->root = nullptr;
}

template <typename T>
void TreePriorityQueue<T>::push(std::size_t priority, const T& data) {
	push_impl(this->root, priority, data);
}

template <typename T>
void TreePriorityQueue<T>::push_impl(Node*& root, std::size_t priority, const T& data) {
	if (!root) {
		root = new Node(priority, data);
	}
	else {
		if (priority <= root->priority) { // <= is for clear order when priorities is equal
			push_impl(root->left, priority, data);
		}
		else {
			push_impl(root->right, priority, data);
		}
	}
}

template <typename T>
T TreePriorityQueue<T>::pop() { /////////////////// need to
	assert(this->root && "Try to pop from empty priority queue");
	T result;
	if (!this->root->right) {
		Node* to_remove = this->root;
		result = this->root->data;
		this->root = this->root->left;
		delete to_remove;
	}
	else {
		Node* current = this->root;
		while (current->right->right) { // current->right && -- is useeless there, because this case is handled above
			current = current->right;
		}
		Node* to_remove = current->right;
		result = current->right->data;
		current->right = to_remove->left;
		delete to_remove;
	}
	return result;
}

template <typename T>
T TreePriorityQueue<T>::peek() {
	assert(this->root && "Try to peek form empty priority queue");
	Node* current = this->root;
	while (current->right) {
		current = current->right;
	}
	return current->data;
}

template <typename T>
bool TreePriorityQueue<T>::is_empty() {
	return !this->root;
}

template <typename T>
void TreePriorityQueue<T>::print_impl(Node* root) {
	if (!root) { return; }
	print_impl(root->right);
	std::cout << root->priority << "   " << root->data << std::endl;
	print_impl(root->left);
}

template <typename T>
void TreePriorityQueue<T>::print() {
	if (!this->root) {
		std::cout << "Priority queue is empty";
	}
	else {
		print_impl(this->root);
	}
	std::cout << std::endl;
}

template <typename T>
TreePriorityQueue<T>::~TreePriorityQueue() {
	remove_impl(this->root);
}

template <typename T>
void TreePriorityQueue<T>::remove_impl(Node* root) {
	if (!root) { return; }

	remove_impl(root-> left);
	remove_impl(root->right);
	delete root;
}
#endif // _TREE_PRIORITY_QUEUE_