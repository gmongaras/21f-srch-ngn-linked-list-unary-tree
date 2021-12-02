#include "DocumentNode.h"
#include <iostream>
#include <math.h>



/************************
 **    Constructors    **
 ***********************/
DocumentNode::DocumentNode() {
    fileName = "";
    frequency = 0;
    documentID = "";
    docLength = 0;
    title = "";
    author = "";
    date = "";

    partDel = "~~";
}
DocumentNode::DocumentNode(const std::string& name, int freq, std::string ID, int length, std::string& Title, std::string& Author, std::string& Date) {
    fileName = name;
    frequency = freq;
    documentID = std::move(ID);
    docLength = length;
    title = Title;
    author = Author;
    date = Date;

    partDel = "~~";
}
DocumentNode::DocumentNode(const DocumentNode &node) {
    fileName = node.fileName;
    frequency = node.frequency;
    documentID = node.documentID;
    docLength = node.docLength;
    title = node.title;
    author = node.author;
    date = node.date;

    partDel = "~~";
}




/********************************
 **    Change Value Methods    **
 *******************************/
void DocumentNode::changeName(const std::string &name) {
    fileName = name;
}

void DocumentNode::changeFrequency(const int freq) {
    frequency = freq;
}

void DocumentNode::changeID(const std::string& ID) {
    documentID = ID;
}

void DocumentNode::changeLength(const int length) {
    docLength = length;
}

void DocumentNode::changeTitle(const std::string &Title) {
    title = Title;
}

void DocumentNode::changeAuthor(const std::string &Author) {
    author = Author;
}

void DocumentNode::changeDate(const std::string &Date) {
    date = Date;
}



/******************************
 **    Get Value Methods     **
 *****************************/
std::string DocumentNode::getName() const {
    return fileName;
}

int DocumentNode::getFreq() const {
    return frequency;
}

std::string DocumentNode::getID() const {
    return documentID;
}

int DocumentNode::getLength() const {
    return docLength;
}

std::string DocumentNode::getTitle() const {
    return title;
}

std::string DocumentNode::getAuthor() const {
    return author;
}

std::string DocumentNode::getDate() const {
    return date;
}



/**************************************
 **    getRelevancyRanking Method    **
 *************************************/
float DocumentNode::getRelevancyRanking() const {
    return std::pow(((float)frequency), (float)2)/(float)docLength;
}



/******************************
 **    Equality Operators    **
 *****************************/
bool DocumentNode::operator==(const DocumentNode &node) {
    return fileName == node.fileName;
}
bool DocumentNode::operator==(const std::string &name) {
    return fileName == name;
}
bool DocumentNode::operator!=(const DocumentNode &node) {
    return fileName != node.fileName;
}
bool DocumentNode::operator!=(const std::string &name) {
    return fileName != name;
}



/********************************
 **    Comparison Operators    **
 *******************************/
bool DocumentNode::operator<(const DocumentNode &node) {
    return fileName < node.fileName;
}
bool DocumentNode::operator<(const std::string &name) {
    return fileName < name;
}
bool DocumentNode::operator>(const DocumentNode &node) {
    return fileName > node.fileName;
}
bool DocumentNode::operator>(const std::string &name) {
    return fileName > name;
}
bool DocumentNode::operator<(const DocumentNode &node) const {
    return fileName < node.fileName;
}
bool DocumentNode::operator<(const std::string &name) const {
    return fileName < name;
}
bool DocumentNode::operator>(const DocumentNode &node) const {
    return fileName > node.fileName;
}
bool DocumentNode::operator>(const std::string &name) const {
    return fileName > name;
}



/******************************************
 **    Overloaded Assignment Operator    **
 *****************************************/
DocumentNode &DocumentNode::operator=(std::string &str) {
    // tokenize the given string into document node parts
    std::vector<std::string> tokenizedParts = tokStr(str, partDel, 6);

    // Add the values to the document node
    fileName = std::string(tokenizedParts[0]);
    frequency = stoi(tokenizedParts[1]);
    documentID = std::string(tokenizedParts[2]);
    docLength = stoi(tokenizedParts[3]);
    title = std::string(tokenizedParts[4]);
    author = std::string(tokenizedParts[5]);
    date = std::string(tokenizedParts[6]);

    return *this;
}



/*****************************
 **    updateFreq Method    **
 ****************************/
int DocumentNode::updateFreq() {
    frequency++;
    return frequency;
}



/***********************************************
 **    Overload OStream Insertion Operator    **
 ***********************************************/
std::ostream& operator<< (std::ostream& out, const DocumentNode& node) {
    //out << "Name: " << node.documentName << "   " << "Word Frequency: " << node.frequency << "   Document ID: " << node.documentID;
    out << node.title << " " << node.author << " " << node.date;
    //out << node.fileName << " " << node.frequency << " " << node.documentID << " " << node.docLength << " " << node.getRelevancyRanking();
    return out;
}



/***********************************************
 **    Overload FStream Insertion Operator    **
 ***********************************************/
std::fstream& operator<< (std::fstream& out, const DocumentNode& node) {
    //out << "Name: " << node.documentName << "   " << "Word Frequency: " << node.frequency << "   Document ID: " << node.documentID;
    out << node.fileName << node.partDel << node.frequency << node.partDel << node.documentID << node.partDel << node.docLength << node.partDel << node.title << node.partDel << node.author << node.partDel << node.date;
    //out << node.fileName << " " << node.frequency << " " << node.documentID << " " << node.docLength << " " << node.getRelevancyRanking();
    return out;
}