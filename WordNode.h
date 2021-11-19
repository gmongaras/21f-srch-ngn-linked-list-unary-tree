#ifndef INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H


#include <vector>
#include <string>
#include <stdexcept>
#include "AVLTree.h"
#include "DocumentNode.h"


// Stores information on words read from the JSON file
class WordNode {
private:
    std::string word; // The word stored in this node
    std::vector<DocumentNode> docs; // Stores the document name and corresponding information


public:
    /**
     * Constructors
     */
    WordNode();
    WordNode(std::string newWord);
    WordNode(std::string newWord, std::string doc);

    /**
     * addDoc Method
     * @param Doc The document to add to the vector
     */
    void addDoc(std::string& Doc);
    void addDoc(DocumentNode& Doc);

    /**
     * getDocLocation Method
     * @param Doc The document to search for
     * @return The index of the given document name, -1 if not found
     */
    int getDocLocation(std::string& Doc);
    int getDocLocation(DocumentNode& Doc);

    /**
     * incrementDoc
     * Increment the counter for an index of a given doc. If the
     * index is -1, add to the last doc added
     * @param index The index to increment
     */
    void incrementDoc(int index);

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
    std::vector<DocumentNode>& getDocuments();

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
    WordNode& operator=(const WordNode& w);

    /**
     * Overload stream insertion operator to print the contents of this list
     * to the output stream in the first argument.
     */
    friend std::ostream& operator<< (std::ostream&, const WordNode&);
};




#endif //INC_21F_FINAL_PROJ_TEMPLATE_WORDNODE_H
