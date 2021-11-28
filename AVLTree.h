#ifndef INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H


#include "TreeNode.h"
#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <fstream>

#define COUNT 4;


template <typename nodetype>
class AVLTree {
private:
    TreeNode<nodetype>* root;
    int numNodes;





    /**************************
     **    Helper Methods    **
     *************************/

    /**
     * AssignmentOperatorHelper Method
     * Inserts the nodes of a given subtree in an order so that sorting isn't needed
     * This method is mainly for the use of the overloaded assignment operator
     * @param subtree The subtree to add to this tree
     */
    void AssignmentOperatorHelper(TreeNode<nodetype>*& newSubtree, TreeNode<nodetype>*& oldSubtree);

    /**
     * clearSubtree Helper Method
     * Clears the given subtree and frees the memory the nodes are using
     * @param subtree The subtree to clear
     */
    void clearSubtree(TreeNode<nodetype>*& subtree);

    /**
     * CopyConstructorHelper Method
     * Inserts the nodes of a given subtree in an order so that sorting isn't needed
     * This method is mainly for the use of the copy constructor
     * @param subtree The subtree to add to this tree
     */
    void CopyConstructorHelper(TreeNode<nodetype>*& newSubtree, TreeNode<nodetype>*& oldSubtree);

    /**
     * PrintSubtree Helper Method
     * Sends the given subtree to the ostream
     * @param subtree The subtree to print to the ostream
     * @param space The space within the print
     * Note: code from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
     */
    void printSubtree(TreeNode<nodetype>*& subtree, int space);

    /**
     * PrintSubtree2 Helper Method
     * Sends the given subtree to the ostream
     * @param subtree The subtree to print to the ostream
     */
    void printSubtree2(TreeNode<nodetype>* const subtree) const;


    /**
     * Insert Helper Method
     * Inserts a node into the tree while maintaining BSTree consistency
     * @param newItem The item to insert into the tree
     * @param curPtr The current node to insert the new item into
     * @param equalityFunction The function to run if the given item is already in the tree
     * @return The value at the inserted node.
     */
    nodetype& insert(nodetype& newItem, TreeNode<nodetype>*& curPtr,
                std::function<void(nodetype& newItem, TreeNode<nodetype>*& curPtr)> equalityFunction);

    /**
     * hasNode Helper Method
     * @param node The node to look for in the tree.
     * @param subtree The subtree to look for the node
     * @return True if the node look for is in the tree, false otherwise
     */
    bool hasNode(nodetype& node, TreeNode<nodetype>*& subtree);
    bool hasNode(TreeNode<nodetype>& node, TreeNode<nodetype>*& subtree);

    /**
     * getNode Helper Method
     * Returns the node being looked for if found
     * @param node The node to look for in the tree.
     * @param subtree The subtree to look for the node
     * @return The node in the tree if the node is found
     */
    nodetype& getNode(nodetype& node, TreeNode<nodetype>*& subtree);
    nodetype& getNode(TreeNode<nodetype>& node, TreeNode<nodetype>*& subtree);

    /**
     * balance Helper Method
     * Ensures the given subtree is balanced
     * @param subtree The subtree to balance
     */
    void balance(TreeNode<nodetype>*& subtree);

    /**
     * getSubtreeHeight Method
     * Returns the height of a given subtree
     * @param subtree The subtree to balance
     */
    int getSubtreeHeight(TreeNode<nodetype>*& subtree);


    /**
     * Rearranging Methods (4 methods)
     * Given a subtree, the functions rearrange the nodes to maintain
     * AVL node consistency and keep the tree balanced
     * @param subtree The subtree to balance
     */
    void rotateWithLeftChild(TreeNode<nodetype>*& subtree);
    void doubleWithLeftChild(TreeNode<nodetype>*& subtree);
    void rotateWithRightChild(TreeNode<nodetype>*& subtree);
    void doubleWithRightChild(TreeNode<nodetype>*& subtree);

