#pragma once

#include "constants.h"

class Coinbase {
public:
    hash_t _hashOfRecipient;
    currency_t _value;
    std::string _message;

    Coinbase(const hash_t &hashOfRecipient,
                currency_t value, const std::string& message);
    Coinbase();
    void dbg();
};

Coinbase::Coinbase(const hash_t &hashOfRecipient,
                         currency_t value, const std::string& message = "") : _hashOfRecipient(hashOfRecipient),
                                                                       _value(value),
                                                                       _message(message) {
    // TODO: calculate signature
}

Coinbase::Coinbase() {
    // _value = BASIC_VALUE_OF_COINBASE_TRANSACTION;
}

std::ostream &operator<<(std::ostream &out, const Coinbase &coinbase) {
    out << coinbase._hashOfRecipient << '-' << coinbase._value << '-'
        << coinbase._message << std::endl;
    return out;
}

void Coinbase::dbg() {
    std::cerr << "_hashOfRecipient: " << _hashOfRecipient << std::endl;
    std::cerr << "_value: " << _value << std::endl;
    std::cerr << "_message: " << _message << std::endl;
}
