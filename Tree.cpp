//
// Created by Nathan Touroux on 07/10/2017.
//

#include "Tree.hpp"

std::unordered_set<Tree> Tree::trees;

Tree::Tree(int value): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(value), level(0) {

}

Tree::Tree(Tree nw, Tree ne, Tree sw, Tree se): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(0), level(nw.level+1)  {
    this->nw = &(*trees.insert(nw).first);
    this->ne = &(*trees.insert(ne).first);
    this->sw = &(*trees.insert(sw).first);
    this->se = &(*trees.insert(se).first);
}

Tree::Tree(Tree const &t): nw(t.nw), ne(t.ne), sw(t.sw), se(t.se), value(t.value), level(t.level) {

}

Tree& Tree::operator=(Tree const &t){
    nw = t.nw;
    ne = t.ne;
    sw = t.sw;
    se = t.se;
    value = t.value;
    level = t.level;
}

Tree::~Tree() {

}

bool Tree::operator==(Tree const &t) const{
    return (nw == t.nw &&
            ne == t.ne &&
            sw == t.sw &&
            se == t.se &&
            value == t.value &&
            level == t.level);
}

int Tree::getValue() const{
    return value;
}

int Tree::getLevel() const{
    return level;
}

bool Tree::isLeaf() const{
    return (nw == nullptr &&
            ne == nullptr &&
            sw == nullptr &&
            se == nullptr);
}

const Tree * Tree::getNW() const{
    return nw;
}

const Tree * Tree::getNE() const {
    return ne;
}

const Tree * Tree::getSW() const {
    return sw;
}

const Tree * Tree::getSE() const {
    return se;
}


Tree Tree::generateEmpty(unsigned int level) {
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

Tree Tree::expend() {
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
