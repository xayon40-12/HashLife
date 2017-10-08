#include <iostream>
#include "Tree.hpp"

int main() {
    Life l0(0), l1(1);
    Tree<Life> t1(l1, l1, l1, l0), t2(l1, l1, l0, l1), t3(l1, l1, l0, l0), t4(l1, l0, l0, l0);
    Tree<Life> tt(t1, t2, t3, t4);
    Tree<Life> t = tt;
    for(int i = 0;i<12;i++){
        t = t.expend();
    }

    long size = 2;
    for(long y = size-1;y>=-size;y--){
        for(long x = -size;x<size;x++){
            std::cout << tt.get(x, y).getState();
        }
        std::cout << std::endl;
    }
    return 0;
}