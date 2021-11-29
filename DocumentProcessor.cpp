#include "DocumentProcessor.h"
#include <chrono>
#include <algorithm>



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



/**
 * wordCountsEqualityFunction
 * Function to pass into the insert method in the wordCounts AVL tree.
 * This function increases
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void wordCountsEqualityFunction(DocumentProcessor::wordToCount& newItem, TreeNode<DocumentProcessor::wordToCount>*& curPtr) {
    curPtr->getData().increaseCount();
}






/*************************
 **    tokStr Method    **
 ************************/
std::vector<std::string> DocumentProcessor::tokStr(std::string &str, char tok) {
    // Vector to hold the tokenized string
    std::vector<std::string> tokenizedString;

    // Temporary string to hold each substring
    std::string substr;

    // Iterate over all values in the string
    for (char i : str) {
        // If the current character is the token, add the substring to the vector
        if (i == tok) {
            if (!substr.empty()) {
                tokenizedString.emplace_back(substr);
            }

            // Clear the substring
            substr.clear();
            continue;
        }

        // Add the next character to the substring
        substr += i;
    }

    // Add the final substring to the vector
    tokenizedString.emplace_back(substr);

    // Return the vector of substring
    return tokenizedString;
}





/******************************
 **    cleanAndAdd Method    **
 *****************************/
void DocumentProcessor::cleanAndAdd(rapidjson::Document*& doc, std::string& docName, int& numWords) {
    // Get the informations from the document
    rapidjson::Value& text = (*doc)["text"];
    std::string textStr = text.GetString();
    std::string ID = (*doc)["uuid"].GetString();
    std::string title = (*doc)["title"].GetString();
    std::string author = (*doc)["author"].GetString();
    std::string date = (*doc)["published"].GetString();

    // Create a node holding all the document information
    DocumentNode docNode(docName, 1, ID, text.GetStringLength(), title, author, date);

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

            // If the word is a stop word or whitespace, don't add it to the words tree
            if (stopWords.hasNode(word) == true || (int)word[0] < 32) {
                word.clear();
                continue;
            }
            // If the word is fine, add it to the words tree and the wordToCount tree
            else {
                numWords++;
                WordNode temp(word, docNode);
                //Words.insert(temp, &wordsEqualityFunction);
                index.addWord(temp);
                DocumentProcessor::wordToCount temp2(word);
                wordCounts.insert(temp2, &wordCountsEqualityFunction);
                word.clear();
            }
        }


        // If the character is not punctuation, add it to word
        else if (std::ispunct(c) == false || c == '\'') {
            word.push_back(c);
        }
    }

    // Add the final word
    WordNode temp(word, docNode);
    //Words.insert(temp, &wordsEqualityFunction);
    index.addWord(temp);
    word.clear();






    // Get all people from the document
    auto people = (*doc)["entities"]["persons"].GetArray();

    // If there is information on the people in the document, store it
    if (!people.Empty()) {
        // Add each name to the hash map
        for (int i = 0; i < people.Size(); i++) {
            std::string person = people[i]["name"].GetString();
            WordNode temp(person, docNode);
            index.addPerson(person, temp);
        }
    }






    // Get all organizations from the document
    auto orgs = (*doc)["entities"]["organizations"].GetArray();

    // If there is information on the organizations in the document, store it
    if (!orgs.Empty()) {
        // Add each organization to the hash map
        for (int i = 0; i < orgs.Size(); i++) {
            std::string org = orgs[i]["name"].GetString();
            WordNode temp(org, docNode);
            index.addOrg(org, temp);
        }
    }










