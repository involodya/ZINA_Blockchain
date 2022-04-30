#pragma once
#include "definitions.cpp"

const nonce_t MAX_NONCE = 1e5;
const size_t REQUIRED_LEN_OF_ZEROS_PREFIX_IN_HASH = 4;
const size_t MAX_LENGTH_OF_BRANCHING_CHAIN = 6;
const ZINA BASIC_VALUE_OF_COINBASE_TRANSACTION(static_cast<size_t>(1));

const size_t PUBLIC_KEY_SIZE = 32;
const size_t SECRET_KEY_SIZE = 32;
const size_t SIGNATURE_SIZE = 32;
const size_t COMPRESSED_PUBLIC_KEY_SIZE = 33;
const size_t SERIALIZED_SIGNATURE_SIZE = 64;

struct ecc_pair_t {
    secret_key_t secret_key;
    public_key_t public_key;

    ~ecc_pair_t() {
        memset(secret_key, 0, SECRET_KEY_SIZE);
        delete[] secret_key;
    }
};
