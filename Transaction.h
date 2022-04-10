#pragma once

#include "constants.h"

class Transaction {
public:
    hash_t _hashOfSender;
    hash_t _hashOfRecipient;
    currency_t _value;
    std::string _message;
    hash_t _signature;

    Transaction(const hash_t &hashOfSender, const hash_t &hashOfRecipient,
                currency_t value, std::string message="");

    void dbg();
};

std::ostream &operator<<(std::ostream &out, const Transaction &transaction);
