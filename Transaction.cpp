
#include "Transaction.h"

Transaction::Transaction(const hash_t &hashOfSender, const hash_t &hashOfRecipient,
                         currency_t value, std::string message) : _hashOfSender(hashOfSender),
                                                                       _hashOfRecipient(hashOfRecipient),
                                                                       _value(value),
                                                                       _message(message) {
    // TODO: calculate signature
}

std::ostream &operator<<(std::ostream &out, const Transaction &transaction) {
    out << transaction._hashOfSender << '-' << transaction._hashOfRecipient << '-' << transaction._value << '-'
        << transaction._message << '-' << transaction._signature;
    return out;
}

void Transaction::dbg() {
    std::cerr << "_hashOfSender: " << _hashOfSender << std::endl;
    std::cerr << "_hashOfRecipient: " << _hashOfRecipient << std::endl;
    std::cerr << "_value: " << _value << std::endl;
    std::cerr << "_message: " << _message << std::endl;
    std::cerr << "_signature: " << _signature << std::endl;
}
