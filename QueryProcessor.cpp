#include <iostream>
#include "QueryProcessor.h"
#include <set>




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
    // Turn the vectors into sets
    std::set<vectype> s1 = vecToSet(vec1);
    std::set<vectype> s2 = vecToSet(vec2);

    // Get the intersections of the sets
    std::set<vectype> intersect;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersect, intersect.begin()));

    // Return a vector of the intersection
    return setToVec(intersect);
}



/************************
 **    Union Method    **
 ***********************/
template <typename vectype>
std::vector<vectype> QueryProcessor::Union(std::vector<vectype> &vec1, std::vector<vectype> &vec2) {
    // Turn the vectors into sets
    std::set<vectype> s1 = vecToSet(vec1);
    std::set<vectype> s2 = vecToSet(vec2);

    // Get the union of the sets
    std::set<vectype> unionOp;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(unionOp, unionOp.begin()));

    // Return a vector of the union
    return setToVec(unionOp);
}



/*****************************
 **    Difference Method    **
 ****************************/
template <typename vectype>
std::vector<vectype> QueryProcessor::Difference(std::vector<vectype> &vec1, std::vector<vectype> &vec2) {
    // Turn the vectors into sets
    std::set<vectype> s1 = vecToSet(vec1);
    std::set<vectype> s2 = vecToSet(vec2);

    // Get the difference of the sets
    std::set<vectype> diff;
    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(diff, diff.begin()));

    // Return a vector of the difference
    return setToVec(diff);
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

    // The mode to query in
    std::string queryMode("normal");


    // Query all words
    for (int i = startIndex; i < vec.size(); i++) {
        try {
            // If NOT is seen the first time, change the location of the notLoc
            if (vec[i] == "not" && notLoc == -1) {
                notLoc = i-1;
                if (orgLoc != -1) {
                    notLoc--;
                }
                if (personLoc != -1) {
                    notLoc--;
                }
                queryMode = "normal";
                continue;
            }
            // If NOT is seen a second time, given an error message
            else if (vec[i] == "not" && notLoc != -1) {
                std::cout << "There can only be one NOT keyword in a query." << std::endl << std::endl;
                return {};
            }
            // IF ORG is seen, change the location of the orgLoc
            else if (vec[i] == "org" && orgLoc == -1) {
                orgLoc = i-1;
                if (notLoc != -1) {
                    orgLoc--;
                }
                if (personLoc != -1) {
                    orgLoc--;
                }
                queryMode = "org";
                continue;
            }
            // If ORG is seen a second time, given an error message
            else if (vec[i] == "org" && orgLoc != -1) {
                std::cout << "There can only be one ORG keyword in a query." << std::endl << std::endl;
                return {};
            }
            // If PERSON is seen, change the location of the personLoc
            else if (vec[i] == "person" && personLoc == -1) {
                personLoc = i-1;
                if (notLoc != -1) {
                    personLoc--;
                }
                if (orgLoc != -1) {
                    personLoc--;
                }
                queryMode = "person";
                continue;
            }
            // If PERSON is seen a second time, given an error message
            else if (vec[i] == "person" && personLoc != -1) {
                std::cout << "There can only be one PERSON keyword in a query." << std::endl << std::endl;
                return {};
            }

            // Query the word
            if (queryMode == "normal") {
                queries.emplace_back(DocProcessor.searchWord(vec[i]).getDocuments().getInOrderVec());
            }
            else if (queryMode == "person") {
                // Increase i until i+1 is greater than the words vector or until
                // it reaches a new keyword. Continuously append to the temp word along the way.
                std::string temp = vec[i];
                while (i+1 < vec.size()) {
                    if (vec[i+1] == std::string("not") || vec[i+1] == std::string("org")) {
                        break;
                    }

                    temp += " " + vec[i+1];
                    i++;
                }
                queries.emplace_back(DocProcessor.searchPeople(temp).getDocuments().getInOrderVec());
            }
            else if (queryMode == "org") {
                // Increase i until i+1 is greater than the words vector or until
                // it reaches a new keyword. Continuously append to the temp word along the way.
                std::string temp = vec[i];
                while (i+1 < vec.size()) {
                    if (vec[i+1] == std::string("not") || vec[i+1] == std::string("person")) {
                        break;
                    }

                    temp += " " + vec[i+1];
                    i++;
                }
                queries.emplace_back(DocProcessor.searchOrgs(temp).getDocuments().getInOrderVec());
            }

        }
        // If a node wasn't found, add a node with no elements
        catch (std::runtime_error& e) {
            std::vector<DocumentNode> temp;
            queries.emplace_back(temp);
        }
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
            if (i >= notLoc && notLoc != -1 && ((i < personLoc && personLoc > notLoc) || (i > personLoc && personLoc < notLoc && personLoc != -1) || personLoc == -1) && ((i < orgLoc && orgLoc > notLoc) || (i > orgLoc && orgLoc < notLoc && orgLoc != -1) || orgLoc == -1)) {
                interVec = Difference<DocumentNode>(interVec, queries[i]);
            }
            // If the current value is the location of a person, query
            // by person
            // else if (i >= personLoc && personLoc != -1 && ((i < notLoc && notLoc > personLoc) || (i > notLoc && notLoc < personLoc && notLoc != -1) || notLoc == -1) && ((i < orgLoc && orgLoc > personLoc) || (i > orgLoc && orgLoc < personLoc && orgLoc != -1) || orgLoc == -1)) {
//                interVec = Intersection<DocumentNode>(interVec, queries[i]);
//            }
//            // If the current value is the location of an organization, query
//            // by organization
//            else if (i >= orgLoc && orgLoc != -1 && ((i < personLoc && personLoc > orgLoc) || (i > personLoc && personLoc < orgLoc && personLoc != -1) || personLoc == -1) && ((i < notLoc && notLoc > orgLoc) || (i > notLoc && notLoc < orgLoc && notLoc != -1) || notLoc == -1)) {
//                interVec = Intersection<DocumentNode>(interVec, queries[i]);
//            }
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
            if (i >= notLoc && notLoc != -1 && ((i < personLoc && personLoc > notLoc) || (i > personLoc && personLoc < notLoc && personLoc != -1) || personLoc == -1) && ((i < orgLoc && orgLoc > notLoc) || (i > orgLoc && orgLoc < notLoc && orgLoc != -1) || orgLoc == -1)) {
                unionVec = Difference<DocumentNode>(unionVec, queries[i]);
            }
            // If the current value is the location of a person, query
            // by person
            else if (i >= personLoc && personLoc != -1 && ((i < notLoc && notLoc > personLoc) || (i > notLoc && notLoc < personLoc && notLoc != -1) || notLoc == -1) && ((i < orgLoc && orgLoc > personLoc) || (i > orgLoc && orgLoc < personLoc && orgLoc != -1) || orgLoc == -1)) {
                unionVec = Intersection<DocumentNode>(unionVec, queries[i]);
            }
            // If the current value is the location of an organization, query
            // by organization
            else if (i >= orgLoc && orgLoc != -1 && ((i < personLoc && personLoc > orgLoc) || (i > personLoc && personLoc < orgLoc && personLoc != -1) || personLoc == -1) && ((i < notLoc && notLoc > orgLoc) || (i > notLoc && notLoc < orgLoc && notLoc != -1) || notLoc == -1)) {
                unionVec = Intersection<DocumentNode>(unionVec, queries[i]);
            }
            // If the current value is not special, query normally
            else {
                unionVec = Union<DocumentNode>(unionVec, queries[i]);
            }
        }

        // Return the union of all words
        return unionVec;
    }



    // If "ORG" "NOT" or "PERSON" is in the query, handle those
    if (notLoc == 0 || personLoc == 0 || orgLoc == 0) {
        // Store the current query results
        std::vector<DocumentNode> queryResults = queries[0];

        // Get the results for all other elements
        for (int i = 1; i < queries.size(); i++) {
            // If the current value is the location of subtractions,
            // query by subtraction
            if (i >= notLoc && notLoc != -1 && ((i < personLoc && personLoc > notLoc) || (i > personLoc && personLoc < notLoc && personLoc != -1) || personLoc == -1) && ((i < orgLoc && orgLoc > notLoc) || (i > orgLoc && orgLoc < notLoc && orgLoc != -1) || orgLoc == -1)) {
                queryResults = Difference<DocumentNode>(queryResults, queries[i]);
            }
            // If the current value is the location of a person, query
            // by person
            else if (i >= personLoc && personLoc != -1 && ((i < notLoc && notLoc > personLoc) || (i > notLoc && notLoc < personLoc && notLoc != -1) || notLoc == -1) && ((i < orgLoc && orgLoc > personLoc) || (i > orgLoc && orgLoc < personLoc && orgLoc != -1) || orgLoc == -1)) {
                queryResults = Intersection<DocumentNode>(queryResults, queries[i]);
            }
            // If the current value is the location of an organization, query
            // by organization
            else if (i >= orgLoc && orgLoc != -1 && ((i < personLoc && personLoc > orgLoc) || (i > personLoc && personLoc < orgLoc && personLoc != -1) || personLoc == -1) && ((i < notLoc && notLoc > orgLoc) || (i > notLoc && notLoc < orgLoc && notLoc != -1) || notLoc == -1)) {
                queryResults = Intersection<DocumentNode>(queryResults, queries[i]);
            }
            // If the current value is not special, do nothing
        }

        // Return the union of all words
        return queryResults;



//        // The current difference
//        std::vector<DocumentNode> diffvec = queries[0];
//
//        // Takes the difference using all words after the "NOT" symbol
//        for (int i = 1; i < queries.size(); i++) {
//            diffvec = Difference<DocumentNode>(diffvec, queries[i]);
//        }
//
//        // Return the vector
//        return diffvec;
    }

    // If the mode is not 'OR' or 'AND' and a keyword isn't used,
    // return the first vector of results
    return queries[0];
}



