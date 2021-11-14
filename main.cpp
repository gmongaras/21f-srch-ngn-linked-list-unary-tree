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
#include "DocumentProcessor.h"


int main(int argc, char** argv) {
    AVLTree<int> t;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    t.insert(a);
    t.insert(b);
    t.insert(c);
    t.insert(d);
    t.insert(e);
    t.insert(f);
    t.printTree();

    DocumentProcessor p;
    p.processDocuments(argv[1]);



    if(argc == 1) {

        runCatchTests();
        return 0;
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
