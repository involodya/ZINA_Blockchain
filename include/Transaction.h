#pragma once

#include "Hash.h"
#include "CPKey.h"

class Transaction {
public:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    CPKey _keyOfSender;
    CPKey _keyOfRecipient;
    currency_t _value;
    std::string _message;
    signature_t _signature;
    uint8_t serialized_signature[SERIALIZED_SIGNATURE_SIZE]{};

    Transaction(const CPKey &keyOfSender, const CPKey &keyOfRecipient,
                currency_t value, const std::string &message = "");

    Hash getValueHash() const;

    void dbg() const;
};

std::ostream &operator<<(std::ostream &out, const Transaction &transaction);
