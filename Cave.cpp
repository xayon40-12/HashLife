//
// Created by Nathan Touroux on 15/10/2017.
//

#include "Cave.hpp"

Cave::Cave(): state(0) {

}

Cave::Cave(int state): state(state) {

}

bool Cave::operator==(Cave const &l) const{
    return state == l.state;
}

void Cave::update(std::vector<std::vector<Cave>> tab, long x, long y) {
    long sum1 = 0, sum2 = 0;
    std::vector<std::vector<long>> dir;
    for(long y=-1;y<=1;y++)
        for(long x = -1;x<=1;x++)
            if(x != 0 || y != 0)
                dir.push_back({x,y});

    for(auto &p: dir){
        sum1 += (tab[y+p[1]][x+p[0]].state == 1);
        sum2 += (tab[y+p[1]][x+p[0]].state == 2);
    }
    if(sum1 > sum2) state = 1;
    else if(sum2 > sum1) state = 2;
}

void Cave::show(long x, long y, Window &win) {
    std::ostringstream oss;
    std::vector<int> colors = {0,10,11};
    oss << color("  ", colors[state]);
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Cave::detectionLength() {
    return 1;
}

int Cave::getState() const {
    return state;
}
