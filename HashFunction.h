/**
 * Outline: This struct is used to hash a string using the murmur3 hash function
 * Note: The hash function (murmur3) I used was a part of a set of multiple algorithms
 *       which can be found at the following link: https://github.com/aappleby/smhasher
 * Date: 12/4/21
 * Author: Gabriel Mongaras
 * Input: A string to hash and a table size
 * Output: A hashed value of type long that fits into the table
 */





#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H


#include "murmur3/MurmurHash3.h"
#include <cstring>



// Struct for the hash function
template <typename K>
struct KeyHash {
    unsigned long hash(const std::string& str, int tableSize) {
        uint64_t seed = 1;
        uint64_t hash_otpt[2];  // allocate 128 bits
        const char* key = str.c_str(); // The key to hash
        MurmurHash3_x64_128(key, (uint64_t)strlen(key), seed, hash_otpt);

        // Reduce the size of the has
        std::string h = std::to_string(*hash_otpt);
        return std::stoll(h.substr(0, 18))%(long)tableSize;
    }
};



#endif // INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H