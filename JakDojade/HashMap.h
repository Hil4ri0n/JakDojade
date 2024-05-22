#pragma once
#include <iostream>
#include "MyVector.h"
#include "String.h"

#define SIZE 10007
using namespace std;

struct HashNode{
    String key;
    int value;
};


class HashMap {
    
private:
    MyVector<HashNode> array[SIZE];
    int size;

    int findValueinChain(MyVector<HashNode>& chain, const String& key);

        unsigned int hashCode(String key);
public:


    HashMap();

    

    void insertNode(const String& key, int value);

    int get(const String& key);

    int sizeofMap();

    bool isEmpty();
};