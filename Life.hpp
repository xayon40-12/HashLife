//
// Created by Nathan Touroux on 08/10/2017.
//

#ifndef HASHLIFE_LIFE_HPP
#define HASHLIFE_LIFE_HPP


#include "Automaton.hpp"
#include "Hashable.hpp"

class Life: public Automaton {
private:
    int state;
public:
    Life(int state);

    bool operator==(Life const &l) const;
    void update(std::vector<Life> tab);

    int getState() const;
};

MAKE_HASHABLE(Life, t.getState())

#endif //HASHLIFE_LIFE_HPP
