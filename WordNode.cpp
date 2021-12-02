#include "WordNode.h"
#include <iostream>

/**
 * docsEqualityFunction
 * Function to pass into the insert method in the docs AVL tree. It
 * increases the counter in the DocumentNode by 1 for the given document.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void docsEqualityFunction(DocumentNode& newItem, TreeNode<DocumentNode>*& curPtr) {
    curPtr->getData().updateFreq();
    //curPtr->getData().addDoc(newItem.getDocuments()[0]);//temp.getDocLocation(newItem.getDocuments()[0]));
}


/************************
 **    Constructors    **
 ***********************/
WordNode::WordNode() {
    word = "";
    wordDocDel = "::|";
    docDel = "`|`";
}
WordNode::WordNode(std::string& newWord) {
    word = newWord;
    wordDocDel = "::|";
    docDel = "`|`";
}
WordNode::WordNode(std::string& newWord, DocumentNode& doc) {
    word = newWord;
    docs.insert(doc, &docsEqualityFunction);
    wordDocDel = "::|";
    docDel = "`|`";
}
WordNode::WordNode(WordNode &node) {
    word = node.word;
    docs = node.docs;
    wordDocDel = "::|";
    docDel = "`|`";
}



/*************************
 **    addDoc Method    **
 ************************/
void WordNode::addDoc(std::string &Doc, std::string& ID, int length, std::string& title, std::string& author, std::string& date) {
    // Temporary node to insert
    DocumentNode temp = DocumentNode(Doc, 1, ID, length, title, author, date);

    // Try inserting the document, if it is already in the
    // tree, increment the value.
    docs.insert(temp, &docsEqualityFunction);
}
void WordNode::addDoc(DocumentNode &Doc) {
    // Try inserting the document, if it is already in the
    // tree, increment the value.
    docs.insert(Doc, &docsEqualityFunction);
}

/**************************
 **    getDocLocation    **
 *************************/
DocumentNode& WordNode::getDoc(std::string &Doc) {
    // Temporary node to look for
    std::string t;
    DocumentNode temp = DocumentNode(Doc, 1, t, 0, t, t, t);

    // Try finding the document, if the node is found,
    // return the
    return docs.getNode(temp);
}
DocumentNode& WordNode::getDoc(DocumentNode &Doc) {
    // Try finding the document, if the node is found,
    // return the
    return docs.getNode(Doc);
}



/*******************************
 **    incrementDoc Method    **
 ******************************/
void WordNode::incrementDoc(std::string& Doc) {
    // Try finding the document in the tree. If it's found, increment it
    getDoc(Doc).updateFreq();
}

void WordNode::incrementDoc(DocumentNode& Doc) {
    // Try finding the document in the tree. If it's found, increment it
    getDoc(Doc).updateFreq();
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
AVLTree<DocumentNode>& WordNode::getDocuments() {
    return docs;
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
WordNode &WordNode::operator=(WordNode &w) {
    word = w.word;
    docs = w.docs;

    return *this;
}
WordNode& WordNode::operator=(std::string& str) {
    // Breakup the string into word and documents
    std::vector<std::string> tokenizedWordDocs = tokStr(str, wordDocDel, 1);

    // Store the word from the vector
    word = std::string(tokenizedWordDocs[0]);

    // If the tokenized string has more than 1 value, store the other values
    // as documents
    if (tokenizedWordDocs.size() > 1) {
        // Store the second part of the tokenized string
        std::string documents = tokenizedWordDocs[1];

        // Split up the documents by the docDel delimiter
        std::vector<std::string> tokenizedDocs = tokStr(documents, docDel, -1);

        // Add and store each document
        for (std::string& doc : tokenizedDocs) {
            DocumentNode temp;
            temp = doc;
            docs.insert(temp, &docsEqualityFunction);
        }
    }

    return *this;
}



/***********************************************
 **    Overload OStream Insertion Operator    **
 **********************************************/
std::ostream& operator<< (std::ostream& out, const WordNode& node) {
    out << "Word: " << node.word << std::endl;

    node.docs.printTree2();

    return out;
}



/***********************************************
 **    Overload FStream Insertion Operator    **
 **********************************************/
std::fstream& operator<< (std::fstream& out, const WordNode& node) {
    out << node.word.c_str() << node.wordDocDel;

    node.docs.fstreamLevelOrder(out, node.docDel);
    //node.docs.printTree2();

    return out;
}