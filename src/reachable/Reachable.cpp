//
// Created by ludwig on 27.11.18.
//

#include "Reachable.h"

using namespace ClassProject;

Reachable::Reachable(unsigned int stateSize) : ReachableInterface(stateSize) {}

BDD_ID Reachable::xnor2(BDD_ID a, BDD_ID b) {}

const std::vector<BDD_ID> &Reachable::getStates() const {}

void Reachable::setDelta(const std::vector<BDD_ID> &transitionFunctions) {}

void Reachable::setInitState(const std::vector<bool> &stateVector) {}

BDD_ID Reachable::compute_reachable_states() {}

bool Reachable::is_reachable(const std::vector<bool> &stateVector) {}
