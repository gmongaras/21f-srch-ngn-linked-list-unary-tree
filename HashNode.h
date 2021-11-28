#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H



template <typename K, typename V>
class HashNode {
    template <typename K3, typename V3, typename F3>
    friend class HashMap;


private:
    K key;
    V value;

    HashNode* next; // The next value with the same key to deal with overlap


public:
    /**
     * Constructors
     */
    HashNode(const K& newKey, const V& newValue);
    HashNode(const HashNode<K,V>& node);



    /**
     * Set Methods
     */
    void setKey(const K& newKey);
    void setValue(const V& newValue);
    void setNext(HashNode<K, V>* node);


    /**
     * Get Methods
     */
    K& getKey();
    V& getValue();
    HashNode* getNext();


    /**
     * Overload Assignment Operator
     */
    HashNode& operator=(const HashNode<K,V>& node);
    HashNode& operator=(const V& newValue);


    /**
     * Overload ostream insertion operator to print the contents of this list
     * to ostream's output stream in the first argument.
     */
    template <typename K2, typename V2>
    friend std::ostream& operator<< (std::ostream&, const HashNode<K2, V2>&);
    template <typename K2, typename V2>
    friend std::ostream& operator<< (std::ostream&, const HashNode<K2, V2>*&);
};











/************************
 **    Constructors    **
 ***********************/
template <typename K, typename V>
HashNode<K,V>::HashNode(const K& newKey, const V& newValue) {
    key = newKey;
    value = newValue;
    next = nullptr;
}
template <typename K, typename V>
HashNode<K,V>::HashNode(const HashNode<K,V> &node) {
    key = node.key;
    value = node.value;
    next = node.next;
}



/**********************
 **    Set Method    **
 *********************/
template <typename K, typename V>
void HashNode<K, V>::setKey(const K &newKey) {
    key = newKey;
}
template <typename K, typename V>
void HashNode<K, V>::setValue(const V &newValue) {
    value = newValue;
}
template <typename K, typename V>
void HashNode<K, V>::setNext(HashNode<K, V> *node) {
    next = node;
}



/***********************
 **    Get Methods    **
 **********************/
template <typename K, typename V>
K& HashNode<K, V>::getKey() {
    return key;
}
template <typename K, typename V>
V& HashNode<K, V>::getValue() {
    return value;
}
template <typename K, typename V>
HashNode<K, V>* HashNode<K, V>::getNext() {
    return next;
}



/****************************************
 **    Overload Assignment Operator    **
 ***************************************/
template <typename K, typename V>
HashNode<K, V>& HashNode<K, V>::operator=(const HashNode<K, V> &node) {
    key = node.key;
    value = node.value;
    next = node.next;

    return *this;
}
template <typename K, typename V>
HashNode<K, V>& HashNode<K, V>::operator=(const V &newValue) {
    value = newValue;

    return *this;
}



/***********************************************
 **    Overload OStream Insertion Operator    **
 **********************************************/
template <typename K2, typename V2>
std::ostream& operator<<(std::ostream& out, const HashNode<K2, V2>& node) {
    // Display this node's value
    out << node.key << ": " << node.value;

    // Display the rest of the node's with the same value
    HashNode<K2, V2>* temp = node.getNext();
    while (temp != nullptr) {
        out << ", " << temp;
        temp = temp->getNext();
    }

    return out;
}
template <typename K2, typename V2>
std::ostream& operator<<(std::ostream& out, const HashNode<K2, V2>*& node) {
    // Display this node's value
    out << node->key << ": " << node->value;

    // Display the rest of the node's with the same value
    HashNode<K2, V2>* temp = node->getNext();
    while (temp != nullptr) {
        out << ", " << temp;
        temp = temp->getNext();
    }


    return out;
}


#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H
