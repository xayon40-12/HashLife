//
// Created by Nathan Touroux on 15/10/2017.
//

#ifndef HASHLIFE_CAVE_HPP
#define HASHLIFE_CAVE_HPP

#include "Automaton.hpp"
#include "Hashable.hpp"
#include "Tree.hpp"

class Cave: public Automaton<Cave> {
private:
    int state;
public:
    Cave();
    Cave(int state);

    bool operator==(Cave const &l) const override;
    void update(std::vector<std::vector<Cave>> tab, long x, long y) override;
    void show(long x, long y) override;

    static long detectionLength();

    int getState() const;
};

MAKE_HASHABLE(Cave, t.getState())

#endif //HASHLIFE_CAVE_HPP
