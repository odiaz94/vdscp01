// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H

#include <vector>
#include "ManagerInterface.h"

/**
 * Namespace containing everything related to the BDD library
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
         * Unique table containing nodes being computed
         */
        std::vector<node> uniqueTable;

        /**
         * Constructor of the class initializes the instance with two nodes representing terminal cases
         */
        Manager();

        /**
         * Method creating a new variable
         * @param label - "name" of the variable
         * @return id of the node representing the created variable
         */
        BDD_ID createVar(const std::string &label) override;

        /**
         * Method True
         * @return id of the node representing the TRUE value
         */
        const BDD_ID &True() override { return uniqueTable[1].id; };

        /**
         * Method False
         * @return id of the node representing the FALSE value
         */
        const BDD_ID &False() override { return uniqueTable[0].id; };

        /**
         * Method verifies if the given node is a terminal node
         * @param f - any node
         * @return TRUE if f is a terminal node, FALSE otherwise
         */
        bool isConstant(const BDD_ID f) override;

        /**
         * Method verifies if the given node is a variable
         * @param f - any node
         * @return TRUE if f is a varuable, FALSE otherwise
         */
        bool isVariable(const BDD_ID x) override;

        /**
         * Method extracts the top variable of the input node
         * @param f - any node
         * @return id of the top variable of f
         */
        BDD_ID topVar(const BDD_ID f) override { return uniqueTable[f].topVar; };

        /**
         * Method implements the if-then-else algorithm (recursive)
         * @param i - decision node
         * @param t - output node if i is TRUE
         * @param e - output node if i is FALSE
         * @return id of the output node, if i is not a leaf node it iterates on itself
         * until it finds a leaf node, after the roll back (by then it has a hierarchical structure)
         * it checks the id of both legs of the i node for equal ids, if this happens the output is
         * replaced with the id of one of the leg nodes, otherwise it checks the uniqueTable for equal
         * nodes and replaces the output with the found node. If all these checks fail, it creates a
         * new node with the collected data and returns the id of this node.
         */
        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

        /**
         * Method extracts the high cofactor of the input node
         * with respect to the variable x
         * @param f - input node
         * @param x - variable
         * @return id of the high cofactor node
         */
        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

        /**
         * Method extracts the low cofactor of the input node
         * with respect to the variable x
         * @param f - input node
         * @param x - variable
         * @return id of the low cofactor node
         */
        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

        /**
         * Method extracts the high cofactor of the input node
         * with respect to the first variable (based on the default variable order)
         * @param f - input node
         * @return id of the high cofactor node
         */
        BDD_ID coFactorTrue(const BDD_ID f) override { return uniqueTable[f].high; };

        /**
       * Method extracts the low cofactor of the input node
       * with respect to the first variable (based on the default variable order)
       * @param f - input node
       * @return id of the low cofactor node
       */
        BDD_ID coFactorFalse(const BDD_ID f) override { return uniqueTable[f].low; };

        /**
         * Method performs an AND operation between two nodes
         * @param a - input node 1
         * @param b - input node 2
         * @return id of the output node
         */
        BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

        /**
         * Method performs an OR operation between two nodes
         * @param a - input node 1
         * @param b - input node 2
         * @return id of the output node
         */
        BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

        /**
         * Method performs an XOR operation between two nodes
         * @param a - input node 1
         * @param b - input node 2
         * @return id of the output node
         */
        BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

        /**
         * Method performs an NEG operation on one node
         * @param a - input node
         * @return id of the output node
         */
        BDD_ID neg(const BDD_ID a) override;

        /**
         * Method performs a NAND operation between two nodes
         * @param a - input node 1
         * @param b - input node 2
         * @return id of the output node
         */
        BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

        /**
         * Method performs a NOR operation between two nodes
         * @param a - input node 1
         * @param b - input node 2
         * @return id of the output node
         */
        BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

        /**
         * Method extracts the name of the top variable
         * @param root - input node
         * @return label of the top variable of the node root
         */
        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        /**
         * Method calculates the size of the uniqueTable
         * @return the current number of nodes in the uniqueTable
         */
        size_t uniqueTableSize() override { return uniqueTable.size(); };

    };

}
#endif
