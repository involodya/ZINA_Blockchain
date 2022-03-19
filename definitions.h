#pragma once

#include <iostream>

using hash_t = std::string;
using nonce_t = size_t;
using currency_t = size_t;

using user_key_t = uint8_t*;
using rsa_pair_t = std::pair<hash_t, user_key_t>;
