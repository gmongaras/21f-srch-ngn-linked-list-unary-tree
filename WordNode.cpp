
#include "WordNode.h"

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
    docs.emplace_back(DocumentNode(doc, 1));
}



/*************************
 **    addDoc Method    **
 ************************/
void WordNode::addDoc(std::string &Doc) {
    // If the document is already in the list, increment it
    for (int i = 0; i < docs.size(); i++) {
        if (docs[i] == Doc) {
            docs[i].updateFreq();
            return;
        }
    }

    // If the document is not in the vector, add it
    docs.emplace_back(DocumentNode(Doc, 1));
}
void WordNode::addDoc(DocumentNode &Doc) {
    // If the document is already in the list, increment it
    for (int i = 0; i < docs.size(); i++) {
        if (docs[i] == Doc) {
            docs[i].updateFreq();
            return;
        }
    }

    // If the document is not in the vector, add it
    docs.emplace_back(Doc);
}



/**************************
 **    getDocLocation    **
 *************************/
int WordNode::getDocLocation(std::string &Doc) {
    for (int i = 0; i < docs.size(); i++) {
        if (docs[i] == Doc) {
            return i;
        }
    }

    return -1;
}
int WordNode::getDocLocation(DocumentNode &Doc) {
    for (int i = 0; i < docs.size(); i++) {
        if (docs[i] == Doc) {
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
    if ((index >= docs.size() && index != -1) || index < -1) {
        throw std::runtime_error("Index out of array bounds");
    }

    // If the index is -1, increment the last item in the vector
    if (index == -1) {
        docs[docs.size()-1].updateFreq();
        return;
    }

    docs[index].updateFreq();
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
std::vector<DocumentNode>& WordNode::getDocuments() {
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
WordNode &WordNode::operator=(const WordNode &w) {
    word = w.word;
    for (int i = 0; i < w.docs.size(); i++) {
        docs.emplace_back(DocumentNode(w.docs[i].getName(), w.docs[i].getFreq()));
    }

    return *this;
}



/**********************************************
 **    Overload Stream Insertion Operator    **
 **********************************************/
std::ostream& operator<< (std::ostream& out, const WordNode& node) {
    out << "Word: " << node.word << std::endl;

    for (int i = 0; i < node.docs.size(); i++) {
        out << "  " << node.docs[i];
    }
    out << std::endl;

    return out;
}