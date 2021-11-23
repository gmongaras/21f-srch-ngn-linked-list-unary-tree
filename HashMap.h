#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H

#include "HashNode.h"


template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
    /**
     * Constructors
     */
    HashMap();
    HashMap(const HashNode<K, V>* node);
    HashMap(const HashNode<K, V>& node);
    HashMap(const HashMap<K, V, F>& map);

    /**
     * getValue Function
     * Returns the value at a given key hash value
     * @param key The key to search for
     * @return The value at the given key
     */
    V& getValue(const K& key);

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



#endif //INC_21F_FINAL_PROJ_TEMPLATE_HASHMAP_H
