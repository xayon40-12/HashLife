//
// Created by Nathan Touroux on 07/10/2017.
//

#ifndef HASHLIFE_TREE_HPP
#define HASHLIFE_TREE_HPP

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "Hashable.hpp"
#include "Automaton.hpp"
#include "Life.hpp"

template<class A>
class Tree{
private:
    static std::unordered_set<Tree<A>> trees;
    static std::unordered_map<unsigned int, Tree<A>> memoizedEmpty;
    static std::unordered_map<Tree<A>, Tree<A>> memoizedNext;
    static std::unordered_map<Tree<A>, std::vector<std::vector<A>>> memoizedGet;

    const Tree<A> *nw, *ne, *sw, *se;
    A value;
    unsigned int level;
    long pow;//2^(level-1)

    Tree<A> center() const;
    Tree<A> Hcenter(Tree<A> const *w, const Tree<A> *e) const;
    Tree<A> Vcenter(Tree<A> const *n, Tree<A> const *s) const;

    Tree<A> set(long tabX, long tabY, Tree<A> t);

    std::vector<std::vector<A>> VConcat(std::vector<std::vector<A>> const &up, std::vector<std::vector<A>> const &down) const;
    std::vector<std::vector<A>> HConcat(std::vector<std::vector<A>> const &left, std::vector<std::vector<A>> const &right) const;
    std::vector<std::vector<A>> squareConcat(std::vector<std::vector<A>> const &ul, std::vector<std::vector<A>> const &ur,
                                             std::vector<std::vector<A>> const &dl, std::vector<std::vector<A>> const &dr) const;
public:
    Tree(A value);
    Tree(Tree<A> nw, Tree<A> ne, Tree<A> sw, Tree<A> se);
    Tree(Tree<A> const &t);
    Tree<A>& operator=(Tree<A> const &t);
    ~Tree<A>();

    bool operator==(Tree<A> const &t) const;

    A getValue() const;
    int getLevel() const;
    bool isLeaf() const;

    const Tree<A> *getNW() const;
    const Tree<A> *getNE() const;
    const Tree<A> *getSW() const;
    const Tree<A> *getSE() const;

    static Tree<A> generate(unsigned int level, const A &a = A());
    Tree<A> expend(const A &a = A());
    Tree<A> expend(unsigned long size, const A &a = A());

    std::vector<std::vector<const Tree<A>*>> getSubTrees();

    A get(long x, long y);
    std::vector<std::vector<A>> getRect(long x1, long y1, long x2, long y2);// TODO optimise using get()
    std::vector<std::vector<A>> get() const;

    Tree<A> nextGeneration();

    long getPow() const;

    void show(long x1, long y1, long x2, long y2);
    void show();
    void show(long l);

    Tree<A> set(long x, long y, A const &a, long px = 0, long py = 0);
    Tree<A> set(long x1, long y1, std::vector<std::vector<A>> tab);
    Tree<A> set(std::vector<std::vector<A>> tab);

    static void reset();
};

#include "Tree.inl"

//******************************************** MAKE HASHABLE ********************************************
MAKE_HASHABLE_T(Tree, t.getSE(), t.getSW(), t.getNE(), t.getNW(), t.getLevel(), t.getValue())

#endif //HASHLIFE_TREE_HPP
