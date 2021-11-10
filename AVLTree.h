#ifndef INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H


#include "TreeNode.h"
#include <iostream>
#define COUNT 4;


template <typename nodetype>
class AVLTree {
private:
    //friend class TreeNode<nodetype>;


    TreeNode<nodetype>* root;


    /**************************
     **    Helper Methods    **
     *************************/

    /**
     * clearSubtree Helper Method
     * Clears the given subtree and frees the memory the nodes are using
     * @param subtree The subtree to clear
     */
    void clearSubtree(TreeNode<nodetype>* subtree);

    /**
     * CopyConstructorHelper Method
     * Inserts the nodes of a given subtree in an order so that sorting isn't needed
     * This method is mainly for the use of the copy constructor
     * @param subtree The subtree to add to this tree
     */
    void CopyConstructorHelper(TreeNode<nodetype> *newSubtree, TreeNode<nodetype> *oldSubtree);

    /**
     * PrintSubtree Helper Method
     * Sends the given subtree to the ostream
     * @param subtree The subtree to print to the ostream
     * @param space The space within the print
     * Node: code from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
     */
    void printSubtree(TreeNode<nodetype>* subtree, int space);


    /**
     * Insert Helper Method
     * Inserts a node into the tree while maintaining BSTree consistency
     * @param newItem The item to insert into the tree
     * @param curPtr The current node to insert the new item into
     */
    void insert(nodetype& newItem, TreeNode<nodetype>* curPtr);



public:
    /**
     * Constructors and Destructor
     */
    AVLTree();
    AVLTree(TreeNode<nodetype>* r);
    AVLTree(AVLTree<nodetype>& tree);
    ~AVLTree();


    /**
     * Insert Method
     * Inserts a node into the tree keeping the AVL tree balanced
     * @param newItem The new item to add to the tree
     */
    void insert(nodetype& newItem);

    /**
     * clearTree Method
     * Clears the subtree and frees the memory used
     */
    void clearTree();

    /**
     * printTree Method
     */
    void printTree();
};



/**********************************************************
 **                Private Helper Methods                **
 *********************************************************/



/*******************************
 **    clearSubtree Method    **
 ******************************/
template <typename nodetype>
void AVLTree<nodetype>::clearSubtree(TreeNode<nodetype>* subtree) {
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
void AVLTree<nodetype>::CopyConstructorHelper(TreeNode<nodetype> *newSubtree, TreeNode<nodetype> *oldSubtree) {
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
void AVLTree<nodetype>::printSubtree(TreeNode<nodetype>* subtree, int space) {
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
 **    insert Helper Method    **
 *******************************/
template <typename nodetype>
void AVLTree<nodetype>::insert(nodetype &newItem, TreeNode<nodetype>* curPtr) {
    // If the new item is less than the current node to insert the node into,
    // add the node to the left of that node
    if (newItem < (*curPtr).data) {
        // If the left side is nullptr, add the item to the left side
        if (curPtr->left == nullptr) {
            curPtr->left = new TreeNode<nodetype>(newItem);
        }
        // If the left side is not nullptr, call the insert method again
        // and insert the node into the left subtree
        else {
            insert(newItem, curPtr->left);
        }
    }

    // If the new item is not less than the current node to insert the node into,
    // add the node to the right of that node
    else {
        // If the right side is nullptr, add the item to the right side
        if (curPtr->right == nullptr) {
            curPtr->right = new TreeNode<nodetype>(newItem);
        }
        // If the right side is not nullptr, call the insert method again
        // and insert the node into the right subtree
        else {
            insert(newItem, curPtr->right);
        }
    }


    // Call checks as stack unwinds
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
}
template <typename nodetype>
AVLTree<nodetype>::AVLTree(TreeNode<nodetype>* r) {
    // If the given node is nullptr, do nothing.
    if (r == nullptr) {
        return;
    }

    root = r;
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
}
template <typename nodetype>
AVLTree<nodetype>::~AVLTree<nodetype>() {
    clearTree();
}





/*************************
 **    Insert Method    **
 ************************/
template <typename nodetype>
void AVLTree<nodetype>::insert(nodetype &newItem) {
    // If the head is nullptr, make the given node head
    if (root == nullptr) {
        root = new TreeNode<nodetype>(newItem);
        return;
    }

    insert(newItem, root);
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
}



/***************************
 **    printTree Method   **
 **************************/
 template <typename nodetype>
void AVLTree<nodetype>::printTree() {
    // Set the tree count
    //COUNT tree.root->height;

    return printSubtree(root, 0);
}




#endif //INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
