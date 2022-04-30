#pragma once

#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <iomanip>
#include <string>

#include <sys/random.h>
#include <secp256k1.h>

#include "Block.h"
#include "Transaction.h"

bool isHashCorrect(const hash_t &current_hash);

struct ecc_pair_t {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    secret_key_t secret_key;
    public_key_t public_key;

    ~ecc_pair_t() {
        memset(secret_key, 0, SECRET_KEY_SIZE);
        delete[] secret_key;
    }
};

template<class Archive>
void ecc_pair_t::serialize(Archive &ar, const unsigned int version) {
    for (size_t i = 0; i < SECRET_KEY_SIZE; ++i) {
        secret_key[i];
    }
    for (size_t i = 0; i < 64; ++i) {
        public_key.data[i];
    }
}
