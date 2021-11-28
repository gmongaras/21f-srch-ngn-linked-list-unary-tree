#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H


#include "Index.h"
#include <string>
#include <bits/stdc++.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/pointer.h"
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <time.h>
#include <unistd.h>
#include "./porter2_stemmer/porter2_stemmer.h"
#include "dirent.h"
#include "sys/stat.h"






class DocumentProcessor {
private:
    AVLTree<std::string> stopWords;
    Index index;
    int NUMFILES;
    int NUMWORDS;



    /**
     * tokStr
     * Tokenizes a string given a token
     * @param str The string to tokenize
     * @param tok The token used to tokenize the string
     * @return A vector holding the tokenized string
     */
    std::vector<std::string> tokStr(std::string& str, char tok = ' ');



    /**
     * cleanAndAdd Method
     * Cleans and adds data to the AVL tree
     * @param doc The document to clean and store
     * @param docName The name of the document to store
     * @param numWords The number of words read in
     */
    void cleanAndAdd(rapidjson::Document*& doc, std::string& docName, int& numWords);


    /**
     * storeStopWords Method
     * Given a filename, it reads in and stores all stopwords
     * @param filename The name of the file to read the stop words from
     */
    void storeStopWords(const std::string& filename);


    /**
     * processDocuments Helper Method
     * Reads in the files given a directory
     * @param directory The name of the directory to parse files from
     * @param numFiles THe number of files read in
     * @param numWords The number of words read in
     * @return The number of files read in total.
     */
    int processDocumentsHelper(const std::string& directory, int& numFiles, int& numWords);



public:
    /**
     * clearIndex
     * Clears all items from the index
     */
    void clearIndex();

    /**
     * processDocuments Method
     * Accepts a directory name to parse .json documents from
     * @param directory The name of the directory to parse files from
     * @return The stored index object containing the information from
     *         the parsed datafiles
     */
    void processDocuments(const std::string& directory);

    /**
     * searchWord Method
     * Accepts a word to search for in the Words tree and returns the
     * WordNode containing that word
     * @param word The word to search for
     * @return A WordNode containing that word
     */
    WordNode searchWord(std::string word);

    /**
     * searchPeople Method
     * Accepts a person to search for in the People Hash Map and returns
     * the results from the search in the Hash Map
     * @param person The person to search for
     * @return A WordNode containing information on that person
     */
    WordNode searchPeople(std::string person);

    /**
     * searchOrgs Method
     * Accepts a organization to search for in the Orgs Hash Map and returns
     * the results from the search in the Hash Map
     * @param org The organization to search for
     * @return A WordNode containing information on that organization
     */
    WordNode searchOrgs(std::string org);
};




#endif // INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H