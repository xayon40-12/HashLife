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

    auto t = Tree<Life>(0).expend(40).set(-2, 1, {{0, 0, 0, 0},
                                                  {0, 1, 0, 1},
                                                  {0, 1, 0, 1},
                                                  {0, 1, 1, 1}});

    long size = 30;
    std::cout << "\033[2J";
    for(long i = 0;;i++){
        if(i%250 == 0)
            t = Tree<Life>(0).expend(20).set({{0, 0, 0, 0},
                                              {0, 1, 0, 1},
                                              {0, 1, 0, 1},
                                              {0, 1, 1, 1}});
        std::cout << "\033[1;1H";
        long time = std::clock(), t1, t2;

        t.show(size);
        t1 = std::clock()-time; time = std::clock();

        t = t.expend().nextGeneration();
        t2 = std::clock()-time; time = std::clock();

        std::cout << "\033[" << 2*size-1 << ";1H";
        std::cout << "i:" << i << "   t1:" << t1 << "   t2:" << t2 << std::endl;
        //usleep(100);
    }

    return 0;
}