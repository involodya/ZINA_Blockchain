#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <unordered_map>

// #define BOOST_ERROR_CODE_HEADER_ONLY
// #include <boost/system/error_code.hpp>
// #include <boost/asio/ssl/impl/src.hpp>
#include <openssl/sha.h>

const size_t HASH_SIZE = SHA256_DIGEST_LENGTH;

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


struct Hash {
    uint8_t *_hash = nullptr;

    Hash();

    explicit Hash(const std::string &hash_object);

    Hash(const Hash &other);

    Hash &operator=(const Hash &other);

    Hash &set(const std::string &hash);

    ~Hash();

    bool operator==(const Hash &other) const;

    bool operator<(const Hash &other) const;

    void dbg() const;
};


std::ostream &operator<<(std::ostream &out, const Hash &hash);


static Hash THRESHOLD_HASH = Hash().set("0x0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");