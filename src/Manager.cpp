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
    if (!isConstant(a)) {
        if (isConstant(b)) {
            if (b == 1) {
                return a;
            } else {
                return 0;
            }
        }
        else {
            BDD_ID topVar_ab;
            BDD_ID high;
            BDD_ID low=0;
            if(topVar(a)<topVar(b)) {
                topVar_ab = topVar(a);
                high=b;
            }
            else {
                topVar_ab = topVar(b);
                high=a;
            }
            for(int i=0;i<uniqueTable.size();i++){
                if(topVar_ab==uniqueTable[i].topVar && high==uniqueTable[i].high && low==uniqueTable[i].low){
                    return uniqueTable[i].id;
                }
            }
            node r = {"",id_nxt,high,low,topVar_ab};
            uniqueTable.push_back(r);
            return id_nxt++;
        }
    }
    else {
        if (a == 1) {
            return b;
        }
        else {
            return 0;
        }
    }
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
    node newNode = {"", id_nxt, high, low, tV};
    uniqueTable.push_back(newNode);
    return id_nxt++;
}
