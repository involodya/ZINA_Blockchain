#pragma once
#include "definitions.h"

class Transaction {
public:
    Transaction(const hash_t& hashOfSender,
                const hash_t& hashOfRecipient,
                currency_t value,
                std::string message) : _hashOfSender(hashOfSender),
                                    _hashOfRecipient(hashOfRecipient),
                                    _value(value),
                                    _message(message),
                                    _signature("") {}

    hash_t _hashOfSender;
    hash_t _hashOfRecipient;
    currency_t _value;
    std::string _message;
    hash_t _signature;
};
