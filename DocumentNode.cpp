#include "DocumentNode.h"



/************************
 **    Constructors    **
 ***********************/
DocumentNode::DocumentNode() {
    documentName = "";
    frequency = 0;
}
DocumentNode::DocumentNode(const std::string &name, const int freq) {
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
std::string &DocumentNode::getName() {
    return documentName;
}

int DocumentNode::getFreq() {
    return frequency;
}



/*****************************
 **    updateFreq Method    **
 ****************************/
int DocumentNode::updateFreq() {
    frequency++;
    return frequency;
}