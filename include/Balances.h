#pragma once

#include <map>
#include <unordered_map>
#include "VerifiedChain.h"

struct Balances {
    std::map<CPKey, currency_t> _balances_table;

    explicit Balances(const VerifiedChain &verifiedChain);

    currency_t operator[](CPKey hash) const;
    currency_t &operator[](CPKey hash);

    void dbg() const;

};

std::ostream &operator<<(std::ostream &out, const Balances &balances);
