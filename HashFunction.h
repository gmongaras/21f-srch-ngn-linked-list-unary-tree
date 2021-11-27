#include "murmur3/MurmurHash3.cpp"
#include <cstring>


// Struct for the hash function
template <typename K>
struct KeyHash {
    unsigned long hash(std::string& str) {
        uint64_t seed = 1;
        uint64_t hash_otpt[2];  // allocate 128 bits
        const char* key = str.c_str(); // The key to hash
        MurmurHash3_x64_128(key, (uint64_t)strlen(key), seed, hash_otpt);
        return *hash_otpt;
    }
};
