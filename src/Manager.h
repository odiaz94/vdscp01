// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include "ManagerInterface.h"

namespace ClassProject {

    struct node {
        std::string label;
        BDD_ID id, high, low, topVar;
    };

    bool operator==(const node& left, const node& right) {
        return (left.label == right.label) and (left.id == right.id) and
                (left.high == right.high) and (left.low == right.low) and
                (left.topVar == right.topVar);
    };

    class Manager: ManagerInterface {

    private:
        BDD_ID id_nxt;

    public:
        std::vector<node> uniqueTable;

        Manager() {
            struct node t = {"1", 1};
            struct node f = {"0", 0};
            uniqueTable.push_back(f);
            uniqueTable.push_back(t);
        }

        BDD_ID createVar(const std::string &label) override {};

        const BDD_ID &True() override { return uniqueTable[1].id; };

        const BDD_ID &False() override { return uniqueTable[0].id; };

        bool isConstant(const BDD_ID f) override {};

        bool isVariable(const BDD_ID x) override {};

        BDD_ID topVar(const BDD_ID f) override {};

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override {};

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override {};

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override {};

        BDD_ID coFactorTrue(const BDD_ID f) override {};

        BDD_ID coFactorFalse(const BDD_ID f) override {};

        BDD_ID and2(const BDD_ID a, const BDD_ID b) override {};

        BDD_ID or2(const BDD_ID a, const BDD_ID b) override {};

        BDD_ID xor2(const BDD_ID a, const BDD_ID b) override {};

        BDD_ID neg(const BDD_ID a) override {};

        BDD_ID nand2(const BDD_ID a, const BDD_ID b) override {};

        BDD_ID nor2(const BDD_ID a, const BDD_ID b) override {};

        std::string getTopVarName(const BDD_ID &root) override {};

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override {};

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override {};

        size_t uniqueTableSize() override {};

    };

}
#endif
