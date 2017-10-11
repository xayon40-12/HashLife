//
// Created by Nathan Touroux on 11/10/2017.
//

#ifndef HASHLIFE_RULE_HPP
#define HASHLIFE_RULE_HPP


#include "Automaton.hpp"
#include "Hashable.hpp"

class Rule: public Automaton<Rule> {
private:
    int state;
    int rule;
public:
    Rule();
    Rule(int state, int rule);

    bool operator==(Rule const &l) const override;
    void update(std::vector<std::vector<Rule>> tab, long x, long y) override;
    void show(long x, long y) override;

    static long detectionLength();

    int getState() const;
};

MAKE_HASHABLE(Rule, t.getState())

#endif //HASHLIFE_RULE_HPP
