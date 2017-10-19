//
// Created by Nathan Touroux on 19/10/2017.
//

#ifndef HASHLIFE_PHYSICS_HPP
#define HASHLIFE_PHYSICS_HPP


#include "Automaton.hpp"
#include "Hashable.hpp"

enum Type {air, rock};

class Physics: public Automaton<Physics> {
private:
    int state;
    Type type;
public:
    Physics();
    Physics(int state, Type type);

    bool operator==(Physics const &l) const override;
    void update(std::vector<std::vector<Physics>> tab, long x, long y) override;
    void show(long x, long y) override;

    static long detectionLength();

    int getState() const;
    Type getType() const;
};

MAKE_HASHABLE(Physics, t.getState(), (int)t.getType())


#endif //HASHLIFE_PHYSICS_HPP
