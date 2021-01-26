//
// Created by sergey on 21.01.21.
//

#include "HashTable.h"

using namespace ClassProject;

HashTable::HashTable() {
    buffer_size = default_size;
    size = 0;
    arr = new node * [buffer_size];
    for (size_t i = 0; i < buffer_size; i++)
        arr[i] = nullptr;
}

size_t HashTable::hashFunc(BDD_ID tv, BDD_ID rh, BDD_ID rl) const {
    return (tv + rh + rl) % buffer_size;
}

bool HashTable::find(node& n) {
    size_t h = hashFunc(n.topVar, n.high, n.low);
    while (arr[h] != nullptr and (arr[h]->topVar != n.topVar
                                  or arr[h]->high != n.high or arr[h]->low != n.low)) {
        h++;
        if (h == buffer_size)
            h = 0;
    }
    if (arr[h] == nullptr)
        return false;
    n.id = arr[h]->id;
    return true;
}

void HashTable::add(const node& n) {
    if (size + 1 > (int)(rehash_size * buffer_size))
        resize();
    size_t h = hashFunc(n.topVar, n.high, n.low);
    while (arr[h] != nullptr and (arr[h]->topVar != n.topVar
                                  or arr[h]->high != n.high or arr[h]->low != n.low)) {
        h++;
        if (h == buffer_size)
            h = 0;
    }
    arr[h] = new node(n);
    if (n.id < nodes_ptr.size())
        nodes_ptr[n.id] = arr[h];
    else nodes_ptr.push_back(arr[h]);
    size++;
}

void HashTable::resize() {
    auto bufsizeOld = buffer_size;
    buffer_size *= 2;
    size = 0;
    node** arr2 = new node * [buffer_size];
    for (size_t i = 0; i < buffer_size; i++)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (size_t i = 0; i < bufsizeOld; i++)
        if (arr2[i]) {
            add(*arr2[i]);
            delete arr2[i];
        }
    delete[] arr2;
}
