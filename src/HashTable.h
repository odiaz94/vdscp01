//
// Created by sergey on 21.01.21.
//

#ifndef VDSPROJECT_HASHTABLE_H
#define VDSPROJECT_HASHTABLE_H

#include "ManagerInterface.h"
#include <vector>
#include <unordered_set>

namespace ClassProject {
    /**
     * A datatype representing a BDD node
     */
    struct node {
        std::string label;
        BDD_ID id, high, low, topVar;
    };
}

namespace std
{
    template<> struct hash<ClassProject::node>
    {
        size_t operator()(ClassProject::node const& n) const noexcept
        {
            size_t h1 = std::hash<size_t>{}(n.topVar);
            size_t h2 = std::hash<size_t>{}(n.high);
            size_t h3 = std::hash<size_t>{}(n.low);
            return ((h1 ^ (h2 << 1)) << 1) ^ h3;
        }
    };
}

namespace ClassProject {
    bool operator==(const node& left, const node& right);

    class HashTable {
    private:
        std::unordered_set<node> table_hash;
        std::vector<node> table;

    public:
        bool find(node& n);

        void add(const node& n);

        const node& operator[](BDD_ID i);
    };
}

#endif //VDSPROJECT_HASHTABLE_H
