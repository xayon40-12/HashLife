#include <iostream>
#include <unistd.h>
#include "Tree.hpp"
#include "Rule.hpp"

void life();
void liquid();
void rule(int n);

int main(int arc, char *argv[]) {
    if(arc>1){
        auto s = std::string(argv[1]);
        if(s == "-help" || s == "-h" || s == "h" || s == "help"){
            std::cout << "choices available:\n1: life\n2: liquid\n3: rule" << std::endl;
        }else if(s == "life" || s == "1")
            life();
        else if(s == "liquid" || s == "2")
            liquid();
        else if(s == "rule" || s == "3"){
            if(arc>2){
                rule(std::atoi(argv[2]));
            }else
                rule(-1);
        }
    }else{
        life();
    }
    return 0;
}

void rule(int n){
    long size = 24;
    std::cout << "\033[2J\033[?25l";
    bool change = (n == -1);
    if(change) n = 0;
    Tree<Rule> t = Tree<Rule>({0, n}).expend(size, {0, n}).set(0, size-1, Rule(1, n));
    for(long i = 0;;i++){
        if(i%(2*size) == 0 && change){
            n++;
            Tree<Rule>::reset();
            t = Tree<Rule>({0, n}).expend(size, {0, n}).set(0, size-1, Rule(1, n));
        }
        t.show(size);
        t = t.expend({0, n}).nextGeneration();
        //usleep(100);
    }
}

void liquid(){

}

void life(){
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

    long size = 24;
    std::cout << "\033[2J\033[?25l";
    for(long i = 0;;i++){
        if(i%250 == 0)
            t = Tree<Life>(0).expend(20).set({{0, 0, 0, 0},
                                              {0, 1, 0, 1},
                                              {0, 1, 0, 1},
                                              {0, 1, 1, 1}});

        long time = std::clock(), t1, t2;

        t.show(size);
        t1 = std::clock()-time; time = std::clock();

        t = t.expend().nextGeneration();
        t2 = std::clock()-time; time = std::clock();

        std::cout << "\033[" << 2*size-1 << ";1H";
        std::cout << "i:" << i << "   t1:" << t1 << "   t2:" << t2 << std::endl;
        //usleep(100);
    }
}