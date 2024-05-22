#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : heap_(), size_(0) {}

bool PriorityQueue::empty() const {
    return size_ == 0;
}

void PriorityQueue::push(const Pair& value) {
    heap_.push_back(value);
    size_++;
    siftUp(size_ - 1);
}

void PriorityQueue::pop() {
    if (size_ == 0) return;
    heap_.get(0) = heap_[size_ - 1];
    heap_.pop_back();
    size_--;
    siftDown(0);
}

Pair PriorityQueue::top() {
    return heap_.get(0);
}

int PriorityQueue::parent(int i) const {
    return (i - 1) / 2;
}

int PriorityQueue::leftChild(int i) const {
    return 2 * i + 1;
}

int PriorityQueue::rightChild(int i) const {
    return 2 * i + 2;
}

void PriorityQueue::siftUp(int i) {
    while (i > 0 && heap_[i].first < heap_[parent(i)].first) {
        Pair tmp = heap_[i];
        heap_[i] = heap_[parent(i)];
        heap_[parent(i)] = tmp;
        i = parent(i);
    }
}

void PriorityQueue::siftDown(int i) {
    int minIndex = i;
    int l = leftChild(i);
    if (l < size_ && heap_[l].first < heap_[minIndex].first) {
        minIndex = l;
    }
    int r = rightChild(i);
    if (r < size_ && heap_[r].first < heap_[minIndex].first) {
        minIndex = r;
    }
    if (i != minIndex) {
        std::swap(heap_[i], heap_[minIndex]);
        siftDown(minIndex);
    }
}