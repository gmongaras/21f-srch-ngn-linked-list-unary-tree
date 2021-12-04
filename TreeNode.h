/**
 * Outline: The TreeNode class stores a single item within it that can be of
 *          any datatype and two pointers to a left and right subtree
 * Date: 12/4/21
 * Author: Gabriel Mongaras
 * Input: item to store
 * Output: A node with that item stored
 */



#ifndef P04_TreeNode_H
#define P04_TreeNode_H

#include <iostream>


template <typename datatype>
class TreeNode {
    template <typename newdatatype>
    friend class AVLTree;

private:
    datatype data;
    TreeNode<datatype> *left;
    TreeNode<datatype> *right;
    int height;

public:
    /**
     * Constructors
     */
    TreeNode();
    TreeNode(datatype newData);
    TreeNode(TreeNode<datatype>& oldData);
    TreeNode(TreeNode<datatype>* oldData);
    TreeNode(const TreeNode<datatype>* oldData);


    /**
     * Overload == operator
     * Input:
     *     A node or data that's the same datatype as this node.
     * Output:
     *     bool (True if data is equal. False otherwise)
     */
    bool operator== (const datatype&) const;
    bool operator== (const TreeNode<datatype>&) const;

    /**
     * Overload != operator
     * Input:
     *     A node or data that's the same datatype as this node.
     * Output:
     *     bool (True if data is not equal. False otherwise)
     */
    bool operator!= (const datatype&) const;
    bool operator!= (const TreeNode<datatype>&) const;

    /**
     * Overload > operator
     * Input:
     *     A node or data that's the same datatype as this node.
     * Output:
     *     bool (True if given data is less than the data in this node. False otherwise)
     */
    bool operator> (const datatype&) const;
    bool operator> (const TreeNode<datatype>&) const;

    /**
     * Overload < operator
     * Input:
     *     A node or data that's the same datatype as this node.
     * Output:
     *     bool (True if given data is greater than the data in this node. False otherwise)
     */
    bool operator< (const datatype&) const;
    bool operator< (const TreeNode<datatype>&) const;

    /**
     * Overload modifying = operator
     * Input:
     *     A node or data that's the same datatype as this node.
     * Output:
     *     A pointer to this node object
     */
    TreeNode<datatype>& operator= (const datatype&);
    TreeNode<datatype>& operator= (const TreeNode<datatype>&);

    /**
     * Overload ostream insertion operator to print the contents of this list
     * to ostream's output stream in the first argument.
     */
    template <typename datatype2>
    friend std::ostream& operator<< (std::ostream&, const TreeNode<datatype2>&);
    template <typename datatype2>
    friend std::ostream& operator<< (std::ostream&, const TreeNode<datatype2>*);

    /**
     * Overload fstream insertion operator to print the contents of this list
     * to fstream's output stream in the first argument.
     */
    template <typename datatype2>
    friend std::fstream& operator<< (std::fstream&, const TreeNode<datatype2>&);
    template <typename datatype2>
    friend std::fstream& operator<< (std::fstream&, const TreeNode<datatype2>*);

    /**
     * Get the data within this node
     * getData() method
     * Input:
     *   None
     * Output:
     *   The data being held by this node
     */
    datatype& getData();

    /**
     * Get the right node in the sequence
     * getRight() method
     * Input:
     *   None
     * Output:
     *   The right node pointed to by this node
     */
    TreeNode* getRight() const;

    /**
     * Get the leftious node in the sequence
     * getLeft() method
     * Input:
     *   None
     * Output:
     *   The left node pointed to by this node
     */
    TreeNode* getLeft() const;

    /**
     * Sets the right node in the sequence
     * setRight()
     * Input:
     *   The right node in the sequence
     * Output:
     *   None
     */
    void setRight(TreeNode<datatype>*);

    /**
     * Sets the leftious node in the sequence
     * setleft()
     * Input:
     *   The left node in the sequence
     * Output:
     *   None
     */
    void setLeft(TreeNode<datatype>*);

    /**
     * Returns the height of the tree
     * getHeight()
     * @return Height of the tree
     */
    int getHeight();
};




/****************************************
 **    Constructors and Destructors    **
 ***************************************/
