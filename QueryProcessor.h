#ifndef INC_21F_FINAL_PROJ_TEMPLATE_QUERYPROCESSOR_H
#define INC_21F_FINAL_PROJ_TEMPLATE_QUERYPROCESSOR_H


#include "DocumentProcessor.h"



class QueryProcessor {
private:
    DocumentProcessor DocProcessor;
    bool shutdown; // True if the search engine is shutdown, false otherwise


    /**
     * tokStr
     * Tokenizes a string given a token
     * @param str The string to tokenize
     * @param tok The token used to tokenize the string
     * @return A vector holding the tokenized string
     */
    std::vector<std::string> tokStr(std::string& str, char tok = ' ');



    /**
     * Intersection Method
     * Takes the intersection of two vectors
     * @param vec1 The first vector to compare
     * @param vec2 The second vector to compare
     * @return A vector with the intersection of the two given vectors
     */
    template <typename vectype>
    std::vector<vectype> Intersection(std::vector<vectype>& vec1, std::vector<vectype>& vec2);



    /**
     * Union Method
     * Takes the Union of two vectors
     * @param vec1 The first vector to compare
     * @param vec2 The second vector to compare
     * @return A vector with the union of the two given vectors
     */
    template <typename vectype>
    std::vector<vectype> Union(std::vector<vectype>& vec1, std::vector<vectype>& vec2);



    /**
     * Difference Method
     * Takes the Difference of two vectors
     * @param vec1 The first vector to compare
     * @param vec2 The second vector to compare
     * @return A vector with the difference of the two given vectors
     */
    template <typename vectype>
    std::vector<vectype> Difference(std::vector<vectype>& vec1, std::vector<vectype>& vec2);



    /**
     * queryWords
     * Given a vector of strings, it queries all words in the vector on a specific mode
     * @param vec A vector of strings to query
     * @param mode Query using either the AND or OR clause or query using none
     * @return The result of the query
     */
    std::vector<DocumentNode> queryWords(std::vector<std::string>& vec, std::string& mode);



    /**
     * sortVec Method
     * Given a vector of DocumentNodes, it returns the sorted form of that vector
     * based on the Relevancy Ranking.
     * @param vec A vector to sort
     * @return A sorted DocumentNode vector
     */
    std::vector<DocumentNode> sortVec(std::vector<DocumentNode> vec);



public:
    /**
     * Constructor
     */
    QueryProcessor();

    /**
     * clearIndex
     * Clear all items from the index
     */
    void clearIndex();

    /**
     * getStats
     * @return A vector of stats to display
     */
    std::vector<float> getStats();

    /**
     * getTop50
     * @return A vector of the top 50 most common words
     */
    std::vector<DocumentProcessor::wordToCount> getTopFifty();

    /**
     * saveFiles
     * Saves the info in index given three file names
     * @param wordsFileName The name of the file to save the words AVL Tree
     * @param peopleFileName The name of the file to save the people Hash Table
     * @param orgsFileName The name of the file to save the organizations Hash Table
     */
    void saveFiles(std::string& wordsFileName, std::string& peopleFileName, std::string& orgsFileName);

    /**
     * LoadDir Method
     * Load the data for the search engine from multiple files in a single directory
     * @param directory The directory used to load the documents from
     */
    void LoadDir(std::string& directory);

    /**
     * LoadFiles Method
     * Load the data for the search engine from three different preloaded files
     * @param wordsFileName The name of the file to load the words AVL Tree from
     * @param peopleFileName The name of the file to load the people Hash Table from
     * @param orgsFileName The name of the file to load the organizations Hash Table from
     */
    void LoadFiles(std::string& wordsFileName, std::string& peopleFileName, std::string& orgsFileName);

    /**
     * ProcessQuery Method
     * Processes a given query
     * @param query The query to process
     * @return The results of the query
     */
    std::vector<DocumentNode> ProcessQuery(std::string& query);

    /**
     * isShutdown Method
     * @return True if the search engine is shutdown, false otherwise
     */
    bool isShutdown();

    /**
     * shutdown Method
     * Shuts down the search engine
     */
    void Shutdown();
};




#endif //INC_21F_FINAL_PROJ_TEMPLATE_QUERYPROCESSOR_H