    /**
     * getInOrderVec Helper Method
     * Get an inorder traversal of the tree in a vector
     * @param vec The vector to store the contents of the tree
     * @param subtree The subtree to parse
     * @return A vector storing the contents of the tree in order
     */
    std::vector<nodetype>& getInOrderVec(std::vector<nodetype>&, TreeNode<nodetype>* subtree);



public:
    /**
     * Constructors and Destructor
     */
    AVLTree();
    AVLTree(TreeNode<nodetype>*& r);
    AVLTree(AVLTree<nodetype>& tree);
    ~AVLTree();


    /**
     * Insert Method
     * Inserts a node into the tree keeping the AVL tree balanced
     * @param newItem The new item to add to the tree
     * @param equalityFunction The function to run if the given item is already in the tree
     * @return The value at the inserted node.
     */
    nodetype& insert(nodetype& newItem,
                     std::function<void(nodetype& newItem, TreeNode<nodetype>*& curPtr)> equalityFunction);

    /**
     * hasNode Method
     * @param node The node to look for in the tree.
     * @return True if the node look for is in the tree, false otherwise
     */
    bool hasNode(nodetype& node);
    bool hasNode(TreeNode<nodetype>& node);

    /**
     * getNode Method
     * Returns the node if the node is found in the node.
     * @param node The node to look for in the tree.
     * @return The node in the tree if the node is found
     */
    nodetype& getNode(nodetype& node);
    nodetype& getNode(TreeNode<nodetype>& node);

    /**
     * getInOrderVec Method
     * Get an inorder traversal of the tree in a vector
     * @return A vector storing the contents of the tree in order
     */
    std::vector<nodetype> getInOrderVec();

    /**
     * Overloaded Assignment Operator
     */
    AVLTree<nodetype>& operator=(AVLTree<nodetype>& tree);

    /**
     * clearTree Method
     * Clears the subtree and frees the memory used
     */
    void clearTree();

    /**
     * printTree Method
     */
    void printTree();

    /**
     * printTree Method
     */
    void printTree2() const;

    /**
     * getRootData Method
     * Returns the data at the root node
     */
    nodetype& getRootData();

    /**
     * fstream LevelOrder Method
     * Sends a level order of the tree to a given fstream
     * @param out The fstream to send output to
     * @param delimiter The delimiter to go between each part of the tree
     * @return The fstream with contents from the tree
     */
    std::fstream& fstreamLevelOrder(std::fstream& out, const std::string& delimiter) const;

    /**
     * saveTree Method
     * Saves a tree to a given filename
     * @param filename The filename to save to
     */
    void saveTree(const std::string& filename = std::string("storage/AVLTree.csv"));

    /**
     * loadTree Method
     * Loads a tree from a given file
     * @param filename The file use to lead in
     * @param delimiter The delimiter used when leading in the tree
     */
    void loadTree(const std::string& filename, char delimiter = ',');
};








/**********************************************************
 **                Private Helper Methods                **
 *********************************************************/



/*******************************************
 **    AssignmentOperatorHelper Method    **
 ******************************************/
template <typename nodetype>
void AVLTree<nodetype>::AssignmentOperatorHelper(TreeNode<nodetype>*& newSubtree, TreeNode<nodetype>*& oldSubtree) {
    // If the old subtree is nullptr, go back up the stack
    if (oldSubtree == nullptr) {
        return;
    }

    // Add the left and right nodes from the old subtree to the new one
    if (oldSubtree->left != nullptr) {newSubtree->left = new TreeNode<nodetype>(oldSubtree->left);}
    if (oldSubtree->right != nullptr) {newSubtree->right = new TreeNode<nodetype>(oldSubtree->right);}

    // Add the left and right subtrees
    CopyConstructorHelper(newSubtree->left, oldSubtree->left);
    CopyConstructorHelper(newSubtree->right, oldSubtree->right);
}



/*******************************
 **    clearSubtree Method    **
 ******************************/
