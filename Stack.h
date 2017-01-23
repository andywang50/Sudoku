#ifndef STACK
#define STACK

#include "Node.h"
#include <cstddef>
template <typename T>
class Stack {
public:
	Stack();

	void push(const T& newData);
	T pop();

	T get_last_without_pop() const;

	~Stack();
	Stack(const Stack<T>& b);
	Stack<T>& operator = (const Stack<T>& b);
	int get_length();
private:
	int length;
	void deep_copy(const Stack<T>& b);
	Node<T>* first;
};

template <typename T>
Stack<T>::Stack() {
	first = 0;
	length = 0;
}

template <typename T>
void Stack<T>::push(const T& newData) {
	if (!(first == 0)) {
		Node<T>* newNode = new Node<T>(newData);
		newNode->next = first;
		first = newNode;
	}
	else {
		Node<T>* newNode = new Node<T>(newData);
		first = newNode;
	}
	length++;
}

template <typename T>
T Stack<T>::pop() {
	T item = T();
	if (!first == 0) {
		Node<T>* pos = first;
		item = pos->data;
		first = pos->next;
		delete pos;
		length = length - 1;

	}
	return item;
}

template <typename T>
T Stack<T>::get_last_without_pop() const {
	T item = T();

	if (!first == 0) {
		item = first->data;
	}
	return item;
}

template <typename T>
void Stack<T>::deep_copy(const Stack<T>& b) {
	first = 0;
	length = 0;
	Node<T>* previous = 0;
	Node<T>* iter = b.first;
	while (iter != 0) {
		if (length == 0) {
			Node<T>* newNode = new Node<T>(iter->data);
			first = newNode;
			previous = newNode;

		}
		else {
			Node<T>* newNode = new Node<T>(iter->data);
			previous->next = newNode;
			previous = newNode;
		}
		iter = iter->next;
		length++;
	}
	
}
template <typename T>
Stack<T>::Stack(const Stack<T>& b) {
	first = 0;
	deep_copy(b);
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& b) {
	if (this != &b) {
		this->~Stack();
		deep_copy(b);
	}
	return *this;
}

template <typename T>
Stack<T>:: ~Stack() {
	while (first != 0) pop();
}

template <typename T>
int Stack<T>::get_length() {
	return this->length;
}


#endif

