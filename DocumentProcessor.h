#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H


#include <string>
#include<bits/stdc++.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/pointer.h"
#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <time.h>
#include "TreeNode.h"
#include <unistd.h>
#include "./porter2_stemmer/porter2_stemmer.cpp"
#include "dirent.h"
#include "sys/stat.h"
#include "Index.h"





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


/******************************
 **    cleanAndAdd Method    **
 *****************************/
void DocumentProcessor::cleanAndAdd(rapidjson::Document*& doc, std::string& docName) {
    // Get the text from the document
    rapidjson::Value& text = (*doc)["text"];
    std::string ID = (*doc)["uuid"].GetString();
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

            // If the word is not empty, stem it, lowercase it, and add it
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            // If the word is a stop word, don't add it to the words tree
            if (stopWords.hasNode(word) == true) {
                word.clear();
                continue;
            }
            // If the word is fine, add it to the words tree
            else {
                WordNode temp(word, docName, ID);
                //Words.insert(temp, &wordsEqualityFunction);
                index.addWord(temp);
                word.clear();
            }
        }


        // If the character is not punctuation, add it to word
        else if (std::ispunct(c) == false || c == '\'') {
            word.push_back(c);
        }
    }

    // Add the final word
    WordNode temp(word, docName, ID);
    //Words.insert(temp, &wordsEqualityFunction);
    index.addWord(temp);
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
int DocumentProcessor::processDocumentsHelper(const std::string &directory, int numFiles) {
    FILE* filePointer; // Holds each file


    // Initialize variables to start file iteraton
    DIR *dir = opendir(directory.data());
    struct dirent *ent;
    struct stat path_stat;
    class stat st;


    char* readBuffer = new char[228362]; // The buffer
    int readBufferSize = sizeof(readBuffer);

    // If the file isn't open, stop the program
    if (dir == NULL) {
        throw std::runtime_error("File not open");
    }

    // Iterate over all documents in the directory
    while ((ent = readdir(dir)) != NULL) {
        // Increase the counter and update the display
        numFiles++;
        if (numFiles%1000 == 0) {
            std::cout << "Files read: " << numFiles << std::endl;
        }


        // Get the file name
        std::string fileName = std::string(ent->d_name);
        std::string fullFileName = directory + "/" + fileName;


        // Check if the file is a directory and ends in .json
        if (fileName == "." || fileName == "..") {// || fileName[size-4] != 'j' || fileName[size-3] != 's' && fileName[size-2] != 'o' && fileName[size-1] != 'n') {
            continue;
        }
        else if (stat(fullFileName.c_str(), &st) == -1)
            continue;
        else if ((st.st_mode & S_IFDIR) != 0) {
            // If the file is a directory, iterate over all those files
            numFiles = processDocumentsHelper(directory+"/"+fileName, numFiles);
            continue;
        }


        // Open the file for reading
        filePointer = fopen(fullFileName.c_str(), "rb");

        // If the file is not opened, skip it
        if (filePointer == nullptr) {
            std::cout << "File could not be opened: " << fileName << std::endl;
            continue;
        }

        // Read the JSON from the file into the document
        rapidjson::FileReadStream* inputStream = new rapidjson::FileReadStream(filePointer, readBuffer, readBufferSize);
        //        myDocument<rapidjson::UTF8<>> *doc = new myDocument<rapidjson::UTF8<>>;
        //        AVLTree<std::string>* AVL = new AVLTree<std::string>;
        //        doc->ParseStream(*inputStream, AVL);
        rapidjson::Document *doc = new rapidjson::Document;
        doc->ParseStream(*inputStream);


        // If the file is open, clean and add the word to the tree
        if (doc->IsNull() == false){
            cleanAndAdd(doc, fileName);
        }



        // Reset the pointers and free the memory
        delete doc;
        delete inputStream;
        fclose(filePointer);
        //delete filePointer;
        memset(readBuffer, 0, readBufferSize);
    }


    // Free the memory used to read the files
    delete [] readBuffer;
    closedir(dir);
    delete ent;


    // Return the number of files read in
    return numFiles;
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
    processDocumentsHelper(directory, 0);


    std::cout << "Processing Time: " << time(&timer)-original << " seconds" << std::endl;
}



/******************
 **    search    **
 *****************/
WordNode& DocumentProcessor::search(std::string word) {
    // Stem and lowercase the word
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Return the word
    return index.getWord(word);
    //stopWords.saveTree(std::string("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/21f-srch-ngn-linked-list-unary-tree/storage/stop.csv"));
    //Words.saveTree(std::string("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/21f-srch-ngn-linked-list-unary-tree/storage/tree.csv"));
    //WordNode temp(word);
    //return Words.getNode(temp);
}


#endif // INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTPROCESSOR_H