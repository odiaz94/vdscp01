//
// Created by ludwig on 27.11.18.
//

#ifndef VDSPROJECT_IMGCOMP_H
#define VDSPROJECT_IMGCOMP_H


#include <map>
#include "ReachableInterface.h"

namespace ClassProject {

    class Reachable : public ReachableInterface {
    private:
        unsigned int stateSize;
        std::vector<BDD_ID> state_bits;
        std::vector<BDD_ID> next_state_bits;
        std::vector<BDD_ID> delta;
        BDD_ID c_init;
        BDD_ID reachable_set;

    public:
        explicit Reachable(unsigned int stateSize);

        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

        const std::vector<BDD_ID> &getStates() const override;

        void setDelta(const std::vector<BDD_ID> &transitionFunctions) override;

        void setInitState(const std::vector<bool> &stateVector) override;

        BDD_ID compute_reachable_states() override;

        bool is_reachable(const std::vector<bool> &stateVector) override;
    };

}
#endif //VDSPROJECT_IMGCOMP_H
