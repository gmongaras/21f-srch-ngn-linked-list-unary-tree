#include <iostream>



/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "DocumentProcessor.cpp"
#include "catch_setup.h"
#include "AVLTree.h"
#include <vector>


int main(int argc, char** argv) {
    //runCatchTests();
    //return 0;
    // If there are no command line arguments, run the catch tests
    if(argc == 1) {
        runCatchTests();
        return 0;
    }



//    AVLTree<int> t;
//    int a = 1;
//    int b = 2;
//    int c = 3;
//    int d = 4;
//    int e = 5;
//    int f = 6;
//    t.insert(a);
//    t.insert(b);
//    t.insert(c);
//    t.insert(d);
//    t.insert(e);
//    t.insert(f);
//    t.printTree();

    // Process the documents from the given input file
    DocumentProcessor p;
    p.processDocuments(argv[1]);


    // Try to find a result given the query
    WordNode results;
    try {
        results = p.search(std::string(argv[2]));
    } catch (std::logic_error& e) {
        // If a result wasn't found, display an error message
        std::cout << "No results for query" << std::endl;
        return 0;
    } catch (std::runtime_error& e) {
        // If a result wasn't found, display an error message
        std::cout << "No results for query" << std::endl;
        return 0;
    }

    // If a result was found, display it
    std::cout << "Results: " << std::endl;
    std::cout << results;
//    for (int i = 0; i < vec.size(); i++) {
//        std::cout << vec[i] << std::endl;
//    }



    //std::cout << "UWU Sussy Baka" << std::endl;
    return 0;
    //abort();
    throw std::runtime_error("UWU Sussy Baka");
}
