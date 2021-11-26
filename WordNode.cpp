#include "WordNode.h"
#include <fstream>
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
}
WordNode::WordNode(std::string& newWord) {
    word = newWord;
}
WordNode::WordNode(std::string& newWord, DocumentNode& doc) {
    word = newWord;
    docs.insert(doc, &docsEqualityFunction);
}
WordNode::WordNode(WordNode &node) {
    word = node.word;
    docs = node.docs;
}



/*************************
 **    addDoc Method    **
 ************************/
void WordNode::addDoc(std::string &Doc, std::string& ID, int length) {
    // Temporary node to insert
    DocumentNode temp = DocumentNode(Doc, 1, ID, length);

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
    DocumentNode temp = DocumentNode(Doc, 1, "", 0);

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
    out << node.word.c_str() << ":";

    node.docs.fstreamLevelOrder(out, ",");
    //node.docs.printTree2();

    return out;
}