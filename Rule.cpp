//
// Created by Nathan Touroux on 11/10/2017.
//

#include "Rule.hpp"
#include <iostream>
#include <sstream>

Rule::Rule(): state(0), rule(0) {

}

Rule::Rule(int state, int rule): state(state), rule(rule) {

}

bool Rule::operator==(Rule const &l) const{
    return state == l.state;
}

void Rule::update(std::vector<std::vector<Rule>> tab, long x, long y) {
    if(!state)
        state = (rule & (1<<(tab[y-1][x-1].getState()<<2 | tab[y-1][x].getState()<<1 | tab[y-1][x+1].getState())))?1:0;
}

void Rule::show(long x, long y) {
    std::ostringstream oss;
    oss << (state==1?color("  ",15):"  ");
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Rule::detectionLength() {
    return 1;
}

int Rule::getState() const {
    return state;
}
