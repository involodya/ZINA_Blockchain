#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const CPKey &keyOfSender, const CPKey &keyOfRecipient,
                         currency_t value, const std::string &message) : _keyOfSender(keyOfSender),
                                                                         _keyOfRecipient(keyOfRecipient),
                                                                         _value(value),
                                                                         _message(message) {
}

Hash Transaction::getValueHash() const {
    std::stringstream ss;
    ss << _keyOfSender << _keyOfRecipient << _value << _message;
    return Hash(ss.str());
}

std::ostream &operator<<(std::ostream &out, const Transaction &transaction) {
    out << transaction._keyOfSender << '-' << transaction._keyOfRecipient << '-' << transaction._value << '-'
        << transaction._message << '-';
    for (size_t i = 0; i < SERIALIZED_SIGNATURE_SIZE; ++i) {
        out << transaction.serialized_signature[i];
    }
    return out;
}

void Transaction::dbg() const {
    using std::cerr, std::endl;
    cerr << "Transaction" << std::endl;
    cerr << "\tkeyOfSender:    " << _keyOfSender << endl;
    cerr << "\tkeyOfRecipient: " << _keyOfRecipient << endl;
    cerr << "\tvalue:          " << _value << endl;
    cerr << "\tmessage:        " << _message << endl;
    cerr << "\tsignature:      0x";
    cerr.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < SERIALIZED_SIGNATURE_SIZE; ++i) {
        std::cerr << static_cast<int>(serialized_signature[i]);
    }
    cerr.unsetf(std::ios::hex);
    cerr << endl;
}