/*******************
 **    sortVec    **
 ******************/
bool crit(DocumentNode a, DocumentNode b) {return a.getRelevancyRanking() > b.getRelevancyRanking();}
std::vector<DocumentNode> QueryProcessor::sortVec(std::vector<DocumentNode> vec) {
    std::sort(vec.begin(), vec.end(), &crit);
    return vec;
}




/***************************
 **    vecToSet Method    **
 **************************/
template <typename vectype>
std::set<vectype> QueryProcessor::vecToSet(std::vector<vectype> &vec) {
    std::set<vectype> s(vec.begin(), vec.end());
    return s;
}



/***************************
 **    setToVec Method    **
 **************************/
template <typename settype>
std::vector<settype> QueryProcessor::setToVec(std::set<settype>& s) {
    std::vector<settype> vec(s.size());
    std::copy(s.begin(), s.end(), vec.begin());
    return vec;
}


















/***********************
 **    Constructor    **
 **********************/
QueryProcessor::QueryProcessor() {
    // Set shutdown to false so the search engine doesn't shutdown immediately
    shutdown = false;
}



/**********************
 **    clearIndex    **
 *********************/
void QueryProcessor::clearIndex() {
    DocProcessor.clearIndex();
}



/********************
 **    getStats    **
 *******************/