template <typename nodetype>
void AVLTree<nodetype>::clearSubtree(TreeNode<nodetype>*& subtree) {
    // If the subtree is nullptr, return (base case)
    if (subtree == nullptr) {
        return;
    }

    // If the subtree is not nullptr, delete the left and right
    // subtrees
    clearSubtree(subtree->right);
    clearSubtree(subtree->left);

    // Delete the root of the subtree
    delete subtree;
}



/****************************************
 **    CopyConstructorHelper Method    **
 ***************************************/
template <typename nodetype>
void AVLTree<nodetype>::CopyConstructorHelper(TreeNode<nodetype>*& newSubtree, TreeNode<nodetype>*& oldSubtree) {
    // If the old subtree is nullptr, go back up the stack
    if (oldSubtree == nullptr) {
        return;
    }

    // Add the left and right nodes from the old subtree to the new one
    if (oldSubtree->left != nullptr) {newSubtree->left = new TreeNode<nodetype>(oldSubtree->left);}
    if (oldSubtree->right != nullptr) {newSubtree->right = new TreeNode<nodetype>(oldSubtree->right);}

    // Add the left and right subtrees
    CopyConstructorHelper(newSubtree->left, oldSubtree->left);
    CopyConstructorHelper(newSubtree->right, oldSubtree->right);
}



/*******************************
 **    printSubtree Method    **
 ******************************/
template <typename nodetype>
void AVLTree<nodetype>::printSubtree(TreeNode<nodetype>*& subtree, int space) {
    // Base case
    if (subtree == nullptr)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    printSubtree(subtree->right, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT i < space; i++)
        std::cout << " ";
    std::cout << subtree->data << "\n";

    // Process left child
    printSubtree(subtree->left, space);
}

/********************************
 **    printSubtree2 Method    **
 *******************************/
template <typename nodetype>
void AVLTree<nodetype>::printSubtree2(TreeNode<nodetype>* const subtree) const {
    // Base case
    if (subtree == nullptr) {
        return;
    }

    // Print the Left subtree
    printSubtree2(subtree->left);

    // Print the middle node
    std::cout << subtree->data << std::endl;

    // Print the right subtree
    printSubtree2(subtree->right);
}



/********************************
 **    insert Helper Method    **
 *******************************/
template <typename nodetype>
nodetype& AVLTree<nodetype>::insert(nodetype& newItem, TreeNode<nodetype>*& curPtr, std::function<void(nodetype& newItem, TreeNode<nodetype>*& curPtr)> equalityFunction) {
    // If curPtr is nullptr, set the curPtr to the newItem
    if (curPtr == nullptr) {
        curPtr = new TreeNode<nodetype>(newItem);
        numNodes++;
        return curPtr->data;
    }

    // If the new item is less than the current node to insert the node into,
    // add the node to the left of that node
    else if (newItem < (*curPtr).data) {
        nodetype& sub = insert(newItem, curPtr->left, equalityFunction);
        balance(curPtr);
        numNodes++;
        return sub;
    }

    // If the new item is greater than the current node to insert the node into,
    // add the node to the right of that node
    else if (newItem > (*curPtr).data) {
        nodetype& sub = insert(newItem, curPtr->right, equalityFunction);
        balance(curPtr);
        numNodes++;
        return sub;
    }

    // If the node is equal call the equality function
    else {
        equalityFunction(newItem, curPtr);
        return curPtr->data;
    }
}



/**********************************
 **    hasNode Helper Methods    **
 *********************************/
template <typename nodetype>
bool AVLTree<nodetype>::hasNode(nodetype &node, TreeNode<nodetype> *&subtree) {
    // If the subtree is empty return false
    if (subtree == nullptr) {
        return false;
    }

    // If the node is found, return true
    else if (subtree->getData() == node) {
        return true;
    }

    // If the node to search for is less than the current subtree root, look
    // to the left of the subtree
    else if (node < subtree->getData()) {
        return hasNode(node, subtree->left);
    }
    // If the node to search for is greater than the current subtree root, look
    // to the left of the subtree
    else {
        return hasNode(node, subtree->right);
    }
}

