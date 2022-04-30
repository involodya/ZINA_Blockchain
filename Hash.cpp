#include <cstring>
#include "Hash.h"

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

Hash &Hash::operator=(const Hash &other) {
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

Hash &Hash::set(const std::string &hash) {
    static std::unordered_map<char, uint8_t> hex = {{'0', 0},
                                                    {'1', 1},
                                                    {'2', 2},
                                                    {'3', 3},
                                                    {'4', 4},
                                                    {'5', 5},
                                                    {'6', 6},
                                                    {'7', 7},
                                                    {'8', 8},
                                                    {'9', 9},
                                                    {'a', 10},
                                                    {'b', 11},
                                                    {'c', 12},
                                                    {'d', 13},
                                                    {'e', 14},
                                                    {'f', 15}};
    delete[] _hash;
    _hash = new uint8_t[HASH_SIZE];
    for (int i = 2; i < HASH_SIZE + 2; i += 2) {
        _hash[i / 2 - 1] = hex[hash[i]] * 16 + hex[hash[i + 1]];
    }

    return *this;
}

template<class Archive>
void Hash::serialize(Archive &ar, const unsigned int version) {
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        ar & _hash[i];
    }
}


std::ostream &operator<<(std::ostream &out, const Hash &hash) {
    out << "0x";
    out.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        // TODO ADD setw and setfill IN ALL SAME PLACES
        out << std::setw(2) << std::setfill('0') << static_cast<int>(hash._hash[i]);
    }
    out.unsetf(std::ios::hex);
    return out;
}