template <typename datatype>
TreeNode<datatype>::TreeNode() {
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename datatype>
TreeNode<datatype>::TreeNode(datatype newData) {
    data = newData;
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename datatype>
TreeNode<datatype>::TreeNode(TreeNode<datatype>& oldData) {
    data = oldData.data;
    left = nullptr;
    right = nullptr;
    height = oldData.height;
}

template <typename datatype>
TreeNode<datatype>::TreeNode(TreeNode<datatype>* oldData) {
    data = oldData->data;
    left = nullptr;
    right = nullptr;
    height = oldData->height;
}

template <typename datatype>
TreeNode<datatype>::TreeNode(const TreeNode<datatype>* oldData) {
    data = oldData->data;
    left = nullptr;
    right = nullptr;
    height = oldData->height;
}



/********************************
 **    Overload == operator    **
 *******************************/
template <typename datatype>
bool TreeNode<datatype>::operator==(const datatype& d) const {
    return (data==d);
}

template <typename datatype>
bool TreeNode<datatype>::operator==(const TreeNode<datatype>& d) const {
    return (data==d.data);
}

/********************************
 **    Overload != operator    **
 *******************************/
template <typename datatype>
bool TreeNode<datatype>::operator!=(const datatype& d) const {
    return (data!=d);
}

template <typename datatype>
bool TreeNode<datatype>::operator!=(const TreeNode<datatype>& d) const {
    return (data!=d.data);
}

/*******************************
 **    Overload > operator    **
 ******************************/
template <typename datatype>
bool TreeNode<datatype>::operator>(const datatype& d) const {
    return (data>d);
}

template <typename datatype>
bool TreeNode<datatype>::operator>(const TreeNode<datatype>& d) const {
    return (data>d.data);
}

/*******************************
 **    Overload < operator    **
 ******************************/
template <typename datatype>
bool TreeNode<datatype>::operator<(const datatype& d) const {
    return (data<d);
}

template <typename datatype>
bool TreeNode<datatype>::operator<(const TreeNode<datatype>& d) const {
    return (data<d.data);
}

/*****************************************
 **    Overload Modifying = operator    **
 ****************************************/
template <typename datatype>
TreeNode<datatype>& TreeNode<datatype>::operator=(const datatype& d) {
    data = d;

    return *this;
}

template <typename datatype>
TreeNode<datatype>& TreeNode<datatype>::operator=(const TreeNode<datatype>& d) {
    data = d.data;

    return *this;
}


/***********************************************
 **    Overload OStream Insertion Operator    **
 **********************************************/
template <typename datatype2>
std::ostream& operator<< (std::ostream& out, const TreeNode<datatype2>& node) {
    out << node.data;
    return out;
}

template <typename datatype2>
std::ostream& operator<< (std::ostream& out, const TreeNode<datatype2>* node) {
    out << node->data;
    return out;
}



/***********************************************
 **    Overload FStream Insertion Operator    **
 **********************************************/
template <typename datatype2>
std::fstream& operator<< (std::fstream& out, const TreeNode<datatype2>& node) {
    out << node.data;
    return out;
}

template <typename datatype2>
std::fstream& operator<< (std::fstream& out, const TreeNode<datatype2>* node) {
    out << node->data;
    return out;
}



/*******************
 **    getData    **
 ******************/
template <typename datatype>
datatype& TreeNode<datatype>::getData() {
    return data;
}

/*******************
 **    getRight    **
 ******************/
template <typename datatype>
TreeNode<datatype>* TreeNode<datatype>::getRight() const {
    return right;
}

/*******************
 **    getLeft    **
 ******************/
template <typename datatype>
TreeNode<datatype>* TreeNode<datatype>::getLeft() const {
    return left;
}

/*******************
 **    setRight    **
 ******************/
template <typename datatype>
void TreeNode<datatype>::setRight(TreeNode<datatype>* newNode) {
    right = newNode;
}

/*******************
 **    setLeft    **
 ******************/
template <typename datatype>
void TreeNode<datatype>::setLeft(TreeNode<datatype>* newNode) {
    left = newNode;
}

/*********************
 **    getHeight    **
 ********************/
template <typename datatype>
int TreeNode<datatype>::getHeight() {
    return height;
}




#endif //P04_TreeNode_H