template <typename nodetype>
bool AVLTree<nodetype>::hasNode(TreeNode<nodetype>& node, TreeNode<nodetype> *&subtree) {
    // If the subtree is empty return false
    if (subtree == nullptr) {
        return false;
    }

    // If the node is found, return true
    else if (subtree == node) {
        return true;
    }

    // If the node to search for is less than the current subtree root, look
    // to the left of the subtree
    else if (node < subtree) {
        return hasNode(node, subtree->left);
    }
    // If the node to search for is greater than the current subtree root, look
    // to the left of the subtree
    else {
        return hasNode(node, subtree->right);
    }
}



/**********************************
 **    getNode Helper Methods    **
 *********************************/
template <typename nodetype>
nodetype& AVLTree<nodetype>::getNode(nodetype &node, TreeNode<nodetype> *&subtree) {
    // If the subtree is empty, the node was not found so raise an error
    if (subtree == nullptr) {
        throw std::runtime_error("Node not found in tree");
    }

    // If the node is found, return it
    else if (subtree->getData() == node) {
        return subtree->data;
    }

    // If the node to search for is less than the current subtree root, look
    // to the left of the subtree
    else if (node < subtree->getData()) {
        return getNode(node, subtree->left);
    }
    // If the node to search for is greater than the current subtree root, look
    // to the left of the subtree
    else {
        return getNode(node, subtree->right);
    }
}

template <typename nodetype>
nodetype& AVLTree<nodetype>::getNode(TreeNode<nodetype>& node, TreeNode<nodetype>*& subtree) {
    // If the subtree is empty, the node was not found so raise an error
    if (subtree == nullptr) {
        throw std::runtime_error("Node not found in tree");
    }

    // If the node is found, return it
    else if (subtree == node) {
        return subtree->data;
    }

    // If the node to search for is less than the current subtree root, look
    // to the left of the subtree
    else if (node < subtree) {
        return getNode(node, subtree->left);
    }
    // If the node to search for is greater than the current subtree root, look
    // to the left of the subtree
    else {
        return getNode(node, subtree->right);
    }
}



/**************************
 **    balance Method    **
 *************************/
template <typename nodetype>
void AVLTree<nodetype>::balance(TreeNode<nodetype>*& subtree) {
    // If the subtree is nullptr, don't do anything
    if (subtree == nullptr) {
        return;
    }


    // If the height of the left subtree is greater than the height of the
    // right subtree by more than 1, correct it
    if (getSubtreeHeight(subtree->left) - getSubtreeHeight(subtree->right) > 1) {
        // Case 1 (LL)
        if (getSubtreeHeight(subtree->left->left) >= getSubtreeHeight(subtree->left->right)) {
            rotateWithLeftChild(subtree);
        }
        // Case 2 (LR)
        else {
            doubleWithLeftChild(subtree);
        }
    }
    // If the height of the right subtree is greater than the height of the
    // left subtree by more than 1, correct it
    else if (getSubtreeHeight(subtree->right) - getSubtreeHeight(subtree->left) > 1) {
        // Case 4 (RR)
        if (getSubtreeHeight(subtree->right->right) >= getSubtreeHeight(subtree->right->left)) {
            rotateWithRightChild(subtree);
        }
        // Case 3 (RL)
        else {
            doubleWithRightChild(subtree);
        }
    }


    // If none of the statements are met, the subtree is balanced



    // Calculate the subtree's height
    subtree->height = std::max(getSubtreeHeight(subtree->left), getSubtreeHeight(subtree->right)) + 1;
}



/***********************************
 **    getSubtreeHeight Method    **
 **********************************/
template <typename nodetype>
int AVLTree<nodetype>::getSubtreeHeight(TreeNode<nodetype>*& subtree) {
    // If the node is nullptr, the value is -1
    if (subtree == nullptr) {
        return -1;
    }

    return subtree->height;
}




/*****************************
 **    Rearrange Methods    **
 ****************************/
