#pragma once

#include <string>
#include <iomanip>
#include <iostream>

#include <openssl/sha.h>

struct Hash {
    uint8_t *_hash;

    Hash();

    explicit Hash(const std::string &hash_object);

    Hash &operator=(const Hash& other);

    bool operator==(const Hash &other) const;

    bool operator<(const Hash &other) const;

    void dbg() const;
};


std::ostream &operator<<(std::ostream &out, const Hash &hash);
