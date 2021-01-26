//
// Created by sergey on 21.01.21.
//

#ifndef VDSPROJECT_HASHTABLE_H
#define VDSPROJECT_HASHTABLE_H

#include "ManagerInterface.h"
#include <vector>

namespace ClassProject {
    /**
     * A datatype representing a BDD node
     */
    struct node {
        std::string label;
        BDD_ID id, high, low, topVar;
    };

    bool operator==(const node& left, const node& right);

    class HashTable {
    private:
        node** arr;
        const size_t default_size = 10;
        size_t size;
        size_t buffer_size;
        const double rehash_size = 0.75;
        std::vector<node*> nodes_ptr;

    public:
        HashTable();

        const node* operator[] (size_t i) {
            return nodes_ptr[i];
        }

        size_t hashFunc(BDD_ID tv, BDD_ID rh, BDD_ID rl) const;

        bool find(node& n);

        void add(const node& n);

        void resize();
    };
}

#endif //VDSPROJECT_HASHTABLE_H
