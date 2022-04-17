#include "Coinbase.h"


Coinbase::Coinbase(const hash_t &hashOfRecipient,
                         currency_t value, const std::string& message = "") : _hashOfRecipient(hashOfRecipient),
                                                                       _value(value),
                                                                       _message(message) {
    // TODO: calculate signature
}

std::ostream &operator<<(std::ostream &out, const Coinbase &coinbase) {
    out << coinbase._hashOfRecipient << '-' << coinbase._value << '-'
        << coinbase._message << std::endl;
    return out;
}

void Coinbase::dbg() {
    std::cerr << "_keyOfRecipient: " << _hashOfRecipient << std::endl;
    std::cerr << "_value: " << _value << std::endl;
    std::cerr << "_message: " << _message << std::endl;
}
