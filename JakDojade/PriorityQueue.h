#pragma once
#include <iostream>
#include "MyVector.h"

struct Pair {
    int first, second;
};

class PriorityQueue {
public:
    PriorityQueue();

    bool empty() const;

    void push(const Pair& value);

    void pop();

    Pair top();

private:
    MyVector<Pair> heap_;
    int size_;

    int parent(int i) const;

    int leftChild(int i) const;

    int rightChild(int i) const;

    void siftUp(int i);

    void siftDown(int i);
};
