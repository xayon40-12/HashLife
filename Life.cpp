//
// Created by Nathan Touroux on 08/10/2017.
//

#include "Life.hpp"

Life::Life(int state): state(state) {

}

bool Life::operator==(Life const &l) const{
    return state == l.state;
}

void Life::update(std::vector<Life> tab) {
    int sum = 0;
    for(auto &l: tab){
        sum += l.state;
    }
    if(sum == 3) state = 1;
    else if(sum != 2) state = 0;
}

int Life::getState() const {
    return state;
}
