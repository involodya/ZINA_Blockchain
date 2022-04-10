#pragma once

#include "constants.h"

struct Hash {
    uint8_t *_hash;
    size_t _size;

    Hash();

    Hash(const std::string &str);
};
