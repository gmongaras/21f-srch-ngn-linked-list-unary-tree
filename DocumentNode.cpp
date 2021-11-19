#include "DocumentNode.h"
#include <iostream>



/************************
 **    Constructors    **
 ***********************/
DocumentNode::DocumentNode() {
    documentName = "";
    frequency = 0;
}
DocumentNode::DocumentNode(const std::string &name, int freq) {
    documentName = name;
    frequency = freq;
}
DocumentNode::DocumentNode(const DocumentNode &node) {
    documentName = node.documentName;
    frequency = node.frequency;
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



/******************************
 **    Get Value Methods     **
 *****************************/
std::string DocumentNode::getName() const {
    return documentName;
}

int DocumentNode::getFreq() const {
    return frequency;
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
    out << "Name: " << node.documentName << "   " << "Word Frequency: " << node.frequency << std::endl;
    return out;
}