#pragma once

#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <iomanip>
#include <string>

#include <sys/random.h>
#include <secp256k1.h>

#include "definitions.h"
#include "constants.h"
#include "Block.h"
#include "Transaction.h"

bool isHashCorrect(hash_t current_hash);

