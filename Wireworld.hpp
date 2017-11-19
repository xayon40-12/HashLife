//
// Created by Nathan Touroux on 12/10/2017.
//

#ifndef HASHLIFE_WIREWORLD_HPP
#define HASHLIFE_WIREWORLD_HPP

#include "Automaton.hpp"
#include "Hashable.hpp"
#include "Tree.hpp"

class Wireworld: public Automaton<Wireworld> {
private:
    int state;// 0:empty 1:head 2:tail 3conductor
public:
    Wireworld();
    Wireworld(int state);

    bool operator==(Wireworld const &l) const override;
    void update(std::vector<std::vector<Wireworld>> tab, long x, long y) override;
    void show(long x, long y, Window &win) override;

    static long detectionLength();

    int getState() const;
};

MAKE_HASHABLE(Wireworld, t.getState())

#endif //HASHLIFE_WIREWORLD_HPP
