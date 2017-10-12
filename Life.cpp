//
// Created by Nathan Touroux on 08/10/2017.
//

#include <sstream>
#include "Life.hpp"

Life::Life(): state(0) {

}

Life::Life(int state): state(state) {

}

bool Life::operator==(Life const &l) const{
    return state == l.state;
}

void Life::update(std::vector<std::vector<Life>> tab, long x, long y) {
    long sum = 0;
    std::vector<std::vector<long>> dir;
    for(long y=-1;y<=1;y++)
        for(long x = -1;x<=1;x++)
            if(x != 0 || y != 0)
                dir.push_back({x,y});

    for(auto &p: dir){
        sum += tab[y+p[1]][x+p[0]].state;
    }
    if(sum == 3) state = 1;
    else if(sum != 2) state = 0;
}

void Life::show(long x, long y) {
    std::ostringstream oss;
    oss << (state==1?color("  ", 10):"  ");
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Life::detectionLength() {
    return 1;
}

int Life::getState() const {
    return state;
}

