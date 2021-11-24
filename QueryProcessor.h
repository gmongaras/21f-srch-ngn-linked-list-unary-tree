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
    std::vector<std::string> tokStr(std::string& str, char tok);



public:
    /**
     * Constructor
     */
    QueryProcessor();


    /**
     * Init
     * Initializes the query processor and displays a prompt
     */
    void Initialize();

    /**
     * Load
     * Load the search engine
     * @param directory The directory used to load the documents from
     */
    void Load(std::string& directory);

    /**
     * ProcessQuery Method
     * Processes a given query
     * @param query The query to process
     * @return The results of the query
     */
    WordNode& ProcessQuery(std::string& query);

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
