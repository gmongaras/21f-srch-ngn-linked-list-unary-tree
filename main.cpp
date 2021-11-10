#include <iostream>



/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "AVLTree.h"


int main(int argc, char** argv) {
    AVLTree<int> t;
    int a = 1;
    int b = 3;
    int c = -1;
    t.insert(a);
    t.insert(b);
    t.insert(c);
    t.printTree();
    AVLTree<int> t2(t);
    int d = 10;
    int e = 2;
    t2.insert(d);
    t2.insert(e);
    t2.printTree();

    int w;
    std::cin >> w;
    if(argc == 1) {

        runCatchTests();
        return 0;
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
