#pragma once
#include "QNode.h"
using namespace std;

template <typename T> class Queue {
private:
	int size;
	QNode<T>* head;
	QNode<T>* tail;

	T* getElement(size_t index) {
		if (index > size) return nullptr;
		QNode<T>* pointer = nullptr;
		if (index > size / 2) {
			pointer = tail;
			for (int i = size; i > index; i--) {
				pointer = pointer->previous;
			}
		}
		else {
			pointer = head;
			for (int i = 1; i < index; i++) {
				pointer = pointer->next;
			}
		}
		return &(pointer->value);
	}

	void removeNode(QNode<T>* pointer) {
		if (head == pointer) {
			head = pointer->next;
		}
		if (tail == pointer) {
			tail = pointer->previous;
		}
		if (pointer->previous != nullptr) {
			pointer->previous->next = pointer->next;
		}
		if (pointer->next != nullptr) {
			pointer->next->previous = pointer->previous;
		}
		delete pointer;
		size--;
	}
public:

	Queue() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	~Queue() {
		while (head != nullptr) {
			QNode<T>* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	/*void push_front(T object) {
		QNode<T>* tmp;
		tmp = new DL_Node<T>;
		tmp->value = object;
		tmp->next = head;
		tmp->previous = nullptr;
		if (head != nullptr) {
			head->previous = tmp;
		}
		head = tmp;
		if (tail == nullptr) tail = tmp;
		size++;
	}*/
	void enqueue(const T& object) {
		QNode<T>* tmp;
		tmp = new QNode<T>;
		tmp->value = object;
		tmp->previous = tail;
		tmp->next = nullptr;
		if (tail != nullptr) {
			tail->next = tmp;
		}
		tail = tmp;
		if (head == nullptr) head = tmp;
		size++;
	}
	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	T dequeue() {
		T returnValue = *getElement(0);
		removeNode(head);
		return returnValue;
	}
};