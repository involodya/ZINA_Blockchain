#pragma once
#include "definitions.h"
#include "ZINA.h"

const nonce_t MAX_NONCE = 1e5;
const size_t REQUIRED_LEN_OF_ZEROS_PREFIX_IN_HASH = 4;
const size_t MAX_LENGTH_OF_BRANCHING_CHAIN = 6;
const hash_t DEFAULT_HASH = std::string(32, '0');
const ZINA BASIC_VALUE_OF_COINBASE_TRANSACTION (static_cast<size_t>(1));