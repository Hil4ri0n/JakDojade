#pragma once

using namespace std;

template <typename T> class MyVector {
private:
	T* array;
	int nrOfElements;
	int capacity;
public:
	MyVector() {
		array = new T[1];
		capacity = 1;
		nrOfElements = 0;
	}
	MyVector(int size) {
		array = new T[size];
		capacity = size;
		nrOfElements = 0;
	}
	void push_back(const T& value) {
		if (nrOfElements == capacity) {
			T* temp = new T[2 * capacity];
			for (int i = 0; i < capacity; i++) {
				temp[i] = array[i];
			}
			delete[] array;
			capacity *= 2;
			array = temp;
		}
		array[nrOfElements] = value;
		nrOfElements++;
	}
	T& get(int index) {
		if (index < nrOfElements) {
			return array[index];
		}
		return array[0];
	}

	T& operator[](int index) {
		return get(index);
	}
	int getSize() {
		return nrOfElements;
	}

	void pop_back() {
		nrOfElements--;
	}
};