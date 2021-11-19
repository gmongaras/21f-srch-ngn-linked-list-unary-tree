

#include "WordNode.h"


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
WordNode::WordNode(std::string newWord) {
    word = newWord;
}
WordNode::WordNode(std::string& newWord, std::string& doc, std::string& ID) {
    word = newWord;
    DocumentNode temp = DocumentNode(doc, 1, ID);
    docs.insert(temp, &docsEqualityFunction);
}



/*************************
 **    addDoc Method    **
 ************************/
void WordNode::addDoc(std::string &Doc, std::string& ID) {
    // Temporary node to insert
    DocumentNode temp = DocumentNode(Doc, 1, ID);

    // Try inserting the document, if it is already in the
    // tree, increment the value.
    docs.insert(temp, &docsEqualityFunction);

//    // If the document is already in the list, increment it
//    try {
//        docs.getNode(temp);
//    }
//    // If the document wasn't found, add it
//    catch (std::runtime_error e) {
//        docs.insert(Doc, &docsEqualityFunction); // Try inserting the node without reiterating
//        return;
//    }
//    for (int i = 0; i < docs.size(); i++) {
//        if (docs[i] == Doc) {
//            docs[i].updateFreq();
//            return;
//        }
//    }
//
//    // If the document is not in the vector, add it
//    docs.emplace_back(DocumentNode(Doc, 1));
}
void WordNode::addDoc(DocumentNode &Doc) {
    // Try inserting the document, if it is already in the
    // tree, increment the value.
    docs.insert(Doc, &docsEqualityFunction);


//    // If the document is already in the list, increment it
//    for (int i = 0; i < docs.size(); i++) {
//        if (docs[i] == Doc) {
//            docs[i].updateFreq();
//            return;
//        }
//    }
//
//    // If the document is not in the vector, add it
//    docs.emplace_back(Doc);
}



/**************************
 **    getDocLocation    **
 *************************/
DocumentNode& WordNode::getDoc(std::string &Doc) {
    // Temporary node to look for
    DocumentNode temp = DocumentNode(Doc, 1, "");

    // Try finding the document, if the node is found,
    // return the
    return docs.getNode(temp);


//    for (int i = 0; i < docs.size(); i++) {
//        if (docs[i] == Doc) {
//            return i;
//        }
//    }
//
//    return -1;
}
DocumentNode& WordNode::getDoc(DocumentNode &Doc) {
    // Try finding the document, if the node is found,
    // return the
    return docs.getNode(Doc);


//    for (int i = 0; i < docs.size(); i++) {
//        if (docs[i] == Doc) {
//            return i;
//        }
//    }
//
//    return -1;
}



/*******************************
 **    incrementDoc Method    **
 ******************************/
void WordNode::incrementDoc(std::string& Doc) {
    // Try finding the document in the tree. If it's found, increment it
    getDoc(Doc).updateFreq();


//    // If the index is too large or small, throw an error
//    if ((index >= docs.size() && index != -1) || index < -1) {
//        throw std::runtime_error("Index out of array bounds");
//    }
//
//    // If the index is -1, increment the last item in the vector
//    if (index == -1) {
//        docs[docs.size()-1].updateFreq();
//        return;
//    }
//
//    docs[index].updateFreq();
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


//    for (int i = 0; i < w.docs.size(); i++) {
//        docs.emplace_back(DocumentNode(w.docs[i].getName(), w.docs[i].getFreq()));
//    }
//
//    return *this;
}



/**********************************************
 **    Overload Stream Insertion Operator    **
 **********************************************/
std::ostream& operator<< (std::ostream& out, const WordNode& node) {
    out << "Word: " << node.word << std::endl;

    node.docs.printTree2();
//
//    for (int i = 0; i < node.docs.size(); i++) {
//        out << "  " << node.docs[i];
//    }
//    out << std::endl;

    return out;
}