#include <cstring>
#include "Hash.h"

const size_t HASH_SIZE = SHA256_DIGEST_LENGTH;
const Hash DEFAULT_HASH = Hash();

Hash::Hash() : _hash(new uint8_t[HASH_SIZE]()) {}

Hash::Hash(const std::string &hash_object) : _hash(new uint8_t[HASH_SIZE]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hash_object.c_str(), hash_object.size());
    SHA256_Final(_hash, &sha256);
}

Hash::Hash(const Hash &other) {
    _hash = new uint8_t[HASH_SIZE];
    memcpy(_hash, other._hash, sizeof(uint8_t) * HASH_SIZE);
}

Hash &Hash::operator=(const Hash& other) {
    if (this == &other) {
        return *this;
    }
    this->~Hash();

    _hash = new uint8_t[HASH_SIZE];
    memcpy(_hash, other._hash, sizeof(uint8_t) * HASH_SIZE);

    return *this;
}

bool Hash::operator==(const Hash &other) const {
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        if (_hash[i] != other._hash[i]) {
            return false;
        }
    }
    return true;
}

bool Hash::operator<(const Hash &other) const {
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        if (_hash[i] < other._hash[i]) {
            return true;
        } else if (_hash[i] > other._hash[i]) {
            return false;
        }
    }
    return false;
}

void Hash::dbg() const {
    std::cerr << "Hash:" << std::endl;
    std::cerr << "\thash: " << *this << std::endl;
}

Hash::~Hash() {
    delete[] _hash;
}


std::ostream &operator<<(std::ostream &out, const Hash &hash) {
    out << "0x";
    out.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        out << static_cast<int>(hash._hash[i]);
    }
    out.unsetf(std::ios::hex);
    return out;
}
