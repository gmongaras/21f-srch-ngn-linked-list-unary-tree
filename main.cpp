#include <iostream>


#include "QueryProcessor.h"
//#include "DocumentNode.h"
//#include "WordNode.h"
//#include "DocumentProcessor.h"
#include "catch_setup.h"





int main(int argc, char** argv) {
    // If there are no command line arguments, run the catch tests
//    if(argc == 1) {
//        runCatchTests();
//        return 0;
//    }



    // Create a query processor object to handle queries
    QueryProcessor q;

    // Holds a query from the user
    std::string query;


    // Process the documents from the input files
    std::string inputDir("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/srch-ngn-data/size-10");
    q.Load(inputDir);


    // Iterate until the search engine is closed
    while (!q.isShutdown()) {
        // Prompt the user for input
        std::cout << "Enter a query to be handled. Enter ~W~ to exit:" << std::endl;
        getline(std::cin, query);

        // If the query is ~W~, stop the query
        if (query == std::string("~W~")) {
            q.Shutdown();
        }
        // If the query is not ~W~, search
        else {

            // Try to find a result given the query
            std::vector<DocumentNode> results;
            try {
                //results = p.search(std::string(argv[2]));
                results = q.ProcessQuery(query);

                // If a result was found, display it
                if (!results.empty()) {
                    std::cout << "Results: " << std::endl;
                    for (int i = 0; i < results.size(); i++) {
                        std::cout << results[i] << std::endl;
                    }
                }
                // If a result wasn't found, display an error message
                else {
                    std::cout << "No results for query" << std::endl;
                }

            } catch (std::logic_error& e) {
                // If a result wasn't found, display an error message
                std::cout << "No results for query" << std::endl;
            } catch (std::runtime_error& e) {
                // If a result wasn't found, display an error message
                std::cout << "No results for query" << std::endl;
            }

            std::cout << std::endl << std::endl;
        }
    }


    std::cout << "Shutting down..." << std::endl;
    std::cout << "Thanks for using the Unary Tree Search Engine Sussy Baka UwU" << std::endl;



    return 0;
}
