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

#include "definitions.h"
#include "constants.h"
#include "Block.h"
#include "Transaction.h"

bool isHashCorrect(const hash_t &current_hash);

struct ecc_pair_t {
    secret_key_t secret_key;
    public_key_t public_key;

    ~ecc_pair_t() {
        memset(secret_key, 0, SECRET_KEY_SIZE);
        delete[] secret_key;
    }
};
