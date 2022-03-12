#include "hash_functions.h"

// TODO realization
rsa_pair_t generateKeys() {
    uint8_t *a = new uint8_t;
    uint8_t *b = new uint8_t;
    return {a, b};
}

// TODO realization
hash_t calculateHash(const Block&) {
    hash_t hash_of_block = "todo";
    return hash_of_block;
}

bool hashIsCorrect(hash_t current_hash) { // hash is correct in our terms when it starts with
    for (int i = 0; i < REQUIRED_LEN_OF_ZEROS_PREFIX_IN_HASH; ++i) {
        if (current_hash[i] != '0') {
            return false;
        }
    }
    return true;
}