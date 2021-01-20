// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H

#include <vector>
#include "ManagerInterface.h"

/**
 * Namespace containing everything ralated to the BDD library
 */
namespace ClassProject {
    /**
     * A datatype representing a BDD node
     */
    struct node {
        std::string label;
        BDD_ID id, high, low, topVar;
    };

    bool operator==(const node& left, const node& right);

    /**
     * A class containing methods for building ROBDDs and performing operations on them
     */
    class Manager: public ManagerInterface {
    private:
        BDD_ID id_nxt;

    public:
        /**
         * A unique table containing nodes being computed
         */
        std::vector<node> uniqueTable;

        /**
         * Constructor of the class initializates the instance with two nodes representing terminal cases
         */
        Manager();

        /**
         * Method creating a new variable
         * @param label - "name" of the variable
         * @return id of a node representing the created variable
         */
        BDD_ID createVar(const std::string &label) override;

        const BDD_ID &True() override { return uniqueTable[1].id; };

        const BDD_ID &False() override { return uniqueTable[0].id; };

        bool isConstant(const BDD_ID f) override;

        bool isVariable(const BDD_ID x) override;

        BDD_ID topVar(const BDD_ID f) override { return uniqueTable[f].topVar; };

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorTrue(const BDD_ID f) override { return uniqueTable[f].high; };

        BDD_ID coFactorFalse(const BDD_ID f) override { return uniqueTable[f].low; };

        BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

        BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

        BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

        BDD_ID neg(const BDD_ID a) override;

        BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

        BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        size_t uniqueTableSize() override { return uniqueTable.size(); };

    };

}
#endif
