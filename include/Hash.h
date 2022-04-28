#pragma once

#include <string>
#include <iomanip>
#include <iostream>

// #define BOOST_ERROR_CODE_HEADER_ONLY
// #include <boost/system/error_code.hpp>
// #include <boost/asio/ssl/impl/src.hpp>
#include <openssl/sha.h>

struct Hash {
    uint8_t *_hash;

    Hash();

    explicit Hash(const std::string &hash_object);

    Hash(const Hash& other);

    Hash &operator=(const Hash& other);

    ~Hash();

    bool operator==(const Hash &other) const;

    bool operator<(const Hash &other) const;

    void dbg() const;
};


std::ostream &operator<<(std::ostream &out, const Hash &hash);
