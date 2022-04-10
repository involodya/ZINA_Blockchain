#pragma once

#include <iostream>
#include "ZINA.h"

using hash_t = std::string;
using nonce_t = size_t;
using currency_t = ZINA;

using user_key_t = uint8_t*;
using rsa_pair_t = std::pair<hash_t, user_key_t>;
