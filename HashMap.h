#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H




#include "HashNode.h"
#include "HashFunction.h"
#include <vector>
#include <functional>



template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
private:
    int size; // The size of the hashmaps
    std::vector<HashNode<K, V>*> map; // The hashmap
    F hashFunc; // The hash function



public:
    /**
     * Constructors and Destructor
     */
    HashMap();
    HashMap(HashMap& oldMap);
    ~HashMap();

    /**
     * addPair Method
     * Adds a key-value pair to the map
     * @param newKey The key to add
     * @param newVal The value to add
     * @param equalityFunc The function to use if the key was found in the map.
     */
    void addPair(K& newKey, V& newValue, std::function<void(V& oldValue, V& newValue)> equalityFunction);

    /**
     * getValue Method
     * Retrieve a value from the map at the location of a given key
     * @param searchKey The key used to search for the value
     * @return The value at the given key
     */
    V& getValue(K& searchKey);

    /**
     * Overloaded [] Operator
     * Retrieve a value from the map at the location of a given key
     * @param searchKey The key used to search for the value
     * @return The value at the given key
     */
    V& operator[](K& searchKey);
};






/***************************************
 **    Constructors and Destructor    **
 **************************************/
template <typename K, typename V, typename F>
HashMap<K, V, F>::HashMap() {
    size = 4194304;
    map.resize(size);
}
template <typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(HashMap<K, V, F> &oldMap) {
    // Set the size
    size = 4194304;

    // Resize the vector map
    map.resize(size);

    // Iterate over all values in the vector and add it to this map
    for (int i = 0; i < oldMap.map.size(); i++) {
        // Add a new node to this map
        map[i] = new HashNode<K, V>(oldMap[i]);

        // Iteration pointer
        HashNode<K, V>* newCurr = map[i];
        HashNode<K, V>* oldCurr = oldMap[i];

        // Iterate over all nodes in the old map for this specific index
        // and add those values to this map
        while (oldCurr->nextNode != nullptr) {
            // Create a new node and add it to the new map's linked list
            newCurr->nextNode = new HashNode<K, V>(oldCurr);

            // Iterate to the next nodes in the list
            newCurr = newCurr->nextNode;
            oldCurr = oldCurr->nextNode;
        }
    }
}

template <typename K, typename V, typename F>
HashMap<K, V, F>::~HashMap<K, V, F>() {
    // Iterate over all values in the vector and delete them
    for (int i = 0; i < map.size(); i++) {
        // Iteration pointers
        HashNode<K, V>* curr = map[i];

        // Iterate over all nodes in the old map for this specific index
        // and delete the values
        while (curr != nullptr) {
            // Get the current node
            HashNode<K, V>* temp = curr;

            // Iterate to the next nodes in the list
            curr = curr->nextNode;

            // Delete the temp pointer
            delete temp;
        }
    }
}




/*******************
 **    addPair    **
 ******************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::addPair(K& newKey, V& newValue, std::function<void(V& oldValue, V& newValue)> equalityFunction) {
    // Hash the given key
    long keyHash = hashFunc.hash(newKey);

    // Get the location in the vector of the hashed key
    HashNode<K, V>*& node = map[keyHash];

    // If the value is nullptr, add a new node to that location
    if (node == nullptr) {
        node = new HashNode<K, V>(newKey, newValue);
    }

    // If the value is not nullptr and the current node's key contains
    // the key of the given key, call the equality function
    else if (node->key == newKey) {
        equalityFunction(node->value, newValue);
    }

    // If the value is not nullptr and the current node's key does not contain
    // the key of the given key, search for the key in the linked list
    else {
        // Iterate to the end of the linked list
        while (node != nullptr) {
            // If the key is found, call the equality function
            if (node->key == newKey) {
                equalityFunction(node->value, newValue);
                return;
            }

            // If the key is not found, move the pointer
            node = node->nextNode;
        }

        // If the current node is nullptr, add a new node to the end of the list
        node = new HashNode<K, V>(newKey, newValue);
    }
}



/***************************
 **    getValue Method    **
 **************************/
template <typename K, typename V, typename F>
V& HashMap<K, V, F>::getValue(K& searchKey) {
    // Hash the given key
    long keyHash = hashFunc.hash(searchKey);

    // Get the location in the vector of the hashed key
    HashNode<K, V>*& node = map[keyHash];

    // If the value is nullptr, raise an exception
    if (node == nullptr) {
        throw std::runtime_error("Key has no value");
    }

    // If the node is not nullptr and the key is found, return the value
    else if (node->key == searchKey) {
        return node->value;
    }

    // If the key is not found, search the linked list
    else {
        // Iterate to the end of the linked list
        while (node != nullptr) {
            // If the key is found, return the value
            if (node->key == searchKey) {
                return node->value;
            }

            // If the key is not found, move the iterator
            node = node->nextNode;
        }

        // If the node wasn't found, raise and error
        throw std::runtime_error("Key has no value");
    }
}



/**********************************
 **    Overloaded [] Operator    **
 *********************************/
template <typename K, typename V, typename F>
V& HashMap<K, V, F>::operator[](K& searchKey) {
    // Hash the given key
    long keyHash = hashFunc.hash(searchKey);

    // Get the location in the vector of the hashed key
    HashNode<K, V>*& node = map[keyHash];

    // If the value is nullptr, raise an exception
    if (node == nullptr) {
        throw std::runtime_error("Key has no value");
    }

    // If the node is not nullptr and the key is found, return the value
    else if (node->key == searchKey) {
        return node->value;
    }

    // If the key is not found, search the linked list
    else {
        // Iterate to the end of the linked list
        while (node != nullptr) {
            // If the key is found, return the value
            if (node->key == searchKey) {
                return node->value;
            }

            // If the key is not found, move the iterator
            node = node->nextNode;
        }

        // If the node wasn't found, raise and error
        throw std::runtime_error("Key has no value");
    }
}





#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
