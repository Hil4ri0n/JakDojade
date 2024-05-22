#pragma once
using namespace std;

template <typename T> class QNode {

public:
	T value;
	QNode<T>* next;
	QNode<T>* previous;
	QNode() {
		next = nullptr;
		previous = nullptr;
	}
	QNode(T newValue) {
		value = newValue;
		next = nullptr;
		previous = nullptr;
	}
};