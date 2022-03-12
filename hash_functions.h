#pragma once
#include "definitions.h"
#include "Constants.h"
#include "Block.h"

rsa_pair_t generateKeys();

hash_t calculateHash(const Block&);

bool hashIsCorrect(hash_t current_hash);