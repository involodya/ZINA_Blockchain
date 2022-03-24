#include "hash_functions.h"
/*
// TODO realization
rsa_pair_t generateKeys() {
    uint8_t *a = new uint8_t;
    uint8_t *b = new uint8_t;
    return {a, b};
}
*/
void f() {std::cout << "HI";}

hash_t sha256(const std::string &hash_object) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hash_object.c_str(), hash_object.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (uint8_t i: hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return ss.str();
}

hash_t calculateHash(const Block &block) {
    std::stringstream ss;
    ss << block._nonce << block._previousBlockHash << block._currentBlockHash;
    for (const Transaction& transaction : block._listOfTransactions) {
        ss << '{' << transaction << '}';
    }
    return sha256(ss.str());
}

bool hashIsCorrect(hash_t current_hash) { // hash is correct in our terms when it starts with
    for (int i = 0; i < REQUIRED_LEN_OF_ZEROS_PREFIX_IN_HASH; ++i) {
        if (current_hash[i] != '0') {
            return false;
        }
    }
    return true;
}
