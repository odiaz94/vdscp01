#include <cassert>

#include "Manager.h"

using namespace ClassProject;

bool ClassProject::operator==(const node &left, const node &right) {
    return (left.label == right.label) and (left.id == right.id) and
           (left.high == right.high) and (left.low == right.low) and
           (left.topVar == right.topVar);
}

Manager::Manager() {
    struct node t = {"1", 1};
    struct node f = {"0", 0};
    uniqueTable.push_back(f);
    uniqueTable.push_back(t);
    id_nxt = 2;
}

BDD_ID Manager::createVar(const std::string &label) {
    struct node newVar = {label, id_nxt, 1, 0, id_nxt};
    uniqueTable.push_back(newVar);
    return id_nxt++;
}

bool Manager::isConstant(const BDD_ID f) {
    if(f == 1 || f == 0)
        return true;
    else
        return false;
}

bool Manager::isVariable(const BDD_ID x) {}

BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b)  {
    /*if (a == 0 or b == 0)
        return 0;
    if (a == 1)
        return b;
    if (b == 1)
        return a;
    auto tV = (a < b) ? a : b;
    auto high = (a < b) ? b : a;
    BDD_ID low = 0;
    for (auto & node : uniqueTable) {
        if (node.topVar == tV and node.low == low and node.high == high)
            return node.id;
    }
    std::string label = uniqueTable[a].label + " and " + uniqueTable[b].label;
    node newNode = {label, id_nxt, high, low, tV};
    uniqueTable.push_back(newNode);
    return id_nxt++;*/
    return ite(a, b, 0);
}

BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
    if (a == 1 or b == 1)
        return 1;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    auto tV = (a < b) ? a : b;
    BDD_ID high = 1;
    BDD_ID low = (a < b) ? b : a;
    for (auto & node : uniqueTable) {
        if (node.topVar == tV and node.low == low and node.high == high)
            return node.id;
    }
    std::string label = uniqueTable[a].label + " or " + uniqueTable[b].label;
    node newNode = {label, id_nxt, high, low, tV};
    uniqueTable.push_back(newNode);
    return id_nxt++;
}

BDD_ID Manager::neg(const BDD_ID a) {
    if (a == 1 or a == 0)
        return not a;
    auto tV = topVar(a);
    auto low = coFactorFalse(a);
    auto high = coFactorTrue(a);
    for (auto & node : uniqueTable)
        if (node.topVar == tV and node.low == high and node.high == low)
            return node.id;

    node newNode = {"not " + uniqueTable[a].label, id_nxt, low, high, tV};
    uniqueTable.push_back(newNode);
    return id_nxt++;
}

BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
    if (a == b)
        return 0;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == 1 xor b == 1) {
        auto var = (a > b) ? a : b;
        return neg(var);
    }
    BDD_ID tV, high, low;
    if (a < b) {
        tV = a;
        high = neg(b);
        low = b;
    } else {
        tV = b;
        high = neg(a);
        low = a;
    }
    for (auto & node : uniqueTable)
        if (node.topVar == tV and node.low == low and node.high == high)
            return node.id;

    std::string label = uniqueTable[a].label + " xor " + uniqueTable[b].label;
    node newNode = {label, id_nxt, high, low, tV};
    uniqueTable.push_back(newNode);
    return id_nxt++;
}

BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
    if (i == 1)
        return t;
    if (i == 0)
        return e;

    auto tV = topVar(i);
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

    for (auto & node : uniqueTable)
        if (node.topVar == tV and node.low == r_low and node.high == r_high)
            return node.id;

    node newNode = {"", id_nxt, r_high, r_low, tV};
    uniqueTable.push_back(newNode);
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
