//
// Created by Nathan Touroux on 08/10/2017.
//

#ifndef HASHLIFE_LIFE_HPP
#define HASHLIFE_LIFE_HPP


#include "Automaton.hpp"
#include "Hashable.hpp"
#include "Tree.hpp"

class Life: public Automaton<Life> {
private:
    int state;
public:
    Life(int state);

    bool operator==(Life const &l) const override;
    void update(std::vector<std::vector<Life>> tab, long x, long y) override;
    void show(long x, long y) override;

    static long detectionLength();

    int getState() const;
};

MAKE_HASHABLE(Life, t.getState())

#endif //HASHLIFE_LIFE_HPP
