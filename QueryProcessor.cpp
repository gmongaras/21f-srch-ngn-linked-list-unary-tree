#include <iostream>
#include "QueryProcessor.h"




/*************************
 **    tokStr Method    **
 ************************/
std::vector<std::string> QueryProcessor::tokStr(std::string &str, char tok) {
    // Vector to hold the tokenized string
    std::vector<std::string> tokenizedString;

    // Temporary string to hold each substring
    std::string substr;

    // Iterate over all values in the string
    for (int i = 0; i < str.size(); i++) {
        // If the current character is the token, add the substring to the vector
        if (substr[i] == tok) {
            if (substr.empty() != true) {
                tokenizedString.emplace_back(substr);
            }

            // Clear the substring
            substr.clear();
            continue;
        }

        // Add the next character to the substring
        substr.push_back(str[i]);
    }

    // Add the final substring to the vector
    tokenizedString.emplace_back(substr);

    // Return the vector of substring
    return tokenizedString;
}













/***********************
 **    Constructor    **
 **********************/
QueryProcessor::QueryProcessor() {
    // Set shutdown to false so the search engine doesn't shutdown immediately
    shutdown = false;
}



/*****************************
 **    Initialize Method    **
 ****************************/
void QueryProcessor::Initialize() {
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



/***********************
 **    Load Method    **
 **********************/
void QueryProcessor::Load(std::string& directory) {
    DocProcessor.processDocuments(directory);

    // Initialize the search engine
    Initialize();
}



/*******************************
 **    ProcessQuery Method    **
 ******************************/
WordNode& QueryProcessor::ProcessQuery(std::string& query) {
    // Lowercase the query
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    // Breakup the query
    std::vector<std::string> tokenizedQuery = tokStr(query, ' ');

    // If the first word is AND, query using the AND clause
    if (tokenizedQuery[0] == "and") {
        return DocProcessor.search(tokenizedQuery[0]);
    }
    // If the first word is OR, query using the OR clause
    else if (tokenizedQuery[0] == "or") {
        return DocProcessor.search(tokenizedQuery[0]);
    }
    // If the first word is not blank, query only that word
    else if (!tokenizedQuery[0].empty()) {
        return DocProcessor.search(tokenizedQuery[0]);
    }
    // If the first word is blank, print an error message
    else {
        std::cout << "Query of incorrect format..." << std::endl << std::endl;
        return DocProcessor.search(tokenizedQuery[0]);
    }
}



/*****************************
 **    isShutdown Method    **
 ****************************/
bool QueryProcessor::isShutdown() {
    return shutdown;
}



/***************************
 **    Shutdown Method    **
 **************************/
void QueryProcessor::Shutdown() {
    shutdown = true;
}