#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>

#include "definitions.h"
#include "constants.h"
#include "Block.h"

rsa_pair_t generateKeys();

hash_t sha256(const std::string &hash_object);

hash_t calculateHash(const Block &block);

bool hashIsCorrect(hash_t current_hash);
