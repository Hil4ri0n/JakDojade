#include "HashMap.h"

int HashMap::findValueinChain(MyVector<HashNode>& chain, const String& key) {
    for (int i = 0; i < chain.getSize(); i++) {
        if (chain.get(i).key == key) {
            return chain.get(i).value;
        }
    }
    return -1;
}

unsigned int HashMap::hashCode(String key)
{
    /*unsigned int hash = 0;

    for (int i = 0; i < key.size(); i++) {
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    }

    return hash % SIZE;*/
    unsigned int hash = 2166136261u; // FNV offset basis
    int i = 0;
    while (key[i] != '\0') {
        hash = (hash * 16777619u) ^ (unsigned int)key[i];
        i++;
    }
    return hash % SIZE;
}

HashMap::HashMap() {
    size = 0;
}



void HashMap::insertNode(const String& key, int value) {
    HashNode node;
    node.key = key;
    node.value = value;
    array[hashCode(key)].push_back(node);
}

int HashMap::get(const String& key)
{
    unsigned int index = hashCode(key);
    if (array[index].getSize()) {
        return findValueinChain(array[index], key);
    }
    else {
        return -1;
    }
}

int HashMap::sizeofMap()
{
    return size;
}

bool HashMap::isEmpty()
{
    return size == 0;
}