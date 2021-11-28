#ifndef INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H
#define INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H


#include "murmur3/MurmurHash3.h"
#include <cstring>


// Struct for the hash function
template <typename K>
struct KeyHash {
    unsigned long hash(const std::string& str) {
        uint64_t seed = 1;
        uint64_t hash_otpt[2];  // allocate 128 bits
        const char* key = str.c_str(); // The key to hash
        MurmurHash3_x86_128(key, (uint64_t)strlen(key), seed, hash_otpt);

        // Reduce the size of the hash
        std::string h = std::to_string(*hash_otpt);
        h = h.substr(0, 2);
        return std::stol(h);
    }
};



#endif // INC_21F_FINAL_PROJ_TEMPLATE_HASHFUNCTION_H