
#include "ZINA.h"
#include "Hash.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <iomanip>
#include <string>

#include <sys/random.h>
#include <secp256k1.h>

using hash_t = Hash;
using nonce_t = size_t;
using currency_t = ZINA;

using secret_key_t = uint8_t *;
using public_key_t = secp256k1_pubkey;
using compressed_public_key_t = uint8_t *;

using signature_t = secp256k1_ecdsa_signature;

