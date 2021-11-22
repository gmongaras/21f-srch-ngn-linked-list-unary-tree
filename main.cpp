#include <iostream>


#include "DocumentNode.h"
#include "WordNode.h"
#include "DocumentProcessor.h"
#include "catch_setup.h"


int main(int argc, char** argv) {
    // If there are no command line arguments, run the catch tests
    if(argc == 1) {
        runCatchTests();
        return 0;
    }





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



    //std::cout << "UWU Sussy Baka" << std::endl;
    return 0;
    //abort();
    throw std::runtime_error("UWU Sussy Baka");
}
