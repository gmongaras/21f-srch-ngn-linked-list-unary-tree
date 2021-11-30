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
public:
    // Struct to hold information on the word counts in an AVL tree. It holds a single
    // word and the word count for that word. This will be used to store the number
    // of times each words appears in all the documents
    struct wordToCount {
        std::string word;
        int count;

        wordToCount() {
            word = "";
            count = 0;
        }

        wordToCount(std::string& s) {
            word = s;
            count = 1;
        }

        bool operator<(wordToCount& w) {
            return word < w.word;
        }

        bool operator>(wordToCount& w) {
            return word > w.word;
        }

        bool operator==(wordToCount& w) {
            return word == w.word;
        }

        void increaseCount() {
            count++;
        }
    };



private:
    AVLTree<std::string> stopWords;
    AVLTree<wordToCount> wordCounts;
    Index index;
    long NUMFILES;
    std::chrono::duration<float> timeToParse;



    /**
     * cleanAndAdd Method
     * Cleans and adds data to the AVL tree
     * @param doc The document to clean and store
     * @param docName The name of the document to store
     */
    void cleanAndAdd(rapidjson::Document*& doc, std::string& docName);


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
     */
    void processDocumentsHelper(const std::string& directory, long& numFiles);



public:
    /**
     * Default Constructor
     */
    DocumentProcessor();


    /**
     * clearIndex
     * Clears all items from the index
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
     * processDocumentsDir Method
     * Accepts a directory name to parse .json documents from
     * @param directory The name of the directory to parse files from
     */
    void processDocumentsDir(const std::string& directory);

    /**
     * processDocumentsFiles Method
     * Accepts a few files to parse the indices from
     * @param wordsFileName The name of the file to load the words AVL Tree from
     * @param peopleFileName The name of the file to load the people Hash Table from
     * @param orgsFileName The name of the file to load the organizations Hash Table from
     */
    void processDocumentsFiles(std::string& wordsFileName, std::string& peopleFileName, std::string& orgsFileName);

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