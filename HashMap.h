#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H




#include "HashNode.h"
#include "HashFunction.h"
#include <vector>
#include <functional>
#include <fstream>



template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
private:
    int size; // The size of the hashmaps
    std::vector<HashNode<K, V>*> map; // The hashmap
    F hashFunc; // The hash function
    int numUnique; // The number of unique items entered
    std::string splitChar; // Character used to split each part of a bucket



public:
    /**
     * Constructors and Destructor
     */
    HashMap();
    HashMap(HashMap& oldMap);
    ~HashMap();

    /**
     * clear Method
     * Clear all contents in the hash map and frees all the memory
     */
    void clear();

    /**
     * saveTable Method
     * Saves all contents to a given files in a rereadable format
     * @param filename The file to save the table to
     */
    void saveTable(std::string& filename);

    /**
     * loadTable Method
     * Loads all contents from a given files into this table
     * @param filename The file to read from
     * @param equalityFunc The function to use if the key was found in the map.
     */
    void loadTable(std::string& filename, std::function<void(V& oldValue, V& newValue)> equalityFunction);

    /**
     * addPair Method
     * Adds a key-value pair to the map
     * @param newKey The key to add
     * @param newVal The value to add
     * @param equalityFunc The function to use if the key was found in the map.
     */
    void addPair(K& newKey, V& newValue, std::function<void(V& oldValue, V& newValue)> equalityFunction);

    /**
     * addNode Method
     * Adds a hash node to the map
     * @param node The node to add
     * @param equalityFunc The function to use if the key was found in the map.
     */
    void addNode(HashNode<K, V>*& newNode, std::function<void(V& oldValue, V& newValue)> equalityFunction);

    /**
     * Overloaded [] Operator
     * Retrieve a value from the map at the location of a given key
     * @param searchKey The key used to search for the value
     * @return The value at the given key
     */
    V& operator[](K& searchKey);

    /**
     * getUnique Method
     * @return The number of unique items entered into this hash map
     */
    int getUnique();
};








/***************************************
 **    Constructors and Destructor    **
 **************************************/
template <typename K, typename V, typename F>
HashMap<K, V, F>::HashMap() {
    size = 4194304;
    map.resize(size);
    numUnique = 0;
    splitChar = "|";
}
template <typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(HashMap<K, V, F> &oldMap) {
    // Set the size
    size = 4194304;
    numUnique = oldMap.numUnique;
    splitChar = "|";

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
    clear();
}



/************************
 **    clear Method    **
 ***********************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::clear() {
    // If the map is already cleared, don't clear the map
    if (numUnique == 0) {
        return;
    }

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
    map.clear();
    map.resize(size);
    numUnique = 0;
}



/****************************
 **    saveTable Method    **
 ***************************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::saveTable(std::string &filename) {
    // Open a file for writing
    std::fstream file(filename.c_str(), std::fstream::out);



    // Iterate over all values in the linked list and add all non-empty buckets
    // to the files
    for (int i = 0; i < map.size(); i++) {
        // If the current value is not empty, add it to the file
        if (map[i] != nullptr) {
            // Holds each node in the bucket
            HashNode<K, V>* temp = map[i];

            // Iterate over each part of the bucket
            while (temp != nullptr) {
                // Add the node to the file
                file << temp;
                if (temp->nextNode != nullptr) {
                    file << splitChar[0];
                }

                // Move to the next node
                temp = temp->nextNode;
            }

            // Go to the next line
            file << std::endl;
        }
    }



    // Close the file
    file.close();
}



/****************************
 **    loadTable Method    **
 ***************************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::loadTable(std::string &filename, std::function<void(V& oldValue, V& newValue)> equalityFunction) {
    // Open a file for reading
    std::ifstream file(filename.c_str(), std::fstream::in);
    HashNode<K, V> t;


    // If the file is open, read it
    if (file) {
        // Iterate until the end of the file is met
        while (!file.eof()) {
            // Get a line from the file
            std::string buff;
            std::getline(file, buff);

            // If the buffer is empty, go to the next line
            if (buff.empty()) {
                continue;
            }

            // Get the key and value from the buffer
            std::vector<std::string> keyVal = tokStr(buff, t.keyValSplit[0], 1);
            std::string key = keyVal[0];
            std::string value = keyVal[1];
            K keyK;
            keyK = key;
            V valueV;
            valueV = value;

            // Add the node to the map
            addPair(keyK, valueV, equalityFunction);
        }
    }
    // If the file is not open, throw an error
    else {
        throw std::runtime_error("File not open");
    }


    // Close the file
    file.close();
}




/*******************
 **    addPair    **
 ******************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::addPair(K& newKey, V& newValue, std::function<void(V& oldValue, V& newValue)> equalityFunction) {
    // Hash the given key
    long keyHash = hashFunc.hash(newKey, size);

    // Get the location in the vector of the hashed key
    HashNode<K, V>* node = map[keyHash];

    // If the value is nullptr, add a new node to that location
    if (node == nullptr) {
        numUnique++;
        map[keyHash] = new HashNode<K, V>(newKey, newValue);
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
        HashNode<K, V>* prev;
        while (node != nullptr) {
            // If the key is found, call the equality function
            if (node->key == newKey) {
                equalityFunction(node->value, newValue);
                return;
            }

            // If the key is not found, move the pointer
            prev = node;
            node = node->nextNode;
        }

        // If the current node is nullptr, add a new node to the end of the list
        prev->nextNode = new HashNode<K, V>(newKey, newValue);
        numUnique++;
    }
}



/*******************
 **    addNode    **
 ******************/
template <typename K, typename V, typename F>
void HashMap<K, V, F>::addNode(HashNode<K, V>*& newNode, std::function<void(V& oldValue, V& newValue)> equalityFunction) {
    // Hash the given key
    long keyHash = hashFunc.hash(newNode->key, size);

    // Get the location in the vector of the hashed key
    HashNode<K, V>* node = map[keyHash];

    // If the value is nullptr, add a new node to that location
    if (node == nullptr) {
        numUnique++;
        map[keyHash] = newNode;
    }

    // If the value is not nullptr and the current node's key contains
    // the key of the given key, call the equality function
    else if (node->key == newNode->key) {
        equalityFunction(node->value, newNode->value);
    }

    // If the value is not nullptr and the current node's key does not contain
    // the key of the given key, search for the key in the linked list
    else {
        // Iterate to the end of the linked list
        HashNode<K, V>* prev;
        while (node != nullptr) {
            // If the key is found, call the equality function
            if (node->key == newNode->key) {
                equalityFunction(node->value, newNode->value);
                return;
            }

            // If the key is not found, move the pointer
            prev = node;
            node = node->nextNode;
        }

        // If the current node is nullptr, add a new node to the end of the list
        prev->nextNode = newNode;
        numUnique++;
    }
}



/**********************************
 **    Overloaded [] Operator    **
 *********************************/
template <typename K, typename V, typename F>
V& HashMap<K, V, F>::operator[](K& searchKey) {
    // Hash the given key
    long keyHash = hashFunc.hash(searchKey, size);

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



/****************************
 **    getUnique Method    **
 ***************************/
template <typename K, typename V, typename F>
int HashMap<K, V, F>::getUnique() {
    return numUnique;
}





#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
