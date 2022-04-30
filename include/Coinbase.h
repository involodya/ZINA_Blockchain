#pragma once

#include "constants.cpp"

struct Coinbase {
    hash_t _hashOfRecipient;
    currency_t _value = BASIC_VALUE_OF_COINBASE_TRANSACTION;
    std::string _message;

    Coinbase(const hash_t &hashOfRecipient,
                currency_t value, const std::string& message);
    Coinbase() = default;
    void dbg();
};

std::ostream &operator<<(std::ostream &out, const Coinbase &coinbase);