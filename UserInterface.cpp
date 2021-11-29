#include "UserInterface.h"
#include <iostream>




/*******************************
 **    handleAction Method    **
 ******************************/
void UserInterface::handleAction(int action) {
    switch (action) {
        // If the action is 1, clear the index
        case 1: {
            QP.clearIndex();
            break;
        }



        // If the action is 2, parse a dataset
        case 2: {
            break;// parse dataset
        }



        // If the action is 3, handle a query
        case 3: {
            // Query to handle
            std::string query;

            // Get an input from the user
            std::cout << "Enter a query to be handled:" << std::endl;
            getline(std::cin, query);

            //Try to find a result given the query
            std::vector<DocumentNode> results;
            try {
                //results = p.search(std::string(argv[2]));
                results = QP.ProcessQuery(query);

                // If a result was found, display it and ask to
                // display more info
                if (!results.empty()) {
                    std::cout << "Results: " << std::endl;
                    for (int i = 0; i < std::min((int)results.size(), 15); i++) {
                        std::cout << i+1 << ": " << results[i] << std::endl;
                    }

                    // Ask the user which document they'd like to display
                    std::string docToDisplay;
                    std::cout << "Enter a document to display (1-" << std::min((int)results.size(), 15) << "). Enter any number outside that range to cancel." << std::endl;
                    getline(std::cin, docToDisplay);

                    // Try converting the user entered value to an int, cancel if it cannot be
                    int val;
                    try {
                        val = stoi(docToDisplay)-1;
                    } catch (std::logic_error& e) {
                        std::cout << std::endl << std::endl;
                        return;
                    }

                    // If the value is between the bounds, display the document
                    if (val > -1 && val < std::min((int)results.size(), 15)) {
                        // Open the document
                        FILE* filePointer = fopen(results[val].getName().c_str(), "rb");

                        char* readBuffer = new char[228362]; // The buffer
                        int readBufferSize = sizeof(readBuffer);

                        // Read the JSON from the file
                        rapidjson::FileReadStream* inputStream = new rapidjson::FileReadStream(filePointer, readBuffer, readBufferSize);
                        rapidjson::Document *doc = new rapidjson::Document;
                        doc->ParseStream(*inputStream);

                        // Display the document contents
                        std::cout << (*doc)["text"].GetString();

                        // Free the used memory
                        delete doc;
                        delete inputStream;
                        fclose(filePointer);
                        delete [] readBuffer;
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
            break;
        }



        // If the action is 4, output statistics
        case 4: {
            std::vector<float> stats = QP.getStats();
            std::cout << "Stats:" << std::endl
                      << "      Total articles read:                  " << stats[0] << std::endl
                      << "      Average words per article:            " << stats[1] << std::endl
                      << "      Total number of unique words indexed: " << stats[2] << std::endl
                      << "      Total number of unique organizations: " << stats[3] << std::endl
                      << "      Total number of unique people:        " << stats[4] << std::endl
                      << "      Total time to parse files:            " << stats[5] << " seconds" << std::endl
                      << "      Top 50 most frequent words:           " << QP.getTopFifty()[0].word << " " << QP.getTopFifty()[0].count << std::endl;
            break;// output stats
        }



        // If the action is 5, shutdown search engine
        case 5: {
            QP.Shutdown();
            break;
        }



        default: {
            // Display an error message to the user
            std::cout << "Invalid action" << std::endl << std::endl;
        }
    }
}














/*****************************
 **    Initialize Method    **
 ****************************/
void UserInterface::Initialize() {
    // Initialize the query processor


    // Process the documents from the input files
    std::string inputDir("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/srch-ngn-data/size-10");
    QP.Load(inputDir);

    std::cout << "┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << std::endl
    << "│                                                                                                                                         │" << std::endl
    << "│              ___  ___  ________   ________  ________      ___    ___      _________  ________  _______   _______                        │" << std::endl
    << "│             |\\  \\|\\  \\|\\   ___  \\|\\   __  \\|\\   __  \\    |\\  \\  /  /|    |\\___   ___\\\\   __  \\|\\  ___ \\ |\\  ___ \\                       │" << std::endl
    << "│             \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\|\\  \\   \\ \\  \\/  / /    \\|___ \\  \\_\\ \\  \\|\\  \\ \\   __/|\\ \\   __/|                      │" << std::endl
    << "│              \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\   __  \\ \\   _  _\\   \\ \\    / /          \\ \\  \\ \\ \\   _  _\\ \\  \\_|/_\\ \\  \\_|/__                    │" << std::endl
    << "│               \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\\\  \\|   \\/  /  /            \\ \\  \\ \\ \\  \\\\  \\\\ \\  \\_|\\ \\ \\  \\_|\\ \\                   │" << std::endl
    << "│                \\ \\_______\\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\__\\\\ _\\ __/  / /               \\ \\__\\ \\ \\__\\\\ _\\\\ \\_______\\ \\_______\\                  │" << std::endl
    << "│                 \\|_______|\\|__| \\|__|\\|__|\\|__|\\|__|\\|__|\\___/ /                 \\|__|  \\|__|\\|__|\\|_______|\\|_______|                  │" << std::endl
    << "│                                                         \\|___|/                                                                         │" << std::endl
    << "│                                                                                                                                         │" << std::endl
    << "│                                                                                                                                         │" << std::endl
    << "│     ________  _______   ________  ________  ________  ___  ___          _______   ________   ________  ___  ________   _______          │" << std::endl
    << "│    |\\   ____\\|\\  ___ \\ |\\   __  \\|\\   __  \\|\\   ____\\|\\  \\|\\  \\        |\\  ___ \\ |\\   ___  \\|\\   ____\\|\\  \\|\\   ___  \\|\\  ___ \\         │" << std::endl
    << "│    \\ \\  \\___|\\ \\   __/|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\\\\\  \\       \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\ \\   __/|        │" << std::endl
    << "│     \\ \\_____  \\ \\  \\_|/_\\ \\   __  \\ \\   _  _\\ \\  \\    \\ \\   __  \\       \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\ \\  \\\\ \\  \\ \\  \\_|/__      │" << std::endl
    << "│      \\|____|\\  \\ \\  \\_|\\ \\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\____\\ \\  \\ \\  \\       \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\     │" << std::endl
    << "│        ____\\_\\  \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\ \\__\\ \\__\\       \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\__\\ \\__\\\\ \\__\\ \\_______\\    │" << std::endl
    << "│       |\\_________\\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|        \\|_______|\\|__| \\|__|\\|_______|\\|__|\\|__| \\|__|\\|_______|    │" << std::endl
    << "│       \\|_________|                                                                                                                      │" << std::endl
    << "│                                                                                                                                         │" << std::endl
    << "│                                                                                                                                         │" << std::endl
    << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << std::endl;
}



/*****************************
 **    promptUser Method    **
 ****************************/
void UserInterface::promptUser() {
    // Holds an action from the user
    std::string action;


    // Iterate until the search engine is closed
    while (!QP.isShutdown()) {
        // Prompt the user for input
        std::cout << "Menu:" << std::endl
                  << "      1. Clear index completely" << std::endl
                  << "      2. Load data" << std::endl
                  << "      3. Enter query" << std::endl
                  << "      4. See statistics" << std::endl
                  << "      5. Shutdown search engine" << std::endl;
        getline(std::cin, action);

        // Handle the action from the user
        try {
            handleAction(stoi(action));
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid action" << std::endl << std::endl;
        }




//        // Prompt the user for input
//        std::cout << "Enter a query to be handled. Enter ~W~ to exit:" << std::endl;
//        getline(std::cin, query);
//
//        // If the query is ~W~, stop the query
//        if (query == std::string("~W~")) {
//            QP.Shutdown();
//        }
//        // If the query is not ~W~, search
//        else {
//
//            // Try to find a result given the query
//            std::vector<DocumentNode> results;
//            try {
//                //results = p.search(std::string(argv[2]));
//                results = QP.ProcessQuery(query);
//
//                // If a result was found, display it
//                if (!results.empty()) {
//                    std::cout << "Results: " << std::endl;
//                    for (int i = 0; i < results.size(); i++) {
//                        std::cout << results[i] << std::endl;
//                    }
//                }
//                // If a result wasn't found, display an error message
//                else {
//                    std::cout << "No results for query" << std::endl;
//                }
//
//            } catch (std::logic_error& e) {
//                // If a result wasn't found, display an error message
//                std::cout << "No results for query" << std::endl;
//            } catch (std::runtime_error& e) {
//                // If a result wasn't found, display an error message
//                std::cout << "No results for query" << std::endl;
//            }
//
//            std::cout << std::endl << std::endl;
//        }
    }


    std::cout << "Shutting down..." << std::endl;
    std::cout << "Thanks for using the Unary Tree Search Engine Sussy Baka UwU" << std::endl;
}