//    // Store the information on the organizations from the document
//    std::string organizations = (*doc)["organizations"].GetString();
//
//    // If there is information on the people in the document, store it
//    if (!people.empty()) {
//        // Breakup the people string into a vector of each person
//        std::vector<std::string> peopleVec = tokStr(people, ',');
//
//        // Iterate over all values in the vector
//        for (std::string person : peopleVec) {
//            // Add the person to the HashMap
//            DocumentNode tempNode(docName, 1, ID, text.GetStringLength());
//            WordNode temp(person, tempNode);
//            index.addPerson(person, temp);
//        }
//    }
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
void DocumentProcessor::processDocumentsHelper(const std::string &directory, int& numFiles, int& numWords) {
    FILE* filePointer; // Holds each file


    // Initialize variables to start file iteraton
    DIR *dir = opendir(directory.data());
    struct dirent *ent;
    struct stat path_stat;
    class stat st;


    char* readBuffer = new char[228362]; // The buffer
    int readBufferSize = sizeof(readBuffer);

    // If the file isn't open, stop the program
    if (dir == nullptr) {
        throw std::runtime_error("File not open");
    }

    // Iterate over all documents in the directory
    while ((ent = readdir(dir)) != nullptr) {
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
            processDocumentsHelper(directory+"/"+fileName, numFiles, numWords);
            continue;
        }

        // Increase the counter and update the display
        numFiles++;
        if (numFiles%1000 == 0) {
            std::cout << "Files read: " << numFiles << std::endl;
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
            cleanAndAdd(doc, fullFileName, numWords);
        }



        // Reset the pointers and free the memory
        delete doc;
        delete inputStream;
        fclose(filePointer);
        memset(readBuffer, 0, readBufferSize);
    }


    // Free the memory used to read the files
    delete [] readBuffer;
    closedir(dir);
    delete ent;
}

















/*******************************
 **    Default Constructor    **
 ******************************/
DocumentProcessor::DocumentProcessor() {
    NUMFILES = 0;
    NUMWORDS = 0;
}



/*****************************
 **    clearIndex Method    **
 ****************************/
void DocumentProcessor::clearIndex() {
    index.clearIndex();
}



/***************************
 **    getStats Method    **
 **************************/
std::vector<float> DocumentProcessor::getStats() {
    return std::vector<float>({(float)NUMFILES, (float)NUMWORDS/(float)NUMFILES, (float)NUMWORDS, (float)index.getNumUniqueOrgs(), (float)index.getNumUniquePeople(), (float)timeToParse.count()});
}



/******************************
 **    getTopFifty Method    **
 *****************************/
std::vector<DocumentProcessor::wordToCount> DocumentProcessor::getTopFifty() {
    // Get all words from the wordCounts tree
    std::vector<DocumentProcessor::wordToCount> counts = wordCounts.getInOrderVec();

    return std::vector<DocumentProcessor::wordToCount>(counts.begin(), counts.begin() + std::min((int)counts.size(), 50));
}



/****************************
 **    processDocuments    **
 ***************************/
void DocumentProcessor::processDocuments(const std::string& directory) {
    // Read in the stop words.
    // Note the stop words list was found at: https://www.link-assistant.com/seo-stop-words.html
    std::string stopWordFilename = "../storage/stopWords2.txt";
    storeStopWords(stopWordFilename);


    // Start timing the time it takes to read all files
    auto start = std::chrono::high_resolution_clock::now();


    // Process the documents
    processDocumentsHelper(directory, NUMFILES, NUMWORDS);


    // Get the end time
    auto stop = std::chrono::high_resolution_clock::now();

    // Store the final difference in time
    timeToParse = stop - start;
}



/**********************
 **    searchWord    **
 *********************/
WordNode DocumentProcessor::searchWord(std::string word) {
    // Stem and lowercase the word
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // If the word is "", return an empty WordNode to display an error message
    if (word.empty()) {
        WordNode temp;
        return temp;
    }

    // Return the results of the query
    return index.getWord(word);


    //stopWords.saveTree(std::string("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/21f-srch-ngn-linked-list-unary-tree/storage/stop.csv"));
    //Words.saveTree(std::string("/mnt/c/Users/gabri/Documents/SMU/Classes/Fall 2021/CS 2341 (Data Structures)/Projects/Project 5/21f-srch-ngn-linked-list-unary-tree/storage/tree.csv"));
    //WordNode temp(word);
    //return Words.getNode(temp);
}



/************************
 **    searchPeople    **
 ***********************/
WordNode DocumentProcessor::searchPeople(std::string person) {
    // If the person is "", return an empty WordNode to display an error message
    if (person.empty()) {
        WordNode temp;
        return temp;
    }

    // Return the results of the query
    return index.getPeopleDocs(person);
}



/**********************
 **    searchOrgs    **
 *********************/
WordNode DocumentProcessor::searchOrgs(std::string org) {
    // If the person is "", return an empty WordNode to display an error message
    if (org.empty()) {
        WordNode temp;
        return temp;
    }

    // Return the results of the query
    return index.getOrgDocs(org);
}