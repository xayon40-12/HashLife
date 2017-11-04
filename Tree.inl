//template defenition of class Tree<A> from Tree.hpp

//******************************************** PRIVATE ********************************************
template<class A> std::unordered_set<Tree<A>> Tree<A>::trees;
template<class A> std::unordered_map<unsigned int, Tree<A>> Tree<A>::memoizedEmpty;
template<class A> std::unordered_map<Tree<A>, Tree<A>> Tree<A>::momoizedNext;

template<class A> Tree<A> Tree<A>::center() const {
    return {*nw->se, *ne->sw, *sw->ne, *se->nw};
}
template<class A> Tree<A> Tree<A>::Hcenter(Tree<A> const *w, const Tree<A> *e) const {
    return {*w->ne, *e->nw, *w->se, *e->sw};
}
template<class A> Tree<A> Tree<A>::Vcenter(Tree<A> const *n, Tree<A> const *s) const {
    return {*n->sw, *n->se, *s->nw, *s->ne};
}

template<class A> Tree<A> Tree<A>::set(long tabX, long tabY, Tree<A> t) {
    if(tabY == 0){// N
        if(tabX == 0)// W
            return Tree<A>(t, *ne, *sw, *se);
        else// E
            return Tree<A>(*nw, t, *sw, *se);
    }else{// S
        if(tabX == 0)// W
            return Tree<A>(*nw, *ne, t, *se);
        else// E
            return Tree<A>(*nw, *ne, *sw, t);
    }
}

//******************************************** PUBLIC ********************************************

template<class A> Tree<A>::Tree(A value): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(value), level(0), pow(0) {

}
template<class A> Tree<A>::Tree(Tree<A> nw, Tree<A> ne, Tree<A> sw, Tree<A> se): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), value(), level(nw.level+1), pow(nw.pow==0?1:2*nw.pow)  {
    this->nw = &(*trees.insert(nw).first);
    this->ne = &(*trees.insert(ne).first);
    this->sw = &(*trees.insert(sw).first);
    this->se = &(*trees.insert(se).first);
}
template<class A> Tree<A>::Tree(Tree<A> const &t): nw(t.nw), ne(t.ne), sw(t.sw), se(t.se), value(t.value), level(t.level), pow(t.pow) {

}
template<class A> Tree<A>& Tree<A>::operator=(Tree<A> const &t) {
    nw = t.nw;
    ne = t.ne;
    sw = t.sw;
    se = t.se;
    value = t.value;
    level = t.level;
    pow = t.pow;
    return *this;
}

template<class A> Tree<A>::~Tree<A>() = default;

template<class A> bool Tree<A>::operator==(Tree<A> const &t) const {
    return (nw == t.nw &&
            ne == t.ne &&
            sw == t.sw &&
            se == t.se &&
            value == t.value &&
            level == t.level);
}

template<class A> A Tree<A>::getValue() const {
    return value;
}
template<class A> int Tree<A>::getLevel() const {
    return level;
}
template<class A> bool Tree<A>::isLeaf() const {
    return (nw == nullptr &&
            ne == nullptr &&
            sw == nullptr &&
            se == nullptr);
}

template<class A> const Tree<A> *Tree<A>::getNW() const {
    return nw;
}
template<class A> const Tree<A> *Tree<A>::getNE() const {
    return ne;
}
template<class A> const Tree<A> *Tree<A>::getSW() const {
    return sw;
}
template<class A> const Tree<A> *Tree<A>::getSE() const {
    return se;
}

template<class A> Tree<A> Tree<A>::generate(unsigned int level, const A &a) {
    auto memo = memoizedEmpty.find(level);
    if(memo != memoizedEmpty.end())
        return memo->second;

    if (level == 0) {
        return memoizedEmpty.insert({level, Tree<A>(a)}).first->second;
    } else {
        return memoizedEmpty.insert({level, {generate(level - 1, a), generate(level - 1, a), generate(level - 1, a),
                                             generate(level - 1, a)}}).first->second;
    }
}

template<class A> Tree<A> Tree<A>::expend(const A &a) {
    if(isLeaf()){
        Tree<A> e = generate(level, a);
        return Tree<A>(*this, e, e, e);
    }else{
        Tree<A> e = generate(level - 1, a);
        return Tree<A>(Tree<A>(e, e, e, *nw),
                       Tree<A>(e, e, *ne, e),
                       Tree<A>(e, *sw, e, e),
                       Tree<A>(*se, e, e, e));
    }
}

