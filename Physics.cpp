//
// Created by Nathan Touroux on 19/10/2017.
//

#include <iostream>
#include <ncurses.h>
#include "Physics.hpp"

#include "Physics.hpp"

Physics::Physics(): state(0), type(air) {

}

Physics::Physics(Type type, int state): state(state), type(type) {

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

    if(is(sand)){
        if(d.is(air) || (has(right) && dr.is(air) && r.is(air)) || (has(left) && dl.is(air) && l.is(air))){
            be(air);
        }else{
            state = !state;
        }
    }else if(is(sandGenerator)){
        state = !state;
    }else if(is(air)){
        if(u.is(sand) || uu.is(sandGenerator)){
            be(sand, !u.state);
        }else if(u.is(air)){
            if(ul.is(sand,right) && !l.is(air)){
                be(sand, left);
            }
            if(ur.is(sand,left) && !r.is(air)){
                be(sand, right);
            }
        }
    }
}

void Physics::show(long x, long y, Window &win) {
    if(type == 0) return;
    std::vector<Colour> colors = {Colour::black(),Colour::gray(),Colour::yellow(), Colour::green()};
    long w = 3;
    win.setColour(colors[type]);
    win.fillRect(x*w, y*w, w, w);
    //std::cout << "\033[" << y+1 << ";" << 2*x+1 << "H" << color("  ", colors[type]);
}

void Physics::be(Type type, int state) {
    this->type = type;
    this->state = state;
}

bool Physics::is(Type type) {
    return this->type == type;
}

bool Physics::is(Type type, int state) {
    return this->type == type && this->state == state;
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
