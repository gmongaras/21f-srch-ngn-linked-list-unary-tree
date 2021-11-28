// Some methods were implemented from the link below to get started on the class/
// https://aozturk.medium.com/simple-hash-map-hash-table-implementation-in-c-931965904250





#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H

#include "HashNode.h"
#include "HashFunction.h"


template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
private:
    HashNode<K, V>** table; // The hashmap
    F hashFunc; // The hash function
    long tableSize; // The size of the hash table



public:
    /**
     * Constructors and Destructor
     */
    HashMap();
    HashMap(const HashMap<K, V, F>& map);
    ~HashMap();

    /**
     * getValue Function
     * Get the value at a given key hash value
     * @param key The key to search for
     * @param val A variable passed in to store the value at the key if found
     * @return True if the key is found, false otherwise
     */
    bool getValue(const K& key, V& value);

    /**
     * Overloaded [] Operator
     * Returns the value at a given key hash value
     * @param key The key to search for
     * @return The value at the given key
     */
    V& operator[](const K& key);

    /**
     * update Method
     * Updates the map given a key and value
     * @param key The key to search for
     * @param value The value to set at that key
     * @return The value at the given key
     */
    V& update(const K& key, const V& value);
};







/***************************************
 **    Constructors and Destructor    **
 **************************************/
template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap() {
    // Initialize the hashmap
    tableSize = 4194304;
    table = new HashNode<K, V> *[tableSize]();
}

template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(const HashMap<K, V, F> &map) {
    // Set the hashmap size and initialize it
    tableSize = map.tableSize;
    table = new HashNode<K, V> *[tableSize]();

    // Copy all hashmap values
    for (int i = 0; i < tableSize; i++) {
        // If the current value in the table to copy is nullptr, skip
        // this iteration
        if (map.table[i].next == nullptr) {
            table[i] = nullptr;
            continue;
        }

        // Iterate over all values in the current HashNode to copy
        // the concurrent values
        table[i] = new HashNode<K, V>(map.table[i]);
        HashNode<K, V>* currNew = table[i]->getNext();
        HashNode<K, V>* currOld = map.table[i].getNext();
        while (currOld->next != nullptr) {
            currNew->next = new HashNode<K, V>(currOld->next);
            currOld = currOld->getNext();
            currNew = currNew->getNext();
        }
    }
}

template<typename K, typename V, typename F>
HashMap<K, V, F>::~HashMap<K, V, F>() {
    // Destroy all hashmap values
    for (int i = 0; i < tableSize; i++) {
        // Iterate over all values in the current HashNode to delete
        // the concurrent values
        HashNode<K, V>* curr = table[i];
        while (curr != nullptr) {
            HashNode<K, V>* temp = curr;
            curr = curr->getNext();
            delete temp;
        }
        table[i] = nullptr;
    }

    // Destroy the hashmap
    delete [] table;
}



/***************************
 **    getValue Method    **
 **************************/
template<typename K, typename V, typename F>
bool HashMap<K, V, F>::getValue(const K &key, V& value) {
    // Hash the given value and get the value corresponding to it
    unsigned long hashValue = hashFunc.hash(key);
    HashNode<K, V>* val = table[hashValue];

    // Iterate till the given key is found
    while (val != nullptr) {
        // If the key is found, return true and store the value
        if (val->key == key) {
            value = val->getValue();
            return true;
        }

        // If the key is not found, move the iterator
        val = val->getNext();
    }

    // Return false if the key wasn't found
    return false;
}



/**********************************
 **    Overloaded [] Operator    **
 *********************************/
template<typename K, typename V, typename F>
V& HashMap<K, V, F>::operator[](const K &key) {
    // Hash the given value and get the value corresponding to it
    unsigned long hashValue = hashFunc.hash(key);
    HashNode<K, V>* val = table[hashValue];

    // Iterate till the given key is found
    while (val != nullptr) {
        // If the key is found, return the value
        if (val->key == key) {
            return val->getValue();
        }

        // If the key is not found, move the iterator
        val = val->getNext();
    }

    // Throw an error if the key wasn't found
    throw std::runtime_error("Key not found");
}



/*************************
 **    update Method    **
 ************************/
template<typename K, typename V, typename F>
V& HashMap<K, V, F>::update(const K &key, const V &value) {
    // Hash the given key
    unsigned long hashValue = hashFunc.hash(key);

    // Pointers to find the location to put the given key-value pair
    HashNode<K, V>* prev = nullptr;
    HashNode<K, V>* curr = table[hashValue];

    // Iterate until the location for the node is found
    while (curr != nullptr && curr->getKey() != key) {
        prev = curr;
        curr = curr->getNext();
    }

    // If the current pointer is nullptr, then there is either nothing at this
    // index in the hash table or we reached the end of the linked list
    if (curr == nullptr) {
        // If prev is nullptr, put the node at the hashed value in the hashmap
        if (prev == nullptr) {
            table[hashValue] = new HashNode<K, V>(key, value);
            return table[hashValue]->value;
        }
        // If prev is not nullptr, set the next value to nullptr
        // as the value wasn't found in the linked list
        else {
            prev->setNext(new HashNode<K, V>(key, value));
            return prev->next->value;
        }
    }

    // If the key was found, update the node
    else {
        curr->setValue(value);
        return curr->value;
    }
}





#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
