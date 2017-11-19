//
// Created by Nathan Touroux on 28/10/2017.
//

#ifndef HASHLIFE_GRIFFEATH_HPP
#define HASHLIFE_GRIFFEATH_HPP

#include "Automaton.hpp"
#include "Hashable.hpp"
#include "Tree.hpp"

class Griffeath: public Automaton<Griffeath> {
private:
    int state;
public:
    Griffeath();
    Griffeath(int state);

    bool operator==(Griffeath const &l) const override;
    void update(std::vector<std::vector<Griffeath>> tab, long x, long y) override;
    void show(long x, long y, Window &win) override;

    static long detectionLength();

    int getState() const;
};

MAKE_HASHABLE(Griffeath, t.getState())

#endif //HASHLIFE_GRIFFEATH_HPP
