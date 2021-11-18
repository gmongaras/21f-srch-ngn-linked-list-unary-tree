#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H


#include <string>
#include <filesystem>
#include <experimental/filesystem>


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/pointer.h"
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <time.h>
#include "myDocument.h"
#include "WordNode.h"
#include "TreeNode.h"
#include <unistd.h>
#include "./porter2_stemmer/porter2_stemmer.cpp"
#include "dirent.h"
#include "sys/stat.h"
//#include "boost/filesystem.hpp"
//#include "boost/range/iterator_range.hpp"

namespace fs = std::experimental::filesystem;





/**
 * wordsEqualityFunction
 * Function to pass into the insert method in the words AVL tree. It
 * increases the counter in the WordNode by 1 for the given document.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void wordsEqualityFunction(WordNode& newItem, TreeNode<WordNode>*& curPtr) {
    curPtr->getData().addDoc(newItem.getDocuments()[0]);//temp.getDocLocation(newItem.getDocuments()[0]));
}

/**
 * stopWordsEqualityFunction
 * Function to pass into the insert method in the stopWords AVL tree.
 * Since we don't need to do anything for equality, this function
 * does nothing.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void stopWordsEqualityFunction(std::string& newItem, TreeNode<std::string>*& curPtr) {
    return;
}





class DocumentProcessor {
private:
    AVLTree<std::string> stopWords;
    AVLTree<WordNode> Words;



    /**
     * cleanAndAdd Method
     * Cleans and adds data to the AVL tree
     * @param doc The document to clean and store
     */
    void cleanAndAdd(rapidjson::Document* doc, std::string& docName);


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
     */
    void processDocumentsHelper(const std::string& directory);



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
    WordNode search(std::string word);
};







/******************************
 **    cleanAndAdd Method    **
 *****************************/
void DocumentProcessor::cleanAndAdd(rapidjson::Document *doc, std::string& docName) {
    // Get the text from the document
    rapidjson::Value& text = (*doc)["text"];
    std::string textStr = text.GetString();

    // Storage used to store each word in the sequence
    std::string word;


    for (int i = 0; i < text.GetStringLength(); i++) {
        // Store the character
        char c = textStr[i];

        // If the character is a space and not another type of punctuation,
        // clean it and add it to the AVL tree.
        if (c == ' ') {
            // If the word is empty, continue the loop
            if (word.empty()) {
                continue;
            }

            // If the word is not empty, stem it and add it
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);

            // If the word is a stop word, don't add it to the words tree
            if (stopWords.hasNode(word) == true) {
                word.clear();
                continue;
            }
            // If the word is fine, add it to the words tree
            else {
                WordNode temp(word, docName);
                Words.insert(temp, &wordsEqualityFunction);
                word.clear();
            }
        }


        // If the character is not punctuation, add it to word
        else if (std::ispunct(c) == false || c == '\'') {
            word.push_back(c);
        }
    }

    // Add the final word
    WordNode temp(word, docName);
    Words.insert(temp, &wordsEqualityFunction);
    word.clear();
}



/**************************
 **    storeStopWords    **
 *************************/
void DocumentProcessor::storeStopWords(const std::string &filename) {
    // Create a pointer to the file object
    std::fstream file;

    // Variable to hold each line in the file
    char* origLine = new char[50];

    // Open the file
    file.open(filename);

    // If the file is open, read the stop words into the AVL Tree
    if (file.is_open()) {
        while (file.eof() == false) {
            // Get a line from the file
            file.getline(origLine, 50, ',');

            // Store the line in the AVLTree
            std::string temp(origLine);
            stopWords.insert(temp, &stopWordsEqualityFunction);
        }
    }


    // Close the file and free the memory
    delete [] origLine;
    file.close();
}



/*****************************************
 **    processDocumentsHelper Method    **
 ****************************************/
void DocumentProcessor::processDocumentsHelper(const std::string &directory) {
    FILE* filePointer; // Holds each file


    // Initialize variables to start file iteraton
    DIR *dir = opendir(directory.data());
    struct dirent *ent;
    struct stat path_stat;
    class stat st;


    char* readBuffer = new char[65536]; // The buffer

    // Iterate over all documents in the directory
    while ((ent = readdir(dir)) != NULL) {
        // Gett he file name
        std::string fileName = std::string(ent->d_name);
        std::string fullFileName = directory + "/" + fileName;


        // Check if the file is a directory
        if (fileName == "." || fileName == "..") {
            continue;
        }
        else if (stat(fullFileName.c_str(), &st) == -1)
            continue;
        else if ((st.st_mode & S_IFDIR) != 0) {
            // If the file is a directory, iterate over all those files
            processDocumentsHelper(directory+"/"+fileName);
            continue;
        }


        // Open the file for reading
        filePointer = fopen(fullFileName.c_str(), "rb");

        // If the file is not opened, skip it
        if (filePointer == nullptr) {
            std::cout << fileName << std::endl;
            continue;
        }

        // Read the JSON from the file into the document
        rapidjson::FileReadStream* inputStream = new rapidjson::FileReadStream(filePointer, readBuffer, sizeof(readBuffer));
        //        myDocument<rapidjson::UTF8<>> *doc = new myDocument<rapidjson::UTF8<>>;
        //        AVLTree<std::string>* AVL = new AVLTree<std::string>;
        //        doc->ParseStream(*inputStream, AVL);
        rapidjson::Document *doc = new rapidjson::Document;
        doc->ParseStream(*inputStream);


        // clean and add the word to the tree
        cleanAndAdd(doc, fullFileName);



        // Reset the pointers and free the memory
        delete doc;
        delete inputStream;
        fclose(filePointer);
        //delete filePointer;
        memset(readBuffer, 0, sizeof(readBuffer));
    }


    // Free the memory used to read the files
    delete [] readBuffer;
    closedir(dir);
    delete ent;
}

















/****************************
 **    processDocuments    **
 ***************************/
void DocumentProcessor::processDocuments(const std::string& directory) {
    // Read in the stop words.
    // Note the stop words list was found at: https://www.link-assistant.com/seo-stop-words.html
    std::string stopWordFilename = "../storage/stopWords2.txt";
    storeStopWords(stopWordFilename);




    time_t timer;
    struct tm y2k = {0};
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    double original = time(&timer);  /* get current time; same as: timer = time(NULL)  */

    // Process the documents
    processDocumentsHelper(directory);


    std::cout << "Processing Time: " << time(&timer)-original << " seconds" << std::endl;
}



/******************
 **    search    **
 *****************/
WordNode DocumentProcessor::search(std::string word) {
    // Stem the word
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);

    // Return the word
    WordNode temp(word);
    return Words.getNode(temp);
}



#endif // INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H