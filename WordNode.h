#ifndef INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H


//#include <string>
#include "AVLTree.h"
#include "DocumentNode.h"
#include "tokStr.h"




// Stores information on words read from the JSON file
class WordNode {
private:

    std::string word; // The word stored in this node
    AVLTree<DocumentNode> docs; // Stores the document name and corresponding information

    std::string wordDocDel; // The delimiter between the word and docs in a file
    std::string docDel; // The delimiter between the docs in a file


public:
    /**
     * Constructors
     */
    WordNode();
    WordNode(std::string& newWord);
    WordNode(std::string& newWord, DocumentNode& doc);
    WordNode(WordNode& node);

    /**
     * addDoc Method
     * @param Doc The document to add to the vector
     */
    void addDoc(std::string &Doc, std::string& ID, int length, std::string& title, std::string& author, std::string& date);
    void addDoc(DocumentNode& Doc);

    /**
     * getDoc Method
     * Get the document from the AVL tree
     * @param Doc The document to search for
     * @return The document in the AVL tree
     */
    DocumentNode& getDoc(std::string& Doc);
    DocumentNode& getDoc(DocumentNode& Doc);

    /**
     * incrementDoc
     * Increment the counter for a given document
     * @param Doc The document to search for
     */
    void incrementDoc(std::string& Doc);
    void incrementDoc(DocumentNode& Doc);

    /**
     * getWord Method
     * Returns the word stored in this object
     * @retrun The stored word in this object
     */
    std::string& getWord();

    /**
     * getDocuments Method
     * Returns the word stored in this object
     * @retrun The stored word in this object
     */
    AVLTree<DocumentNode>& getDocuments();

    /**
     * Comparison Operators
     */
    bool operator==(WordNode& w);
    bool operator==(std::string& w);
    bool operator>(WordNode& w);
    bool operator>(std::string& w);
    bool operator<(WordNode& w);
    bool operator<(std::string& w);

    /**
     * Overloaded Assignment Operator
     */
    WordNode& operator=(WordNode& w);
    WordNode& operator=(std::string& str);

    /**
     * Overload ostream insertion operator to print the contents of this list
     * to ostream's output stream in the first argument.
     */
    friend std::ostream& operator<< (std::ostream&, const WordNode&);

    /**
     * Overload fstream insertion operator to print the contents of this list
     * to fstream's output stream in the first argument.
     */
    friend std::fstream& operator<< (std::fstream&, const WordNode&);
};




#endif //INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H