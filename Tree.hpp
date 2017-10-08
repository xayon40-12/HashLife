//
// Created by Nathan Touroux on 07/10/2017.
//

#ifndef HASHLIFE_TREE_HPP
#define HASHLIFE_TREE_HPP

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "Hashable.hpp"
#include "Automaton.hpp"
#include "Life.hpp"

template<class A>
//typename std::enable_if<std::is_base_of<Automaton, A>::value, void>
class Tree {
private:
    static std::unordered_set<Tree<A>> trees;

    const Tree *nw, *ne, *sw, *se;
    A value;
    int level;

    Tree center() const{
        return {nw->se, ne->sw, sw->ne, se->nw};
    }
    Tree Hcenter(Tree const *w, const Tree *e) const{
        return {w->ne, e->nw, w->se, e->sw};
    }
    Tree Vcenter(Tree const *n, Tree const *s) const{
        return {n->sw, n->se, s->nw, s->ne};
    }

public:
    Tree(A value): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(value), level(0) {

    }
    Tree(Tree nw, Tree ne, Tree sw, Tree se): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(0), level(nw.level+1)  {
        this->nw = &(*trees.insert(nw).first);
        this->ne = &(*trees.insert(ne).first);
        this->sw = &(*trees.insert(sw).first);
        this->se = &(*trees.insert(se).first);
    }
    Tree(Tree const &t): nw(t.nw), ne(t.ne), sw(t.sw), se(t.se), value(t.value), level(t.level) {

    }
    Tree& operator=(Tree const &t){
        nw = t.nw;
        ne = t.ne;
        sw = t.sw;
        se = t.se;
        value = t.value;
        level = t.level;
        return *this;
    }
    ~Tree() {

    }

    bool operator==(Tree const &t) const{
        return (nw == t.nw &&
                ne == t.ne &&
                sw == t.sw &&
                se == t.se &&
                value == t.value &&
                level == t.level);
    }

    A getValue() const{
        return value;
    }
    int getLevel() const{
        return level;
    }
    bool isLeaf() const{
        return (nw == nullptr &&
                ne == nullptr &&
                sw == nullptr &&
                se == nullptr);
    }

    const Tree *getNW() const{
        return nw;
    }
    const Tree *getNE() const {
        return ne;
    }
    const Tree *getSW() const {
        return sw;
    }
    const Tree *getSE() const {
        return se;
    }

    static Tree generateEmpty(unsigned int level) {
        static std::unordered_map<unsigned int, Tree> memoizedEmpty;
        auto memo = memoizedEmpty.find(level);
        if(memo != memoizedEmpty.end())
            return memo->second;

        if (level == 0) {
            return memoizedEmpty.insert({level, Tree(0)}).first->second;
        } else {
            return memoizedEmpty.insert({level, {generateEmpty(level - 1), generateEmpty(level - 1), generateEmpty(level - 1),
                                                 generateEmpty(level - 1)}}).first->second;
        }
    }

    Tree expend() {
        Tree e = generateEmpty(level-1);
        if(isLeaf()){
            return Tree(*this, e, e, e);
        }else{
            return Tree(Tree(e, e, e, *nw),
                        Tree(e, e, *ne, e),
                        Tree(e, *sw, e, e),
                        Tree(*se, e, e, e));
        }
    }

    std::vector<A> getRect(int x1, int y1, int x2, int y2){
        //TODO
    }

    Tree nextGeneration() const{
        static std::unordered_map<Tree, Tree> momoizedNext;
        auto memo = momoizedNext.find(*this);
        if(memo != momoizedNext.end())
            return memo->second;

        if(level == 2){
            //TODO life.update(tab)
            //TODO return centered updated tree
        }else{
            Tree t00 = nw->center();
            Tree t01 = Hcenter(nw, ne).center();
            Tree t02 = ne->center();
            Tree t10 = Vcenter(nw, sw).center();
            Tree t11 = center().center();
            Tree t12 = Vcenter(ne, se).center();
            Tree t20 = sw->center();
            Tree t21 = Hcenter(sw, se).center();
            Tree t22 = se->center();

            return momoizedNext.insert({*this, Tree(Tree(t00, t01, t10, t11).nextGeneration(),
                                                    Tree(t01, t02, t11, t12).nextGeneration(),
                                                    Tree(t10, t11, t20, t21).nextGeneration(),
                                                    Tree(t11, t12, t21, t22).nextGeneration())}).first->second;
        }
    }
};

template<class A>
std::unordered_set<Tree<A>> Tree<A>::trees;

MAKE_HASHABLE_T(Tree, t.getSE(), t.getSW(), t.getNE(), t.getNW(), t.getLevel(), t.getValue())

#endif //HASHLIFE_TREE_HPP
