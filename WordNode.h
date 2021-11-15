#ifndef INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H


#include <vector>
#include <string>
#include <stdexcept>


// Stores information on words read from the JSON file
class WordNode {
private:
    std::string word; // The word stored in this node
    std::vector<std::string> documents; // The documents which contain this word
    std::vector<int> counts; // The number of times each document contains this word


public:
    /**
     * Constructors
     */
    WordNode();
    WordNode(std::string newWord);
    WordNode(std::string newWord, std::string doc);

    /**
     * addDoc Method
     * @param Doc The document to add to the vector
     */
    void addDoc(std::string& Doc);

    /**
     * getDocLocation Method
     * @param Doc The document to search for
     * @return The index of the given document name, -1 if not found
     */
    int getDocLocation(std::string& Doc);

    /**
     * incrementDoc
     * Increment the counter for an index of a given doc. If the
     * index is -1, add to the last doc added
     * @param index The index to increment
     */
    void incrementDoc(int index);

    /**
     * getWord Method
     * Returns the word stored in this object
     * @retrun The stored word in this object
     */
    std::string& getWord();

    /**
     * getDocuments Method
     * Returns the word stored in this object
     * @retrun The stored word in this object
     */
    std::vector<std::string>& getDocuments();

    /**
     * Comparison Operators
     */
    bool operator==(WordNode& w);
    bool operator==(std::string& w);
    bool operator>(WordNode& w);
    bool operator>(std::string& w);
    bool operator<(WordNode& w);
    bool operator<(std::string& w);

    /**
     * Overloaded Assignment Operator
     */
    WordNode& operator=(const WordNode& w);
};




/************************
 **    Constructors    **
 ***********************/
WordNode::WordNode() {
    word = "";
}
WordNode::WordNode(std::string newWord) {
    word = newWord;
}
WordNode::WordNode(std::string newWord, std::string doc) {
    word = newWord;
    documents.push_back(doc);
    counts.push_back(1);
}



/*************************
 **    addDoc Method    **
 ************************/
void WordNode::addDoc(std::string &Doc) {
    // If the document is already in the list, increment it
    for (int i = 0; i < documents.size(); i++) {
        if (documents[i] == Doc) {
            counts[i]++;
            return;
        }
    }

    // If the document is not in the vector, add it
    documents.push_back(Doc);
    counts.push_back(1);
}



/**************************
 **    getDocLocation    **
 *************************/
int WordNode::getDocLocation(std::string &Doc) {
    for (int i = 0; i < documents.size(); i++) {
        if (documents[i] == Doc) {
            return i;
        }
    }

    return -1;
}



/*******************************
 **    incrementDoc Method    **
 ******************************/
void WordNode::incrementDoc(int index) {
    // If the index is too large or small, throw an error
    if ((index >= documents.size() && index != -1) || index < -1) {
        throw std::runtime_error("Index out of array bounds");
    }

    // If the index is -1, increment the last item in the vector
    if (index == -1) {
        counts[counts.size()-1]++;
        return;
    }

    counts[index]++;
}


/*******************
 **    getWord    **
 ******************/
std::string& WordNode::getWord() {
    return word;
}



/*******************************
 **    getDocuments Method    **
 ******************************/
std::vector<std::string>& WordNode::getDocuments() {
    return documents;
}



/********************************
 **    Comparison Operators    **
 *******************************/
bool WordNode::operator==(WordNode &w) {
    return word==w.word;
}
bool WordNode::operator==(std::string& w) {
    return word==w;
}
bool WordNode::operator<(WordNode &w) {
    return word<w.word;
}
bool WordNode::operator<(std::string &w) {
    return word>w;
}
bool WordNode::operator>(WordNode &w) {
    return word>w.word;
}
bool WordNode::operator>(std::string &w) {
    return word>w;
}



/******************************************
 **    Overloaded Assignment Operator    **
 *****************************************/
WordNode &WordNode::operator=(const WordNode &w) {
    word = w.word;
    for (int i = 0; i < w.documents.size(); i++) {
        documents.push_back(w.documents[i]);
        counts.push_back(w.counts[i]);
    }

    return *this;
}


#endif //INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H
