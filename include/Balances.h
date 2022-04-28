#pragma once

#include <map>
#include "VerifiedChain.h"

//TODO HASH change to KEY

struct Balances {
    std::map<hash_t, currency_t> _balances_table;

    explicit Balances(const VerifiedChain &verifiedChain);

    currency_t operator[](hash_t hash) const;
    currency_t &operator[](hash_t hash);

    void dbg() const;
};
