#include "Manager.h"

using namespace ClassProject;

Manager::Manager() {
    struct node t = {"1", 1, 1, 1, 1};
    struct node f = {"0", 0, 0, 0, 0};
    uniqueTable.add(f);
    uniqueTable.add(t);
    id_nxt = 2;
}

BDD_ID Manager::createVar(const std::string &label) {
    struct node newVar = {label, id_nxt, 1, 0, id_nxt};
    uniqueTable.add(newVar);
    return id_nxt++;
}

bool Manager::isConstant(const BDD_ID f) {
    if(f == 1 || f == 0)
        return true;
    else
        return false;
}

bool Manager::isVariable(const BDD_ID x) {
    if (x > 1)
        if (topVar(x) == x)
            return true;
    return false;
}

BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
    return ite(a, b, 0);
}

BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
    return ite(a,neg(b),1);
}

BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b){
    return ite(a,0,neg(b));
}

BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
    return ite(a, 1, b);
}

BDD_ID Manager::neg(const BDD_ID a) {
    return ite(a, 0, 1);
}

BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
    return ite(a, neg(b), b);
}

BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
    if (i == 1)
        return t;
    if (i == 0)
        return e;
    node node_to_find = {"", 0, i, t, e};
    if (computedTable.find(node_to_find))
        return node_to_find.id;

    auto tV = topVar(i); //
    if (t > 1) {
        auto tV_t = topVar(t);
        tV = (tV_t < tV) ? tV_t : tV;
    }
    if (e > 1) {
        auto tV_e = topVar(e);
        tV = (tV_e < tV) ? tV_e : tV;
    }

    auto r_high = ite(coFactorTrue(i, tV), coFactorTrue(t, tV), coFactorTrue(e, tV));
    auto r_low = ite(coFactorFalse(i, tV), coFactorFalse(t, tV), coFactorFalse(e, tV));
    if (r_high == r_low)
        return r_high;

    node_to_find = {"", id_nxt, r_high, r_low, tV};
    auto found = uniqueTable.find(node_to_find);
    computedTable.add({"", node_to_find.id, i, t, e});
    if (found)
        return node_to_find.id;

    uniqueTable.add(node_to_find);
    return id_nxt++;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {
    auto tV = topVar(f);
    auto f_high = coFactorTrue(f);
    if (f <= 1 or x <= 1 or tV > x)
        return f;
    if (tV == x)
        return f_high;

    auto f_low = coFactorFalse(f);
    auto T = coFactorTrue(f_high, x);
    auto F = coFactorTrue(f_low, x);
    return ite(tV, T, F);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
    auto tV = topVar(f);
    auto f_low = coFactorFalse(f);
    if (f <= 1 or x <= 1 or tV > x)
        return f;
    if (tV == x)
        return f_low;

    auto f_high = coFactorTrue(f);
    auto T = coFactorFalse(f_high, x);
    auto F = coFactorFalse(f_low, x);
    return ite(tV, T, F);
}

std::string Manager::getTopVarName(const BDD_ID &root) {
    return uniqueTable[topVar(root)].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    if (isConstant(root))
        return;
    findNodes(coFactorTrue(root), nodes_of_root);
    findNodes(coFactorFalse(root), nodes_of_root);
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    std::set<BDD_ID> nodes;
    findNodes(root, nodes);
    for (auto & node : nodes)
        if (node > 1)
            vars_of_root.insert(topVar(node));
}
