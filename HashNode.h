#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H



template <typename K, typename V>
class HashNode {
    template <typename K3, typename V3, typename F3>
    friend class HashMap;


private:
    K key;
    V value;

    // The next hashnode in the linked list
    HashNode<K, V>* nextNode;

    // The character used to split the key and value when in a file
    std::string keyValSplit;


public:
    /**
     * Constructors
     */
    HashNode();
    HashNode(K& newKey, V& newValue);
    HashNode(HashNode<K, V>& node);


    /**
     * Set Methods
     */
    void setKey(const K& newKey);
    void setValue(V& newVal);
    void setNext(const HashNode<K, V>* node);

    /**
     * Get Methods
     */
    K& getKey();
    V& getValue();
    HashNode<K, V>*& getNext();

    /**
     * Overload ostream insertion operator to print the contents of this list
     * to ostream's output stream in the first argument.
     */
    template <typename K2, typename V2>
    friend std::ostream& operator<< (std::ostream&, const HashNode<K2, V2>&);
    template <typename K2, typename V2>
    friend std::ostream& operator<< (std::ostream&, const HashNode<K2, V2>*);

    /**
     * Overload fstream insertion operator to print the contents of this list
     * to fstream's output stream in the first argument.
     */
    template <typename K2, typename V2>
    friend std::fstream& operator<< (std::fstream&, const HashNode<K2, V2>&);
    template <typename K2, typename V2>
    friend std::fstream& operator<< (std::fstream&, const HashNode<K2, V2>*);
};






/************************
 **    Constructors    **
 ***********************/
template <typename K, typename V>
HashNode<K, V>::HashNode() {
    nextNode = nullptr;
    keyValSplit = "|||";
}
template <typename K, typename V>
HashNode<K, V>::HashNode(K& newKey, V& newVal) {
    key = newKey;
    value = newVal;
    nextNode = nullptr;
    keyValSplit = "|||";
}
template <typename K, typename V>
HashNode<K, V>::HashNode(HashNode<K, V>& node) {
    key = node.key;
    value = node.value;
    nextNode = nullptr;
    keyValSplit = "|||";
}



/***********************
 **    Set Methods    **
 **********************/
template <typename K, typename V>
void HashNode<K, V>::setKey(const K& newKey) {
    key = newKey;
}

template <typename K, typename V>
void HashNode<K, V>::setValue(V& newVal) {
    value = newVal;
}

template <typename K, typename V>
void HashNode<K, V>::setNext(const HashNode<K, V>* node) {
    nextNode = node;
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
HashNode<K, V>*& HashNode<K, V>::getNext() {
    return nextNode;
}



/***********************************************
 **    Overload OStream Insertion Operator    **
 **********************************************/
template <typename K2, typename V2>
std::ostream& operator<< (std::ostream& out, const HashNode<K2, V2>& node) {
    out << node.key << node.keyValSplit << node.value;
    return out;
}

template <typename K2, typename V2>
std::ostream& operator<< (std::ostream& out, const HashNode<K2, V2>* node) {
    out << node->key << node->keyValSplit << node->value;
    return out;
}



/***********************************************
 **    Overload FStream Insertion Operator    **
 **********************************************/
template <typename K2, typename V2>
std::fstream& operator<< (std::fstream& out, const HashNode<K2, V2>& node) {
    out << node.key;
    out << node.keyValSplit;
    out << node.value;
    return out;
}

template <typename K2, typename V2>
std::fstream& operator<< (std::fstream& out, const HashNode<K2, V2>* node) {
    out << node->key;
    out << node->keyValSplit;
    out << node->value;
    return out;
}






#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H
