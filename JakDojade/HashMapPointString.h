#pragma once
#include <iostream>
#include "MyVector.h"
#include "String.h"

#define SIZE 10007
using namespace std;

struct Point {
    int x, y;
};

struct HashNode2 {
    Point key;
    String value;
};


class HashMapPointString {

private:
    MyVector<HashNode2> array[SIZE];
    int size;

    String findValueinChain(MyVector<HashNode2> chain, Point key);

    unsigned int hashCode(Point key);
public:


    HashMapPointString();



    void insertNode(Point key, String value);

    String get(Point key);

    int sizeofMap();

    bool isEmpty();
};