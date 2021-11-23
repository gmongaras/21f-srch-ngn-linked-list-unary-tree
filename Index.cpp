#include "Index.h"



/**
 * wordsEqualityFunction
 * Function to pass into the insert method in the words AVL tree. It
 * increases the counter in the WordNode by 1 for the given document.
 * @param newItem The item to insert
 * @param curPtr The pointer to the current subtree
 */
void wordsEqualityFunction(WordNode& newItem, TreeNode<WordNode>*& curPtr) {
    curPtr->getData().addDoc(newItem.getDocuments().getRootData());
    //curPtr->getData().addDoc(newItem.getDocuments()[0]);//temp.getDocLocation(newItem.getDocuments()[0]));
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