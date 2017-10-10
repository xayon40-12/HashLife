#include <iostream>
#include <unistd.h>
#include "Tree.hpp"

int main() {
    /*Life l0(0), l1(1);
    Tree<Life> t1(l0, l1, l0, l1), t2(l0, l1, l0, l1), t3(l0, l1, l0, l0), t4(l1, l1, l0, l0);
    Tree<Life> tt(t1, t2, t3, t4);
    Tree<Life> t = tt;
    for(int i = 0;i<32;i++){
        t = t.expend();
    }*/

    auto t = Tree<Life>(0).expend(43).set(-2, 1, 1, -2, {{0, 0, 0, 0},
                                                         {0, 1, 0, 1},
                                                         {0, 1, 0, 1},
                                                         {0, 1, 1, 1}});

    std::cout << "\033[2J";
    for(;;){
        std::cout << "\033[1;1H";
        t.show(30);
        t = t.expend().nextGeneration();
        usleep(10*1000);
    }

    return 0;
}