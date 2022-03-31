#pragma once

#include "ZINA.h"
#include "Hash.h"

#include <iostream>

#include <secp256k1.h>

using hash_t = Hash;
using nonce_t = size_t;
using currency_t = ZINA;

using secret_key_t = uint8_t *;
using public_key_t = secp256k1_pubkey;
struct ecc_pair_t {
    secret_key_t secret_key;
    public_key_t public_key;
};
using signature_t = secp256k1_ecdsa_signature;