template <typename nodetype>
void AVLTree<nodetype>::rotateWithLeftChild(TreeNode<nodetype>*& subtree) {
    TreeNode<nodetype>* temp = subtree->left;
    subtree->left = temp->right;
    temp->right = subtree;
    subtree->height = std::max(getSubtreeHeight(subtree->left), getSubtreeHeight(subtree->right)) + 1;
    temp->height = std::max(getSubtreeHeight(temp->left), subtree->height) + 1;
    subtree = temp;

//    subtree = subtree->left;
//    subtree->height = temp->height;
//    temp->left = subtree->right;
//    subtree->right = temp;
}

template <typename nodetype>
void AVLTree<nodetype>::doubleWithLeftChild(TreeNode<nodetype>*& subtree) {
    rotateWithRightChild(subtree->left);
    rotateWithLeftChild(subtree);
}

template <typename nodetype>
void AVLTree<nodetype>::rotateWithRightChild(TreeNode<nodetype>*& subtree) {
    TreeNode<nodetype>* temp = subtree->right;
    subtree->right = temp->left;
    temp->left = subtree;
    subtree->height = std::max(getSubtreeHeight(subtree->right), getSubtreeHeight(subtree->left)) + 1;
    temp->height = std::max(getSubtreeHeight(temp->right), subtree->height) + 1;
    subtree = temp;

//    TreeNode<nodetype>* temp = subtree;
//    subtree = subtree->right;
//    temp->right = subtree->left;
//    subtree->left = temp;
}

template <typename nodetype>
void AVLTree<nodetype>::doubleWithRightChild(TreeNode<nodetype>*& subtree) {
    rotateWithLeftChild(subtree->right);
    rotateWithRightChild(subtree);
}



/****************************************
 **    getInOrderVec Helper Methods    **
 ***************************************/
template <typename nodetype>
std::vector<nodetype> &AVLTree<nodetype>::getInOrderVec(std::vector<nodetype>& vec, TreeNode<nodetype> *subtree) {
    // If the subtree is nullptr, return the vector
    if (subtree == nullptr) {
        return vec;
    }

    // Store the values in the left subtree
    getInOrderVec(vec, subtree->left);

    // Store this subtrees value
    vec.emplace_back(subtree->data);

    // Store the values in the right subtree
    getInOrderVec(vec, subtree->right);

    // Return the vector
    return vec;
}




















/**************************************************
 **                Public Methods                **
 *************************************************/


/***************************************
 **    Constructors and Destructor    **
 **************************************/
template <typename nodetype>
AVLTree<nodetype>::AVLTree() {
    root = nullptr;
    numNodes = 0;
}
template <typename nodetype>
AVLTree<nodetype>::AVLTree(TreeNode<nodetype>*& r) {
    // If the given node is nullptr, do nothing.
    if (r == nullptr) {
        return;
    }

    root = r;
    numNodes = 1;
}
template <typename nodetype>
AVLTree<nodetype>::AVLTree(AVLTree<nodetype> &tree) {
    // If the given tree is nullptr, do nothing.
    if (tree.root == nullptr) {
        return;
    }

    // Insert the root node
    root = new TreeNode<nodetype>(tree.root);

    // Insert the other nodes
    CopyConstructorHelper(root, tree.root);
    numNodes = tree.numNodes;
}
template <typename nodetype>
AVLTree<nodetype>::~AVLTree<nodetype>() {
    clearTree();
}





/*************************
 **    Insert Method    **
 ************************/
template <typename nodetype>
nodetype& AVLTree<nodetype>::insert(nodetype &newItem, std::function<void(nodetype& newItem, TreeNode<nodetype>*& curPtr)> equalityFunction) {
    // If the head is nullptr, make the given node head
    if (root == nullptr) {
        root = new TreeNode<nodetype>(newItem);
        return root->data;
    }

    return insert(newItem, root, equalityFunction);
}



/***************************
 **    hasNode Methods    **
 **************************/
template <typename nodetype>
bool AVLTree<nodetype>::hasNode(nodetype &node) {
    return hasNode(node, root);
}

template <typename nodetype>
bool AVLTree<nodetype>::hasNode(TreeNode<nodetype> &node) {
    return hasNode(node, root);
}