std::vector<float> QueryProcessor::getStats() {
    return DocProcessor.getStats();
}



/******************************
 **    getTopFifty Method    **
 *****************************/
std::vector<DocumentProcessor::wordToCount> QueryProcessor::getTopFifty() {
    // Get all words from the wordCounts tree
    return DocProcessor.getTopFifty();
}



/****************************
 **    saveFiles Method    **
 ***************************/
void QueryProcessor::saveFiles(std::string &wordsFileName, std::string &peopleFileName, std::string &orgsFileName) {
    DocProcessor.saveFiles(wordsFileName, peopleFileName, orgsFileName);
}



/**************************
 **    LoadDir Method    **
 *************************/
void QueryProcessor::LoadDir(std::string& directory) {
    DocProcessor.processDocumentsDir(directory);
}



/****************************
 **    LoadFiles Method    **
 ***************************/
void QueryProcessor::LoadFiles(std::string &wordsFileName, std::string &peopleFileName, std::string &orgsFileName) {
    DocProcessor.processDocumentsFiles(wordsFileName, peopleFileName, orgsFileName);
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
            return sortVec(DocProcessor.searchWord(tokenizedQuery[1]).getDocuments().getInOrderVec());
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
            return sortVec(DocProcessor.searchWord(tokenizedQuery[1]).getDocuments().getInOrderVec());
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