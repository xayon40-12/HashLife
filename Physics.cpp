//
// Created by Nathan Touroux on 19/10/2017.
//

#include <iostream>
#include "Physics.hpp"

#include "Physics.hpp"

Physics::Physics(): state(0), type(air) {

}

Physics::Physics(int state, Type type): state(state), type(type) {

}

bool Physics::operator==(Physics const &l) const{
    return state == l.state && type == l.type;
}

void Physics::update(std::vector<std::vector<Physics>> tab, long x, long y) {
    std::vector<std::vector<long>> dir;
    long d = detectionLength();
    for(long y=-d;y<=d;y++)
        for(long x = -d;x<=d;x++)
            if(x != 0 || y != 0)
                dir.push_back({x,y});

    if(type == sand){
        if(tab[y+1][x].getType() == air){type = air; state = 0;}
    }else if(type == air){
        if(tab[y-1][x].getType() == sand){type = sand; state = !tab[y-1][x].getState();}
    }
}

void Physics::show(long x, long y) {
    std::ostringstream oss;
    std::vector<int> colors = {0,8,11};
    oss << color("  ", colors[type]);
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

long Physics::detectionLength() {
    return 2;
}

int Physics::getState() const {
    return state;
}

Type Physics::getType() const {
    return type;
}
