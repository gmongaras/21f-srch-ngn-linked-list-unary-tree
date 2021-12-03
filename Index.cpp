#include "Index.h"
#include <algorithm>



/**
 * wordsEqualityFunction
 * Function to pass into the insert method in the words AVL tree. It
 * adds a new document to the given node and increases the count of the word.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void wordsEqualityFunction(WordNode& newItem, TreeNode<WordNode>*& curPtr) {
    curPtr->getData().addDoc(newItem.getDocuments().getRootData());
    curPtr->getData().incrementCount();
    //curPtr->getData().addDoc(newItem.getDocuments()[0]);//temp.getDocLocation(newItem.getDocuments()[0]));
}



/**
 * peopleEqualityFunction
 * Function to pass into the update method in the people hash map. It
 * adds a new document to that node.
 * @param nodeValue The value in the hash map to modify
 * @param givenValue The value to add to the hash map
 */
void peopleEqualityFunction(WordNode& nodeValue, WordNode& givenValue) {
    nodeValue.addDoc(givenValue.getDocuments().getRootData());
}


/**
 * orgsEqualityFunction
 * Function to pass into the update method in the orgs hash map. It
 * adds a new document to that node.
 * @param nodeValue The value in the hash map to modify
 * @param givenValue The value to add to the hash map
 */
void orgsEqualityFunction(WordNode& nodeValue, WordNode& givenValue) {
    nodeValue.addDoc(givenValue.getDocuments().getRootData());
}










/***************************
 **    loadTree Method    **
 **************************/
;



















/*****************************
 **    clearIndex Method    **
 ****************************/
void Index::clearIndex() {
    words.clearTree();
    people.clear();
    orgs.clear();
}



/****************************
 **    saveFiles Method    **
 ***************************/
void Index::saveFiles(std::string &wordsFileName, std::string &peopleFileName, std::string &orgsFileName) {
    words.saveTree(wordsFileName);
    people.saveTable(peopleFileName);
    orgs.saveTable(orgsFileName);
}



/*********************
 **    LoadFiles    **
 ********************/
void Index::LoadFiles(std::string &wordsFileName, std::string &peopleFileName, std::string &orgsFileName) {
    // Unload the old words data and load in the new data
    words.clearTree();
    words.loadTree(wordsFileName, '\n', &wordsEqualityFunction);//, wordCounts);

    // Unload the old people data and load in the new data
    people.clear();
    people.loadTable(peopleFileName, &peopleEqualityFunction);

    // Unload the old organization data and load in the new data
    orgs.clear();
    orgs.loadTable(orgsFileName, &orgsEqualityFunction);
}











/**************************
 **    addWord Method    **
 *************************/
void Index::addWord(WordNode &word) {
    words.insert(word, &wordsEqualityFunction);
}



/**************************
 **    getWord Method    **
 *************************/
WordNode &Index::getWord(std::string &word) {
    WordNode temp(word);
    return words.getNode(temp);
}



/******************************
 **    getNumWords Method    **
 *****************************/
long long Index::getNumWords() {
    return words.getNumAdded();
}



/************************************
 **    getNumUniqueWords Method    **
 ***********************************/
int Index::getNumUniqueWords() {
    return words.getNumNodes();
}



/******************************
 **    getTop50WordCounts    **
 *****************************/
bool sortFunc(const WordNode& a, const WordNode& b) {return (a.getCount() > b.getCount());}
//bool sortFunc(WordNode& a, WordNode& b) {return (a.getCount() > b.getCount());}
std::vector<WordNode> Index::getTop50WordCounts() {
    // Get an inorder vector of the Words AVL Tree
    std::vector<WordNode> inorderAVLTree;
    inorderAVLTree.resize(words.getNumNodes());
    words.getInOrderVec(inorderAVLTree);

    // Re sort the vector in terms of the word counts
    std::sort(inorderAVLTree.begin(), inorderAVLTree.end(), sortFunc);

    // Get the top 50 words from the vector
    std::vector<WordNode> topCounts = std::vector<WordNode>(inorderAVLTree.begin(), inorderAVLTree.begin() + std::min((int)inorderAVLTree.size(), 50));

    // Reverse the top values
    std::reverse(topCounts.begin(), topCounts.begin());

    return topCounts;
}













/****************************
 **    addPerson Method    **
 ***************************/
void Index::addPerson(std::string &person, WordNode &node) {
    people.addPair(person, node, &peopleEqualityFunction);
}



/********************************
 **    getPeopleDocs Method    **
 *******************************/
WordNode& Index::getPeopleDocs(std::string& person) {
    return people[person];
}



/*************************************
 **    getNumUniquePeople Method    **
 ************************************/
int Index::getNumUniquePeople() {
    return people.getUnique();
}









/*************************
 **    addOrg Method    **
 ************************/
void Index::addOrg(std::string &org, WordNode &node) {
    orgs.addPair(org, node, &orgsEqualityFunction);
}



/*****************************
 **    getOrgDocs Method    **
 ****************************/
WordNode &Index::getOrgDocs(std::string &org) {
    return orgs[org];
}



/****************************
 **    getNumUniqueOrgs    **
 ***************************/
int Index::getNumUniqueOrgs() {
    return orgs.getUnique();
}