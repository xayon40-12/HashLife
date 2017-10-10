//
// Created by Nathan Touroux on 08/10/2017.
//

#ifndef HASHLIFE_AUTOMATON_HPP
#define HASHLIFE_AUTOMATON_HPP

#include <vector>
#include <unordered_map>

template <class A>
class Automaton {
public:
    virtual bool operator==(A const &a) const = 0;
    virtual void update(std::vector<std::vector<A>> tab, long x, long y) = 0;
    virtual std::string show() = 0;
    //static long detectionLength()  //MUST BE OVERRIDED
};


#endif //HASHLIFE_AUTOMATON_HPP
