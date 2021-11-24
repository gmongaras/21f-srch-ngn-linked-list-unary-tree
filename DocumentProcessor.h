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





/**
 * wordsEqualityFunction
 * Function to pass into the insert method in the words AVL tree. It
 * increases the counter in the WordNode by 1 for the given document.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
//void wordsEqualityFunction(WordNode& newItem, TreeNode<WordNode>*& curPtr) {
//    curPtr->getData().addDoc(newItem.getDocuments().getRootData());
//    //curPtr->getData().addDoc(newItem.getDocuments()[0]);//temp.getDocLocation(newItem.getDocuments()[0]));
//}





class DocumentProcessor {
private:
    AVLTree<std::string> stopWords;
    Index index;



    /**
     * cleanAndAdd Method
     * Cleans and adds data to the AVL tree
     * @param doc The document to clean and store
     * @param docName The name of the document to store
     */
    void cleanAndAdd(rapidjson::Document*& doc, std::string& docName);


    /**
     * storeStopWords Method
     * Given a filename
     * @param filename The name of the file to read the stop words from
     */
    void storeStopWords(const std::string& filename);


    /**
     * processDocuments Helper Method
     * Reads in the files given a directory
     * @param directory The name of the directory to parse files from
     * @param numFiles THe number of files read in
     * @return The number of files read in total.
     */
    int processDocumentsHelper(const std::string& directory, int numFiles);



public:
    /**
     * processDocuments Method
     * Accepts a directory name to parse .json documents from
     * @param directory The name of the directory to parse files from
     * @return The stored index object containing the information from
     *         the parsed datafiles
     */
    void processDocuments(const std::string& directory);

    /**
     * search Method
     * Accepts a word to search for in the Words tree and returns the
     * WordNode containing that word
     * @param word The word to search for
     * @return A WordNode containing that word
     */
    WordNode& search(std::string word);
};




#endif // INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H