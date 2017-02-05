#ifndef DL_NODE_H
#define DL_NODE_H

template <typename T>
class Node;

template <typename T>
class Stack;

template <typename T>
class Node {
public:
	Node(const T& newData);
	friend class Stack<T>;
	Node();
private:
	T data;
	Node* next;
};

template <typename T>
Node<T>::Node(const T& newData) {
	data = newData;
	next = nullptr;
}

template <typename T>
Node<T>::Node() {
	data = NULL;
	next = nullptr;
}
#endif