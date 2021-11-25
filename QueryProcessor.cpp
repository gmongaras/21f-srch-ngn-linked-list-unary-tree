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
        if (str[i] == tok) {
            if (!substr.empty()) {
                tokenizedString.emplace_back(substr);
            }

            // Clear the substring
            substr.clear();
            continue;
        }

        // Add the next character to the substring
        substr += str[i];
    }

    // Add the final substring to the vector
    tokenizedString.emplace_back(substr);

    // Return the vector of substring
    return tokenizedString;
}



/*******************************
 **    Intersection Method    **
 ******************************/
template <typename vectype>
std::vector<vectype> QueryProcessor::Intersection(std::vector<vectype> &vec1, std::vector<vectype> &vec2) {
    // Vector to hold the intersection of the two vectors
    std::vector<vectype> interVec;

    // Iterate over all values in vec1
    for (int i = 0; i < vec1.size(); i++) {
        // Iterate over all values in vec2 to check if the same value was found.
        for (int j = 0; j < vec2.size(); j++) {
            // If the current value being looked at in vec1 is the same as the
            // current value being looked at in vec2, add it to the unionVec
            if (vec1[i] == vec2[j]) {
                interVec.emplace_back(vec1[i]);
                break;
            }
        }
    }

    // Return the intersection vector
    return interVec;
}



/************************
 **    Union Method    **
 ***********************/
template <typename vectype>
std::vector<vectype> QueryProcessor::Union(std::vector<vectype> &vec1, std::vector<vectype> &vec2) {
    // Vector to hold the union of the two vectors
    std::vector<vectype> unionVec = vec1;

    // Iterate over all values in vec2
    for (int i = 0; i < vec2.size(); i++) {
        // True if the current value is in the unionVec, false otherwise
        bool repeat = false;

        // Iterate over all values in unionVec to check if the same value was found.
        for (int j = 0; j < unionVec.size(); j++) {
            // If the current value being looked at in vec2 is the same as the
            // current value being looked at in unionVec, set the boolean to
            // true as the value should not be added again
            if (vec2[i] == unionVec[j]) {
                repeat = true;
                break;
            }
        }

        // If the item is not a repeat, add it to the unionVec
        if (!repeat) {
            unionVec.emplace_back(vec2[i]);
        }
    }

    // Return the union vector
    return unionVec;
}



/*****************************
 **    queryWords Method    **
 ****************************/
std::vector<DocumentNode> QueryProcessor::queryWords(std::vector<std::string>& vec, std::string& mode) {
    // The index to start at
    int startIndex = 0;

    // If the mode is AND or OR, skip the first word in the vector
    if (mode == "and" || mode == "or") {
        startIndex = 1;
    }


    // Holds all queries
    std::vector<std::vector<DocumentNode>> queries;


    // Query all words
    for (int i = startIndex; i < vec.size(); i++) {
        queries.emplace_back(DocProcessor.search(vec[i]).getDocuments().getInOrderVec());
    }



    // If the query mode is and, keep and store the documents that
    // appear in all lists
    if (mode == "and") {
        // Store the current intersection
        std::vector<DocumentNode> interVec;

        // Get the intersection between the first and second elements in the vector
        interVec = Intersection<DocumentNode>(queries[0], queries[1]);

        // Get the intersection for all other elements
        for (int i = 2; i < queries.size(); i++) {
            interVec = Intersection<DocumentNode>(interVec, queries[i]);
        }

        // Return the union of all words
        return interVec;
    }



    // If the query mode is or, keep and store the documents that
    // appear in any of the lists
    else if (mode == "or") {
        // Store the current union
        std::vector<DocumentNode> unionVec;

        // Get the union between the first and second elements in the vector
        unionVec = Union<DocumentNode>(queries[0], queries[1]);

        // Get the union for all other elements
        for (int i = 2; i < queries.size(); i++) {
            unionVec = Union<DocumentNode>(unionVec, queries[i]);
        }

        // Return the union of all words
        return unionVec;
    }


    // If the mode is not OR or AND, return the first vector of results
    return queries[0];
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
std::vector<DocumentNode> QueryProcessor::ProcessQuery(std::string& query) {
    // Lowercase the query
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    // Breakup the query
    std::vector<std::string> tokenizedQuery = tokStr(query, ' ');

    // If the first word is AND, query using the AND clause
    if (tokenizedQuery[0] == "and") {
        // If the length of the vector is less than 2, print an error message
        if (tokenizedQuery.size() < 2) {
            std::cout << "A query with an AND clause must have at least two arguments" << std::endl << std::endl;
        }
        // If the length of the vector is 2, return a query with just one word
        else if (tokenizedQuery.size() == 2) {
            return DocProcessor.search(tokenizedQuery[1]).getDocuments().getInOrderVec();
        }
        // If the length of the vector is greater than 2, query all given words
        else {
            return queryWords(tokenizedQuery, tokenizedQuery[0]);
        }
    }
    // If the first word is OR, query using the OR clause
    else if (tokenizedQuery[0] == "or") {
        // If the length of the vector is less than 2, print an error message
        if (tokenizedQuery.size() < 2) {
            std::cout << "A query with an OR clause must have at least two arguments" << std::endl << std::endl;
        }
        // If the length of the vector is 2, return a query with just one word
        else if (tokenizedQuery.size() == 2) {
            return DocProcessor.search(tokenizedQuery[1]).getDocuments().getInOrderVec();
        }
        // If the length of the vector is greater than 2, query all given words
        else {
            return queryWords(tokenizedQuery, tokenizedQuery[0]);
        }
    }
    // If the first word is not blank, query only that word
    else if (!tokenizedQuery[0].empty()) {
        return DocProcessor.search(tokenizedQuery[0]).getDocuments().getInOrderVec();
    }
    else {
        // If the first word is blank, print an error message
        std::cout << "Query of incorrect format..." << std::endl << std::endl;
    }
    return {};
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