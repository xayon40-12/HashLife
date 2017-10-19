#include <iostream>
#include <unistd.h>

#include "Tree.hpp"
#include "Rule.hpp"
#include "Wireworld.hpp"
#include "Cave.hpp"
#include "Physics.hpp"


void life();
void liquid();
void rule(int n);
void wireworld();
void cave();
void physics();

int main(int arc, char *argv[]) {
    srand(time(0));
    if(arc>1){
        auto s = std::string(argv[1]);
        if(s == "-help" || s == "-h" || s == "h" || s == "help"){
            std::cout << "choices available:\n1: life\n2: liquid\n3: rule [n]\n4: wireworld\n5: cave\n6: physics" << std::endl;
        }else if(s == "life" || s == "1")
            life();
        else if(s == "liquid" || s == "2")
            liquid();
        else if(s == "rule" || s == "3"){
            if(arc>2){
                rule(std::atoi(argv[2]));
            }else
                rule(-1);
        }else if(s == "wireworld" || s == "4")
            wireworld();
        else if(s == "cave" || s == "5")
            cave();
        else if(s == "physics" || s == "6")
            physics();
    }else{
        life();
    }
    return 0;
}

void physics(){
    long size = 24;
    std::cout << "\033[2J\033[?25l";
    Physics a(0,air), r(0,rock), s(0,sand);
    Tree<Physics> t = Tree<Physics>::generate(size).set(
            {{a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,s,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,s,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,s,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,s,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,},
             {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,}}
    );

    for(long i = 0;;i++){
        t.show(size);
        t = t.expend().nextGeneration();
        usleep(10000);
    }
}

void cave(){
    long size = 24;
    std::cout << "\033[2J\033[?25l";
    Tree<Cave> t = Tree<Cave>(0).expend(size);
    for(int y = -size;y<size;y++){
        for(int x = -size;x<size;x++){
            t = t.set(x, y, Cave(rand()%2 + 1));
        }
    }
    for(long i = 0;;i++){
        t.show(-size,size-1-i,size-1,-size-i);
        if(i%size == 0)
        for(int y = -2*size-i;y < -size-i;y++){
            for(int x = -size;x<size;x++){
                t = t.set(x, y, Cave(rand()%2 + 1));
            }
        }
        t = t.expend().nextGeneration();
        usleep(10000);
    }
}

void wireworld(){
    long size = 24;
    std::cout << "\033[2J\033[?25l";
    Tree<Wireworld> t = Tree<Wireworld>(0).expend(size).set(
            {{0,3,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
             {3,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
             {3,0,0,0,0,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0},
             {3,0,0,0,0,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0},
             {0,3,3,3,3,0,3,3,3,0,0,0,3,3,3,3,3,3,3,3,0},
             {0,0,0,3,0,0,0,3,0,3,0,0,3,3,3,3,3,3,3,3,0},
             {0,0,0,3,0,0,0,0,3,0,0,0,3,3,3,3,3,3,3,3,0},
             {0,0,0,3,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0},
             {0,0,0,3,0,0,0,0,0,0,0,0,1,3,3,3,3,3,3,3,0},
             {0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,3,0,0,3,3,3,3,3,3,3,0,0,3,0,0,0},
             {0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,0,0},
             {0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,0,0,3,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,3,3,3,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0},
             {0,3,3,1,3,0,0,0,3,0,0,0,3,3,3,3,0,0,0,0,0},
             {0,3,3,3,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0}}
    );
    for(long i = 0;;i++){
        t.show(size);
        t = t.expend().nextGeneration();
        usleep(100000);
    }
}

void rule(int n){
    long size = 24;
    std::cout << "\033[2J\033[?25l";
    bool change = (n == -1);
    if(change) n = 0;
    Tree<Rule> t = Tree<Rule>({0, n}).expend(size, {0, n}).set(0, -size, Rule(1, n));
    for(long i = 0;;i++){
        if(i%(2*size) == 0 && change){
            n++;
            Tree<Rule>::reset();
            t = Tree<Rule>({0, n}).expend(size, {0, n}).set(0, size-1, Rule(1, n));
        }
        if(change){
            t.show(size);
            std::cout << std::endl << "rule: " << n << std::endl;
        }else
            t.show(-size,size-1-i,size-1,-size-i);
        t = t.expend({0, n}).nextGeneration();
        usleep(100);
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