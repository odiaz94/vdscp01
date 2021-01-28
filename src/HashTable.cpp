//
// Created by sergey on 21.01.21.
//

#include "HashTable.h"

namespace ClassProject {
    bool operator==(const node& left, const node& right) {
        return (left.topVar == right.topVar) and (left.high == right.high)
               and (left.low == right.low);
    }

    bool HashTable::find(node& n) {
        auto search = table_hash.find(n);
        if (search != table_hash.end()) {
            n.id = search->id;
            return true;
        }
        return false;
    }

    void HashTable::add(const node& n) {
        table_hash.insert(n);
        table.push_back(n);
    }

    const node& HashTable::operator[](BDD_ID i) {
        return table[i];
    }
}
