//
// Created by Nathan Touroux on 28/10/2017.
//

#include "Griffeath.hpp"

Griffeath::Griffeath(): state(0) {

}

Griffeath::Griffeath(int state): state(state) {

}

bool Griffeath::operator==(Griffeath const &l) const{
    return state == l.state;
}

void Griffeath::update(std::vector<std::vector<Griffeath>> tab, long x, long y) {
    if(state == 0) return;

    long sum = 0, next = (state)%4+1;
    std::vector<std::vector<long>> dir;
    for(long y=-1;y<=1;y++)
        for(long x = -1;x<=1;x++)
            if(x != 0 || y != 0)
                dir.push_back({x,y});

    for(auto &p: dir){
        sum += (tab[y+p[1]][x+p[0]].state == next);
    }
    if(sum >= 3) state = next;
}

void Griffeath::show(long x, long y) {
    std::ostringstream oss;
    std::vector<int> colors = {0,11,214,202,9};
    oss << color("  ", colors[state]);
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Griffeath::detectionLength() {
    return 1;
}

int Griffeath::getState() const {
    return state;
}
