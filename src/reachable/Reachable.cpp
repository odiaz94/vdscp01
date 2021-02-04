//
// Created by ludwig on 27.11.18.
//

#include "Reachable.h"

using namespace ClassProject;

Reachable::Reachable(unsigned int stateSize) : ReachableInterface(stateSize) {
    this->stateSize = stateSize;
    for (unsigned int i = 0; i < stateSize; i++) {
        state_bits.push_back(createVar("s" + std::to_string(i)));
        next_state_bits.push_back(createVar("s" + std::to_string(i) + "`"));
    }
}

BDD_ID Reachable::xnor2(BDD_ID a, BDD_ID b) {
    return ite(a, b, neg(b));
}

const std::vector<BDD_ID> &Reachable::getStates() const {
    return state_bits;
}

void Reachable::setDelta(const std::vector<BDD_ID> &transitionFunctions) {
    delta = transitionFunctions;
    reachable_set = False();
}

void Reachable::setInitState(const std::vector<bool> &stateVector) {
    c_init = True();
    for (unsigned int i = 0; i < stateSize; i++)
        if (stateVector[i])
            c_init = and2(c_init, xnor2(state_bits[i], True()));
        else c_init = and2(c_init, xnor2(state_bits[i], False()));
    reachable_set = False();
}

BDD_ID Reachable::compute_reachable_states() {
    BDD_ID theta = True();
    for (unsigned int i = 0; i < stateSize; i++) {
        theta = and2(theta, or2(and2(next_state_bits[i], delta[i]),
                                and2(neg(next_state_bits[i]), neg(delta[i]))));
    }
    auto c_R1 = c_init;
    BDD_ID c_R;
    do {
        c_R = c_R1;
        auto imgS = and2(c_R, theta);
        for (unsigned int i = 0; i < stateSize; i++)
            imgS = or2(coFactorTrue(imgS, state_bits[i]), coFactorFalse(imgS, state_bits[i]));
        for (unsigned int i = 0; i < stateSize; i++)
            imgS = and2(imgS, xnor2(state_bits[i], next_state_bits[i]));
        for (unsigned int i = 0; i < stateSize; i++)
            imgS = or2(coFactorTrue(imgS, next_state_bits[i]),
                        coFactorFalse(imgS, next_state_bits[i]));
        c_R1 = or2(c_R, imgS);
    } while (c_R != c_R1);
    return c_R;
}

bool Reachable::is_reachable(const std::vector<bool> &stateVector) {
    if (reachable_set == False())
        reachable_set = compute_reachable_states();

    auto c_state = True();
    for (unsigned int i = 0; i < stateSize; i++)
        if (stateVector[i])
            c_state = and2(c_state, xnor2(state_bits[i], True()));
        else c_state = and2(c_state, xnor2(state_bits[i], False()));

    if (reachable_set == or2(reachable_set, c_state))
        return true;
    return false;
}
