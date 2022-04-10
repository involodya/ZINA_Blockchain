#pragma once

// #include <unordered_map>
#include "VerifiedChain.h"

struct Balances {
    std::unordered_map<hash_t, currency_t> _balances_table;

    explicit Balances(const VerifiedChain &verifiedChain);

    currency_t operator[](hash_t hash) const;
    currency_t &operator[](hash_t hash);

    void dbg() const;
};
