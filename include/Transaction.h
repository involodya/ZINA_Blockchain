#pragma once

#include "constants.h"
#include "Hash.h"

class Transaction {
public:
    hash_t _hashOfSender;
    hash_t _hashOfRecipient;
    currency_t _value;
    std::string _message;
    signature_t _signature;
    uint8_t serialized_signature[SERIALIZED_SIGNATURE_SIZE]{};

    Transaction(const hash_t &hashOfSender, const hash_t &hashOfRecipient,
                currency_t value, const std::string &message = "");

    uint8_t *getValueHash() const;

    void dbg();
};

std::ostream &operator<<(std::ostream &out, const Transaction &transaction);
