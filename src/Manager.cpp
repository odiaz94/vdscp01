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
    if(!isConstant(a)){
        if(isConstant(b)){
            if(b == 0){return 1;}
            else{return !a;}
        }
        else{
            BDD_ID tV, high, low=0;
            if(topVar(a)<topVar(b)) {
                tV = topVar(a);
                high=b;}
            else {
                tV = topVar(b);
                high=a;}
            for(int i=0;i<uniqueTable.size();i++){
                if(tV==uniqueTable[i].topVar && high==uniqueTable[i].high && low==uniqueTable[i].low){
                    return uniqueTable[i].id;}
            }
            node r = {"",id_nxt,high,low,tV};
            uniqueTable.push_back(r);
            return id_nxt++;
        }
    }
    else{
        if(a == 0){return 1;}
        else{return !b;}
    }
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

std::string Manager::getTopVarName(const BDD_ID &root) {
    return uniqueTable[topVar(root)].label;
}
