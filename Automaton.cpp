//
// Created by Nathan Touroux on 08/10/2017.
//

#include "Automaton.hpp"

std::string color(std::string s,int n){
    std::ostringstream oss;
    oss << "\033[48;5;" << n <<"m" << s << "\033[0m";
    return oss.str();
}