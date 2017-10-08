#include <iostream>
#include "Tree.hpp"

int main() {
    Tree t1(1, 1, 1, 1), t2(1, 1, 1, 1), t3(1, 1, 0, 0), t4(0, 0, 0, 0);
    Tree tt(t1, t2, t3, t4);
    Tree t = t1;
    for(int i = 0;i<12;i++){
        t = t.expend();
    }
    std::cout << t.getLevel() << std::endl;
    return 0;
}