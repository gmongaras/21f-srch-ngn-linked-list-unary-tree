#include "DocumentNode.h"
#include <iostream>



/************************
 **    Constructors    **
 ***********************/
DocumentNode::DocumentNode() {
    documentName = "";
    frequency = 0;
    documentID = "";
    docLength = 0;
}
DocumentNode::DocumentNode(const std::string &name, int freq, std::string ID, int length) {
    documentName = name;
    frequency = freq;
    documentID = std::move(ID);
    docLength = length;
}
DocumentNode::DocumentNode(const DocumentNode &node) {
    documentName = node.documentName;
    frequency = node.frequency;
    documentID = node.documentID;
    docLength = node.docLength;
}




/********************************
 **    Change Value Methods    **
 *******************************/
void DocumentNode::changeName(const std::string &name) {
    documentName = name;
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



/******************************
 **    Get Value Methods     **
 *****************************/
std::string DocumentNode::getName() const {
    return documentName;
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



/**************************************
 **    getRelevancyRanking Method    **
 *************************************/
float DocumentNode::getRelevancyRanking() const {
    return (float)frequency/(float)docLength;
}



/******************************
 **    Equality Operators    **
 *****************************/
bool DocumentNode::operator==(const DocumentNode &node) {
    return documentName == node.documentName;
}
bool DocumentNode::operator==(const std::string &name) {
    return documentName == name;
}
bool DocumentNode::operator!=(const DocumentNode &node) {
    return documentName != node.documentName;
}
bool DocumentNode::operator!=(const std::string &name) {
    return documentName != name;
}



/********************************
 **    Comparison Operators    **
 *******************************/
bool DocumentNode::operator<(const DocumentNode &node) {
    return documentName < node.documentName;
}
bool DocumentNode::operator<(const std::string &name) {
    return documentName < name;
}
bool DocumentNode::operator>(const DocumentNode &node) {
    return documentName > node.documentName;
}
bool DocumentNode::operator>(const std::string &name) {
    return documentName > name;
}



/*****************************
 **    updateFreq Method    **
 ****************************/
int DocumentNode::updateFreq() {
    frequency++;
    return frequency;
}



/**********************************************
 **    Overload Stream Insertion Operator    **
 **********************************************/
std::ostream& operator<< (std::ostream& out, const DocumentNode& node) {
    //out << "Name: " << node.documentName << "   " << "Word Frequency: " << node.frequency << "   Document ID: " << node.documentID;
    out << node.documentName << " " << node.frequency << " " << node.documentID << " " << node.docLength;
    return out;
}