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
};






/************************
 **    Constructors    **
 ***********************/
template <typename K, typename V>
HashNode<K, V>::HashNode() {
    nextNode = nullptr;
}
template <typename K, typename V>
HashNode<K, V>::HashNode(K& newKey, V& newVal) {
    key = newKey;
    value = newVal;
    nextNode = nullptr;
}
template <typename K, typename V>
HashNode<K, V>::HashNode(HashNode<K, V>& node) {
    key = node.key;
    value = node.value;
    nextNode = nullptr;
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






#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHNODE_H
