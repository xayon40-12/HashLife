//
// Created by Nathan Touroux on 12/10/2017.
//

#include "Wireworld.hpp"
Wireworld::Wireworld(): state(0) {

}

Wireworld::Wireworld(int state): state(state) {

}

bool Wireworld::operator==(Wireworld const &l) const{
    return state == l.state;
}

void Wireworld::update(std::vector<std::vector<Wireworld>> tab, long x, long y) {
    // 0:empty 1:head 2:tail 3conductor
    if(state == 1) state = 2;
    else if(state == 2) state = 3;
    else if(state == 3){
        long sum = 0;
        std::vector<std::vector<long>> dir;
        for(long y=-1;y<=1;y++)
            for(long x = -1;x<=1;x++)
                if(x != 0 || y != 0)
                    dir.push_back({x,y});

        for(auto &p: dir){
            sum += (tab[y+p[1]][x+p[0]].state == 1);
        }
        if(sum == 1 || sum == 2) state = 1;
    }
}

void Wireworld::show(long x, long y, Window &win) {
    std::ostringstream oss;
    int colors[] = {0, 9, 14, 11};
    oss << color("  ", (colors[state]));
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Wireworld::detectionLength() {
    return 1;
}

int Wireworld::getState() const {
    return state;
}
