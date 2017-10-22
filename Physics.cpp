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
    /*std::vector<std::vector<long>> dir;
    long d = detectionLength();
    for(long y=-d;y<=d;y++)
        for(long x = -d;x<=d;x++)
            if(x != 0 || y != 0)
                dir.push_back({x,y});*/

    auto uu = tab[y-2][x];
    auto ull = tab[y-1][x-2],ul = tab[y-1][x-1], u = tab[y-1][x], ur = tab[y-1][x+1], urr = tab[y-1][x+2];
    auto ll = tab[y][x-2],l = tab[y][x-1], r = tab[y][x+1], rr = tab[y][x+2];
    auto dl = tab[y+1][x-1], d = tab[y+1][x], dr = tab[y+1][x+1];

    if(type == sand){
        if(u.getType() == sandGenerator){
            be(sand);
        }else if((dl.is(air) && l.is(air)) ||
                (d.is(air)) ||
                (dr.is(air) && r.is(air))){
            be(air);
        }
    }else if(is(air)){
        if(u.is(sand)){
            be(sand);
        }else if(uu.is(sandGenerator)){
            be(sand);
        }else if(u.is(air)) {
            if (!l.is(air) && ul.is(sand)) {
                /*if (ul.getState() == 1 || ll.getType() != air || ull.getType() != air) {
                    type = sand;
                    state = !ul.getState();
                }*/
            } else if (!r.is(air) && ur.is(sand)) {
                /*if (ur.getState() == 0 || rr.getType() != air || urr.getType() != air) {
                    type = sand;
                    state = !ur.getState();
                }*/
            }
        }
    }
}

void Physics::show(long x, long y) {
    std::ostringstream oss;
    std::vector<int> colors = {0,8,11};
    oss << color("  ", colors[type]);
    std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << oss.str();
}

void Physics::be(Type type, int state) {
    this->type = type;
    this->state = state;
}

bool Physics::is(Type type) {
    return this->type = type;
}

bool Physics::has(int state) {
    return this->state == state;
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