template<class A> Tree<A> Tree<A>::expend(unsigned long size, const A &a){
    if(size == 1)
        return expend(a);
    else
        return expend(size-1, a).expend(a);
}

template<class A> std::vector<std::vector<const Tree<A>*>> Tree<A>::getSubTrees() {
    return {{nw, ne},{sw, se}};
}

template<class A> A Tree<A>::get(long x, long y) {
    //   y/\
        //    |
    //–––––––––>x
    //    |
    //    |
    Tree<A> const *t(this);
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

template<class A> std::vector<std::vector<A>> Tree<A>::getRect(long x1, long y1, long x2, long y2) {
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

template<class A> std::vector<std::vector<A>> Tree<A>::get() {
    return getRect(-pow, pow-1, pow-1, -pow);
}

template<class A> Tree<A> Tree<A>::nextGeneration() {
    if(level < 2)
        return *this;//can't update

    auto memo = momoizedNext.find(*this);
    if(memo != momoizedNext.end())
        return memo->second;

    auto det = A::detectionLength();
    if(level-1 == det){

        auto tab = get();
        std::vector<std::vector<A>> tab2;
        auto p2 = pow/2;
        for(long y = p2;y<3*pow/2;y++){
            tab2.push_back(std::vector<A>());
            for(long x = pow/2;x<3*pow/2;x++){
                tab2[y-p2].push_back(tab[y][x]);
                tab2[y-p2][x-p2].update(tab, x, y);
            }
        }
        return generate(det).set(tab2);
    }else{
        Tree<A> t00 = nw->center();
        Tree<A> t01 = Hcenter(nw, ne).center();
        Tree<A> t02 = ne->center();
        Tree<A> t10 = Vcenter(nw, sw).center();
        Tree<A> t11 = center().center();
        Tree<A> t12 = Vcenter(ne, se).center();
        Tree<A> t20 = sw->center();
        Tree<A> t21 = Hcenter(sw, se).center();
        Tree<A> t22 = se->center();

        return momoizedNext.insert({*this, Tree<A>(Tree<A>(t00, t01, t10, t11).nextGeneration(),
                                                   Tree<A>(t01, t02, t11, t12).nextGeneration(),
                                                   Tree<A>(t10, t11, t20, t21).nextGeneration(),
                                                   Tree<A>(t11, t12, t21, t22).nextGeneration())}).first->second;
    }
}

template<class A> long Tree<A>::getPow() const {
    return pow;
}

template<class A> void Tree<A>::show(long x1, long y1, long x2, long y2) {
    if(x1>x2) std::swap(x1, x2);
    if(y1<y2) std::swap(y1, y2);
    auto values = getRect(x1, y1, x2, y2);
    long dx = x2 - x1, dy = y1 - y2;
    for(long y = 0;y<=dy;y++){
        for(long x = 0;x<=dx;x++){
            values[y][x].show(x, y);
        }
    }
}

template<class A> void Tree<A>::show() {
    show(-pow, pow-1, pow-1, -pow);
}
template<class A> void Tree<A>::show(long l) {
    show(-l, l-1, l-1, -l);
}

template<class A> Tree<A> Tree<A>::set(long x, long y, A const &a, long px, long py) {
    if(level == 0)
        return (getValue() == a)?*this:Tree<A>(a);
    else{
        long dx = (x >= px), dy = (y >= py);
        Tree<A> t = *getSubTrees()[!dy][dx];//!dy because y axis is upside down in the array
        return set(dx, !dy, t.set(x, y, a, px+(dx?1:-1)*t.getPow(), py+(dy?1:-1)*t.getPow()));
    }
}

template<class A> Tree<A> Tree<A>::set(long x1, long y1, std::vector<std::vector<A>> tab) {
    long dx = tab[0].size()-1, dy = tab.size()-1;
    Tree<A> t = *this;
    for(long y = 0;y<=dy;y++){
        for(long x = 0;x<=dx;x++){
            t = t.set(x1+x, y1-y, tab[y][x]);
        }
    }
    return t;
}

template<class A> Tree<A> Tree<A>::set(std::vector<std::vector<A>> tab){
    return set(-(tab[0].size()/2), tab.size()/2-1, tab);
}

template<class A> void Tree<A>::reset(){
    trees.clear();
    memoizedEmpty.clear();
    momoizedNext.clear();
}