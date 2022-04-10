#pragma once

#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <iomanip>
#include <string>

#include <sys/random.h>
#include <openssl/sha.h>
#include <secp256k1.h>

#include "definitions.h"
#include "constants.h"
#include "Block.h"

rsa_pair_t generateKeys();

hash_t sha256(const std::string &hash_object);

hash_t calculateHash(const Block &block);

bool hashIsCorrect(hash_t current_hash);

void f();