/***************************
 **    getNode Methods    **
 **************************/
template <typename nodetype>
nodetype& AVLTree<nodetype>::getNode(nodetype& node) {
    return getNode(node, root);
}

template <typename nodetype>
nodetype& AVLTree<nodetype>::getNode(TreeNode<nodetype>& node) {
    return getNode(node, root);
}



/********************************
 **    getInOrderVec Method    **
 *******************************/
template <typename nodetype>
std::vector<nodetype> AVLTree<nodetype>::getInOrderVec() {
    std::vector<nodetype> vec;
    return getInOrderVec(vec, root);
}



/******************************************
 **    Overloaded Assignment Operator    **
 *****************************************/
template <typename nodetype>
AVLTree<nodetype> &AVLTree<nodetype>::operator=(AVLTree<nodetype> &tree) {
    // If the given tree is nullptr, do nothing.
    if (tree.root == nullptr) {
        return *this;
    }

    // Insert the root node
    root = new TreeNode<nodetype>(tree.root);

    // Insert the other nodes
    AssignmentOperatorHelper(root, tree.root);

    return *this;
}



/*******************************
 **    clearSubtree Method    **
 ******************************/
template <typename nodetype>
void AVLTree<nodetype>::clearTree() {
    // If the root is nullptr, don't do anything
    if (root == nullptr)
        return;

    // Clear the left and right subtrees
    clearSubtree(root->left);
    clearSubtree(root->right);

    // Frees the root
    delete root;
    root = nullptr;
}



/***************************
 **    printTree Method   **
 **************************/
template <typename nodetype>
void AVLTree<nodetype>::printTree() {
    return printSubtree(root, 0);
}



/****************************
 **    printTree2 Method   **
 ***************************/
template <typename nodetype>
void AVLTree<nodetype>::printTree2() const {
    return printSubtree2(root);
}



/******************************
 **    getRootData Method    **
 *****************************/
template <typename nodetype>
nodetype& AVLTree<nodetype>::getRootData() {
    return root->data;
}



/************************************
 **    fstreamLevelOrder Method    **
 ***********************************/
template <typename nodetype>
std::fstream &AVLTree<nodetype>::fstreamLevelOrder(std::fstream &out, const std::string& delimiter) const {
    // Code from: https://www.geeksforgeeks.org/level-order-tree-traversal/

    // Base case
    if (root == nullptr) {
        return out;
    }

    // Create queue for level traversial
    std::queue<TreeNode<nodetype>*> q;

    // Enqueue the subtree and initialize the height
    q.push(root);

    // The node to send to the fstream
    TreeNode<nodetype>* node;

    // Iterate till the queue is empty meaning all nodes have been visitied
    while (q.empty() == false) {
        // Save the front of the queue and remove it from the queue
        node = q.front();
        out << node->data << delimiter;
        q.pop();

        // Visit the left child
        if (node->left != nullptr) {q.push(node->left);}

        // Visit the right child
        if (node->right != nullptr) {q.push(node->right);}
    }

    return out;
}



/********************
 **    saveTree    **
 *******************/
template <typename nodetype>
void AVLTree<nodetype>::saveTree(const std::string &filename) {
    // Open a file for writing
    std::fstream file(filename.c_str(), std::fstream::out);

    // Save the tree to the file
    fstreamLevelOrder(file, "\n");

    // Close the file
    file.close();
}



/***************************
 **    loadTree Method    **
 **************************/
template <typename nodetype>
void AVLTree<nodetype>::loadTree(const std::string &filename, char delimiter) {
//    // Open a file for reading
//    std::fstream file(filename.c_str(), std::fstream::in);
//
//    // Check if the file is open
//    if (file.is_open()) {
//        // Iterate over all lines in the file
//        while (!file.eof()) {
//            // Create a temporary node to read in the line
//            TreeNode<nodetype> newNode;
//            newNode << file.getline();
//        }
//    }
//    // If the file isn't open, throw and error
//    else {
//        throw std::runtime_error("AVLTree file could not open");
//    }
}




#endif //INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
