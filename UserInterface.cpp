#include "UserInterface.h"
#include <iostream>




/*******************************
 **    handleAction Method    **
 ******************************/
void UserInterface::handleAction(int action) {
    switch (action) {
        // If the action is 1, clear the index
        case 1: {
            // If the index is already clear, show an error message
            if (indexClear) {
                std::cout << "Index already cleared" << std::endl << std::endl;
                break;
            }

            std::cout << "Clearing index..." << std::endl;
            QP.clearIndex();
            indexClear = true;
            std::cout << "Index cleared" << std::endl;
            std::cout << std::endl << std::endl;
            break;
        }



        // If the action is 2, save the structures to specified filenames
        case 2: {
            // If the index is clear, show an error message
            if (indexClear) {
                std::cout << "Index cleared. Please enter new data before saving any data structures." << std::endl << std::endl;
                break;
            }

            // Get three filename from the user
            std::string f1;
            std::string f2;
            std::string f3;
            std::cout << "Please enter a filename to save the Words AVL Tree:" << std::endl;
            getline(std::cin, f1);
            std::cout << std::endl;

            std::cout << "Please enter a filename to save the People Hash Table:" << std::endl;
            getline(std::cin, f2);
            std::cout << std::endl;

            std::cout << "Please enter a filename to save the Organizations Hash Table:" << std::endl;
            getline(std::cin, f3);
            std::cout << std::endl;


            // Save the files
            QP.saveFiles(f1, f2, f3);

            break;
        }



        // If the action is 3, parse a dataset
        case 3: {
            // If the index is not cleared, clear the index
            if (!indexClear) {
                std::cout << "Clearing index..." << std::endl;
                QP.clearIndex();
                indexClear = true;
                std::cout << "Index cleared" << std::endl;
                std::cout << std::endl << std::endl;
            }

            // Read in the data
            bool fail = readFiles();

            // If the files were not successfully read in, break the case
            if (fail) {
                std::cout << "Files could not be read in." << std::endl;
                break;
            }

            // The index is no longer cleared
            indexClear = false;

            std::cout << std::endl << std::endl;

            break;
        }



        // If the action is 4, handle a query
        case 4: {
            // If the index is clear, show an error message
            if (indexClear) {
                std::cout << "Index cleared. Please enter new data before handling a query." << std::endl << std::endl;
                break;
            }

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



        // If the action is 5, output statistics
        case 5: {
            // If the index is clear, show an error message
            if (indexClear) {
                std::cout << "Index cleared. Please enter new data before showing stats." << std::endl << std::endl;
                break;
            }

            // Get the top 50 words
            std::vector<WordNode> top = QP.getTopFifty();

            std::vector<float> stats = QP.getStats();
            std::cout << "Stats:" << std::endl << std::setprecision(19)
                      << "      Total articles read:                       " << stats[0] << " articles" << std::endl << std::fixed << std::setprecision(5)
                      << "      Average words per article:                 " << stats[1] << " words/article" << std::endl << std::defaultfloat << std::setprecision(19)
                      << "      Total number of words indexed:             " << stats[2] << " words" << std::endl
                      << "      Total number of unique words indexed:      " << stats[3] << " unique words" << std::endl
                      << "      Total number of unique organizations:      " << stats[4] << " unique organization" << std::endl
                      << "      Total number of unique people:             " << stats[5] << " unique people" << std::endl << std::fixed << std::setprecision(5)
                      << "      Total time to parse files:                 " << stats[6] << " seconds" << std::defaultfloat << std::endl
                      << "      Top " << std::min((int)top.size(), 50) << " most frequent words after cleaning:           " << std::endl;

            // Display all top words
            for (int i = 0; i < top.size(); i++) {
                std::cout << "          " << i+1 << ": " << "Word: " << top[i].getWord() << "    " << "Count: " << top[i].getCount() << std::endl;
            }
            std::cout << std::endl << std::endl;
            break;// output stats
        }



        // If the action is 6, shutdown search engine
        case 6: {
            QP.Shutdown();
            break;
        }



        default: {
            // Display an error message to the user
            std::cout << "Invalid action" << std::endl << std::endl;
        }
    }
}



/****************************
 **    readFiles Method    **
 ***************************/
bool UserInterface::readFiles() {
    // Ask which mode the user wants to read data
    std::string choice;
    while (choice != "1" && choice != "2") {
        std::cout << "How would you like to read data?" << std::endl
                  << "1. From scratch using a directory of data files" << std::endl
                  << "2. Using several files with preloaded data" << std::endl;

        getline(std::cin, choice);

        // Error checking
        if (choice != "1" && choice != "2") {
            std::cout << "Invalid input" << std::endl << std::endl;
        }
    }


    // If the choice is 1, read data normally from a directory
    std::cout << std::endl;
    if (choice == "1") {
        // Process the documents from the input files
        bool dataRead = false;
        std::string inputDir;
        while (!dataRead && inputDir != "~W~") {
            std::cout << "Please enter a directory to read from: " << std::endl;
            getline(std::cin, inputDir);
            try {
                std::cout << "Reading data..." << std::endl;
                QP.LoadDir(inputDir);
                dataRead = true;
            } catch (std::runtime_error e) {
                if (inputDir != "~W~") {
                    std::cout << "Directory is invalid. Please enter a valid directory to read data from or ~W~ to cancel." << std::endl << std::endl;
                }
            }
        }

        // If the exit key was used, return true as the file reading was unsuccessful
        if (inputDir == "~W~") {
            return true;
        }
    }
    // If the choice is 2, read data from a few premade datafiles
    else {
        // Get three filename from the user
        std::string f1;
        std::string f2;
        std::string f3;
        std::cout << "Please enter a filename to read the Words AVL Tree from:" << std::endl;
        getline(std::cin, f1);
        std::cout << std::endl;

        std::cout << "Please enter a filename to read the People Hash Table from:" << std::endl;
        getline(std::cin, f2);
        std::cout << std::endl;

        std::cout << "Please enter a filename to read the Organizations Hash Table from:" << std::endl;
        getline(std::cin, f3);
        std::cout << std::endl;


        // Load the files
        QP.LoadFiles(f1, f2, f3);
    }

    return false;
}


















/*****************************
 **    Initialize Method    **
 ****************************/
void UserInterface::Initialize() {
    // Initialize the query processor
    indexClear = false;

    // Read the data
    bool fail = readFiles();

    // If files reading failed, don't do anything
    if (fail) {
        QP.Shutdown();
        return;
    }

    std::cout << "┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                 "│                                                                                                                                         │\n"
                 "│              ___  ___  ________   ________  ________      ___    ___      _________  ________  _________  _________                     │\n"
                 "│             |\\  \\|\\  \\|\\   ___  \\|\\   __  \\|\\   __  \\    |\\  \\  /  /|    |\\___   ___\\\\   __  \\|\\   _____\\|\\   _____\\                    │\n"
                 "│             \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\|\\  \\   \\ \\  \\/  / /    \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\_____\\ \\  \\_____\\                   │\n"
                 "│              \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\   __  \\ \\   _  _\\   \\ \\    / /          \\ \\  \\ \\ \\   _  _\\ \\   _____\\ \\   _____\\                  │\n"
                 "│               \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\\\  \\|   \\/  /  /            \\ \\  \\ \\ \\  \\\\  \\\\ \\  \\_____\\ \\  \\_____\\                 │\n"
                 "│                \\ \\_______\\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\__\\\\ _\\ __/  / /               \\ \\__\\ \\ \\__\\\\ _\\\\ \\________\\ \\________\\                │\n"
                 "│                 \\|_______|\\|__| \\|__|\\|__|\\|__|\\|__|\\|__|\\___/ /                 \\|__|  \\|__|\\|__|\\|________|\\|________|                │\n"
                 "│                                                         \\|___|/                                                                         │\n"
                 "│                                                                                                                                         │\n"
                 "│                                                                                                                                         │\n"
                 "│    ________  ________   ________  ________  ________  ___  ___          _________  ________   ________  ___  ________   _________       │\n"
                 "│   |\\   ____\\|\\   _____\\|\\   __  \\|\\   __  \\|\\   ____\\|\\  \\|\\  \\        |\\   _____\\|\\   ___  \\|\\   ____\\|\\  \\|\\   ___  \\|\\   _____\\      │\n"
                 "│   \\ \\  \\___|\\ \\  \\_____\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\\\\\  \\       \\ \\  \\_____\\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\ \\  \\\\ \\  \\ \\  \\_____\\     │\n"
                 "│    \\ \\_____  \\ \\   _____\\ \\   __  \\ \\   _  _\\ \\  \\    \\ \\   __  \\       \\ \\   _____\\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\ \\  \\\\ \\  \\ \\   _____\\    │\n"
                 "│     \\|____|\\  \\ \\  \\_____\\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\____\\ \\  \\ \\  \\       \\ \\  \\_____\\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_____\\   │\n"
                 "│       ____\\_\\  \\ \\________\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\ \\__\\ \\__\\       \\ \\________\\ \\__\\\\ \\__\\ \\_______\\ \\__\\ \\__\\\\ \\__\\ \\________\\  │\n"
                 "│      |\\_________\\|________|\\|__|\\|__|\\|__|\\|__|\\|_______|\\|__|\\|__|        \\|________|\\|__| \\|__|\\|_______|\\|__|\\|__| \\|__|\\|________|  │\n"
                 "│      \\|_________|                                                                                                                       │\n"
                 "│                                                                                                                                         │\n"
                 "│                                                                                                                                         │\n"
                 "└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << std::endl;
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
                  << "      2. Save data structures" << std::endl
                  << "      3. Load data" << std::endl
                  << "      4. Enter query" << std::endl
                  << "      5. See statistics" << std::endl
                  << "      6. Shutdown search engine" << std::endl;
        getline(std::cin, action);

        std::cin.clear();                              //clear errors/bad flags on cin
        std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');//precise amount of ignoring
        std::cin.rdbuf()->in_avail(); //returns the exact number of characters in the cin buffer.

        // Handle the action from the user
        try {
            handleAction(stoi(action));
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid action" << std::endl << std::endl;
        }
    }


    std::cout << "Shutting down..." << std::endl;
    std::cout << "Thanks for using the Unary Tree Search Engine Sussy Baka UwU" << std::endl;
}