//
// Created by Nathan Touroux on 07/10/2017.
//

#ifndef HASHLIFE_TREE_HPP
#define HASHLIFE_TREE_HPP

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "Hashable.hpp"


class Tree {
private:
    static std::unordered_set<Tree> trees;

    const Tree *nw, *ne, *sw, *se;
    int value;
    int level;

public:
    Tree(int value);
    Tree(Tree nw, Tree ne, Tree sw, Tree se);
    Tree(Tree const &t);
    Tree& operator=(Tree const &t);
    ~Tree();

    bool operator==(Tree const &t) const;

    int getValue() const;
    int getLevel() const;
    bool isLeaf() const;

    Tree const *getNW() const;
    Tree const *getNE() const;
    Tree const *getSW() const;
    Tree const *getSE() const;

    static Tree generateEmpty(unsigned int level);

    Tree expend();
};

MAKE_HASHABLE(Tree, t.getSE(), t.getSW(), t.getNE(), t.getNW(), t.getLevel(), t.getValue())

#endif //HASHLIFE_TREE_HPP
