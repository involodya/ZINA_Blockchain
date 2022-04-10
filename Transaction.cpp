#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const hash_t &hashOfSender, const hash_t &hashOfRecipient,
                         currency_t value, const std::string &message) : _hashOfSender(hashOfSender),
                                                                         _hashOfRecipient(hashOfRecipient),
                                                                         _value(value),
                                                                         _message(message) {
    // TODO: calculate signature
}

uint8_t *Transaction::getValueHash() const {
    std::stringstream ss;
    ss << _hashOfSender << _hashOfRecipient << _value << _message;
    return Hash(ss.str())._hash;
}

std::ostream &operator<<(std::ostream &out, const Transaction &transaction) {
    out << transaction._hashOfSender << '-' << transaction._hashOfRecipient << '-' << transaction._value << '-'
        << transaction._message << '-';
    for (size_t i = 0; i < SERIALIZED_SIGNATURE_SIZE; ++i) {
        out << transaction.serialized_signature[i];
    }
    return out;
}

void Transaction::dbg() {
    std::cerr << "Transaction " << std::endl;
    std::cerr << "\t_hashOfSender: " << _hashOfSender << std::endl;
    std::cerr << "\t_hashOfRecipient: " << _hashOfRecipient << std::endl;
    std::cerr << "\t_value: " << _value << std::endl;
    std::cerr << "\t_message: " << _message << std::endl;
    std::cerr << "\t_signature: 0x";
    std::cerr.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < SERIALIZED_SIGNATURE_SIZE; ++i) {
        std::cerr << static_cast<int>(serialized_signature[i]);
    }
    std::cerr.unsetf(std::ios::hex);
    std::cerr << std::endl;
}
