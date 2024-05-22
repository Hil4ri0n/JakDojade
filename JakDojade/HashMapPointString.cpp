#include "HashMapPointString.h"

String HashMapPointString::findValueinChain(MyVector<HashNode2> chain, Point key) {
    for (int i = 0; i < chain.getSize(); i++) {
        Point pkt = chain.get(i).key;
        if (pkt.x == key.x && pkt.y == key.y) {
            return chain.get(i).value;
        }
    }
    return "";
}

unsigned int HashMapPointString::hashCode(Point key) {
    unsigned int hash;
    unsigned int hash_x = key.x;
    unsigned int hash_y = key.y;
    hash = (hash_x ^ (hash_y << 1)) % SIZE;
    return hash;
}

HashMapPointString::HashMapPointString() {
    size = 0;
}



void HashMapPointString::insertNode(Point key, String value) {
    HashNode2 node;
    node.key = key;
    node.value = value;
    array[hashCode(key)].push_back(node);
}

String HashMapPointString::get(Point key)
{
    unsigned int index = hashCode(key);
    if (array[index].getSize()) {
        return findValueinChain(array[index], key);
    }
    else {
        return "";
    }
}

int HashMapPointString::sizeofMap()
{
    return size;
}

bool HashMapPointString::isEmpty()
{
    return size == 0;
}