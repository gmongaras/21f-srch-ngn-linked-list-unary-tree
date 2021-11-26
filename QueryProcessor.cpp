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
 **    Difference Method    **
 ****************************/
template <typename vectype>
std::vector<vectype> QueryProcessor::Difference(std::vector<vectype> &vec1, std::vector<vectype> &vec2) {
    // Vector to hold the difference of the two given vectors
    std::vector<vectype> diffVec;

    // Iterate over all values in vec 1
    for (int i = 0; i < vec1.size(); i++) {
        // Boolean to ensure the current value in vec1 isn't in vec2.
        bool inVec2 = false;

        // Iterate over all values in vec2
        for (int j = 0; j < vec2.size(); j++) {
            // If the values in vec1 and vec2 are the same, change
            // the boolean to ensure the value isn't added
            // to the new vector
            if (vec1[i] == vec2[j]) {
                inVec2 = true;
                break;
            }
        }

        // If the current value in vec1 is not in vec2, add it
        // to the new vector
        if (!inVec2) {
            diffVec.emplace_back(vec1[i]);
        }
    }

    // Return the difference vector
    return diffVec;
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

    // Initial location of NOT queries if any
    int notLoc = -1;
    // Initial location of ORG queries if any
    int orgLoc = -1;
    // Initial location of PERSON queries if any
    int personLoc = -1;


    // Query all words
    for (int i = startIndex; i < vec.size(); i++) {
        // If NOT is seen, change the location of the notLoc
        if (vec[i] == "not") {
            notLoc = i-1;
            if (orgLoc != -1) {
                notLoc--;
            }
            if (personLoc != -1) {
                notLoc--;
            }
            continue;
        }
        // IF ORG is seen, change the location of the orgLoc
        else if (vec[i] == "org") {
            orgLoc = i-1;
            if (notLoc != -1) {
                orgLoc--;
            }
            if (personLoc != -1) {
                orgLoc--;
            }
            continue;
        }
        // If PERSON is seen, change the location of the personLoc
        else if (vec[i] == "person") {
            personLoc = i-1;
            if (notLoc != -1) {
                personLoc--;
            }
            if (orgLoc != -1) {
                personLoc--;
            }
            continue;
        }
        queries.emplace_back(DocProcessor.search(vec[i]).getDocuments().getInOrderVec());
    }



    // If the query mode is and, keep and store the documents that
    // appear in all lists
    if (mode == "and") {
        // Store the current intersection
        std::vector<DocumentNode> interVec;

        // Get the intersection between the first and second elements in the vector
        interVec = Intersection<DocumentNode>(queries[0], queries[1]);

        // Get the intersection for all other elements keeping in mind subtraction,
        // org, and person queries.
        for (int i = 2; i < queries.size(); i++) {
            // If the current value is the location of subtractions,
            // query by subtraction
            if (i >= notLoc && notLoc != -1) {
                interVec = Difference<DocumentNode>(interVec, queries[i]);
            }
            // If the current value is not special, query normally
            else {
                interVec = Intersection<DocumentNode>(interVec, queries[i]);
            }
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
            // If the current value is the location of subtractions,
            // query by subtraction
            if (i >= notLoc && notLoc != -1) {
                unionVec = Difference<DocumentNode>(unionVec, queries[i]);
            }
            // If the current value is not special, query normally
            else {
                unionVec = Union<DocumentNode>(unionVec, queries[i]);
            }
        }

        // Return the union of all words
        return unionVec;
    }



    // If the second item in the query vector is NOT, query with subtraction
    if (notLoc == 0) {
        // The current difference
        std::vector<DocumentNode> diffvec = queries[0];

        // Takes the difference using all words after the "NOT" symbol
        for (int i = 1; i < queries.size(); i++) {
            diffvec = Difference<DocumentNode>(diffvec, queries[i]);
        }

        // Return the vector
        return diffvec;
    }

    // If the mode is not 'OR' or 'AND' and subtraction isn't used,
    // return the first vector of results
    return queries[0];
}



/*******************
 **    sortVec    **
 ******************/
std::vector<DocumentNode> QueryProcessor::sortVec(std::vector<DocumentNode> vec) {
    // Algorithm from https://www.geeksforgeeks.org/insertion-sort/

    int i, j;
    DocumentNode key;
    for (i = 1; i < vec.size(); i++)
    {
        key = vec[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && vec[j].getRelevancyRanking() < key.getRelevancyRanking())
        {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }

    // Return the sorted vector
    return vec;
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
            return sortVec(DocProcessor.search(tokenizedQuery[1]).getDocuments().getInOrderVec());
        }
        // If the length of the vector is greater than 2, query all given words
        else {
            return sortVec(queryWords(tokenizedQuery, tokenizedQuery[0]));
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
            return sortVec(DocProcessor.search(tokenizedQuery[1]).getDocuments().getInOrderVec());
        }
        // If the length of the vector is greater than 2, query all given words
        else {
            return sortVec(queryWords(tokenizedQuery, tokenizedQuery[0]));
        }
    }
    // If the first word is not blank, query only that word
    else if (!tokenizedQuery[0].empty()) {
        return sortVec(queryWords(tokenizedQuery, tokenizedQuery[0]));
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