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

    const Tree *nw, *ne, *sw, *se;
    A value;
    unsigned int level;
    long pow;//2^(level-1)

    Tree center() const {
        return {*nw->se, *ne->sw, *sw->ne, *se->nw};
    }
    Tree Hcenter(Tree const *w, const Tree *e) const {
        return {*w->ne, *e->nw, *w->se, *e->sw};
    }
    Tree Vcenter(Tree const *n, Tree const *s) const {
        return {*n->sw, *n->se, *s->nw, *s->ne};
    }

public:
    Tree(A value): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(value), level(0), pow(0) {

    }
    Tree(Tree<A> nw, Tree ne, Tree sw, Tree se): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(0), level(nw.level+1), pow(nw.pow==0?1:2*nw.pow)  {
        this->nw = &(*trees.insert(nw).first);
        this->ne = &(*trees.insert(ne).first);
        this->sw = &(*trees.insert(sw).first);
        this->se = &(*trees.insert(se).first);
    }
    Tree(Tree const &t): nw(t.nw), ne(t.ne), sw(t.sw), se(t.se), value(t.value), level(t.level), pow(t.pow) {

    }
    Tree& operator=(Tree const &t) {
        nw = t.nw;
        ne = t.ne;
        sw = t.sw;
        se = t.se;
        value = t.value;
        level = t.level;
        pow = t.pow;
        return *this;
    }
    ~Tree() = default;

    bool operator==(Tree const &t) const {
        return (nw == t.nw &&
                ne == t.ne &&
                sw == t.sw &&
                se == t.se &&
                value == t.value &&
                level == t.level);
    }

    A getValue() const {
        return value;
    }
    int getLevel() const {
        return level;
    }
    bool isLeaf() const {
        return (nw == nullptr &&
                ne == nullptr &&
                sw == nullptr &&
                se == nullptr);
    }

    const Tree *getNW() const {
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
        if(isLeaf()){
            Tree e = generateEmpty(level);
            return Tree(*this, e, e, e);
        }else{
            Tree e = generateEmpty(level-1);
            return Tree(Tree(e, e, e, *nw),
                        Tree(e, e, *ne, e),
                        Tree(e, *sw, e, e),
                        Tree(*se, e, e, e));
        }
    }

    Tree expend(unsigned long size){
        if(size == 1)
            return expend();
        else
            return expend(size-1).expend();
    }

    std::vector<std::vector<const Tree*>> getSubTrees() const{
        return {{nw, ne},{sw, se}};
    }

    A get(long x, long y) const{
        //   y/\
        //    |
        //–––––––––>x
        //    |
        //    |
        Tree const *t(this);
        long px = 0, py = 0;
        long pow = getPow();
        while(t->getLevel() != 0){
            pow /= 2;
            if(x >= px && y >= py){
                t = t->getNE();
                px += pow;
                py += pow;
            } else if(x >= px && y < py){
                t = t->getSE();
                px += pow;
                py -= pow;
            } else if(x < px && y >= py){
                t = t->getNW();
                px -= pow;
                py += pow;
            } else if(x < px && y < py){
                t = t->getSW();
                px -= pow;
                py -= pow;
            }
        }
        return t->getValue();
    }

    std::vector<std::vector<A>> getRect(long x1, long y1, long x2, long y2) const{
        std::vector<std::vector<A>> values;
        if(x1>x2) std::swap(x1, x2);
        if(y1<y2) std::swap(y1, y2);
        long dx = x2 - x1, dy = y1 - y2;
        for(long y = 0;y<=dy;y++){
            values.push_back(std::vector<A>());
            for(long x = 0;x<=dx;x++){
                values[y].push_back(get(x1+x, y1-y));
            }
        }
        return values;
    }

    std::vector<std::vector<A>> get() const{
        return getRect(-pow, pow-1, pow-1, -pow);
    }

    Tree nextGeneration() const{
        if(level < 2)
            return *this;//can't update

        static std::unordered_map<Tree, Tree> momoizedNext;
        auto memo = momoizedNext.find(*this);
        if(memo != momoizedNext.end())
            return memo->second;

        if(level == 2){

            auto tab = get(), tab2 = tab;
            for(long y = 1;y<=2;y++){
                for(long x = 1;x<=2;x++){
                    tab[y][x].update(tab2, x, y);
                }
            }
            return Tree(tab[1][1],tab[1][2],tab[2][1],tab[2][2]);
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

    long getPow() const {
        return pow;
    }

    void show(long x1, long y1, long x2, long y2) {
        if(x1>x2) std::swap(x1, x2);
        if(y1<y2) std::swap(y1, y2);
        auto values = getRect(x1, y1, x2, y2);
        long dx = x2 - x1, dy = y1 - y2;
        std::ostringstream os;
        for(long y = 0;y<=dy;y++){
            for(long x = 0;x<=dx;x++){
                os << values[y][x].show();
            }
            os << std::endl;
        }
        std::cout << os.str();
    }

    void show() {
        show(-pow, pow-1, pow-1, -pow);
    }
    void show(long l) {
        show(-l, l-1, l-1, -l);
    }

    const Tree* set(long tabX, long tabY, const Tree *t) const {
        if(tabY == 0){// N
            if(tabX == 0)// W
                return &(*trees.insert(Tree(*t, *ne, *sw, *se)).first);
            else// E
                return &(*trees.insert(Tree(*nw, *t, *sw, *se)).first);
        }else{// S
            if(tabX == 0)// W
                return &(*trees.insert(Tree(*nw, *ne, *t, *se)).first);
            else// E
                return &(*trees.insert(Tree(*nw, *ne, *sw, *t)).first);
        }
    }

    const Tree* set(long x, long y, A const &a, long px = 0, long py = 0) const {
        if(level == 0)
            return (getValue() == a)?this:&(*trees.insert(Tree(a)).first);
        else{
            long dx = (x >= px), dy = (y >= py);
            Tree t = *getSubTrees()[!dy][dx];//!dy because y axis is upside down in the array
            return set(dx, !dy, t.set(x, y, a, px+(dx?1:-1)*t.getPow(), py+(dy?1:-1)*t.getPow()));
        }
    }

    Tree set(long x1, long y1, long x2, long y2, std::vector<std::vector<A>> tab) {
        if(x1>x2) std::swap(x1, x2);
        if(y1<y2) std::swap(y1, y2);
        long dx = x2 - x1, dy = y1 - y2;
        const Tree *t = this;
        for(long y = 0;y<=dy;y++){
            for(long x = 0;x<=dx;x++){
                t = t->set(x1+x, y1-y, tab[y][x]);
            }
        }
        return *t;
    }
};

template<class A>
std::unordered_set<Tree<A>> Tree<A>::trees;

MAKE_HASHABLE_T(Tree, t.getSE(), t.getSW(), t.getNE(), t.getNW(), t.getLevel(), t.getValue())

#endif //HASHLIFE_TREE_HPP
