#include "Balances.h"

Balances::Balances(const VerifiedChain &verifiedChain) {
    for (auto block_iterator = verifiedChain._chain_of_blocks.begin();
         block_iterator != verifiedChain._chain_of_blocks.end(); ++block_iterator) {
        for (auto transaction_iterator = block_iterator->_listOfTransactions.begin();
             transaction_iterator != block_iterator->_listOfTransactions.end(); ++transaction_iterator) {

            _balances_table[transaction_iterator->_keyOfSender] -= transaction_iterator->_value;

            auto it = _balances_table.find(transaction_iterator->_keyOfRecipient);
            if (it != _balances_table.end()) {
                it->second += transaction_iterator->_value;
            } else {
                _balances_table[transaction_iterator->_keyOfRecipient] = transaction_iterator->_value;
            }

        }
    }
}

currency_t Balances::operator[](CPKey hash) const {
    auto it = _balances_table.find(hash);
    if (it != _balances_table.end()) {
        return it->second;
    } else {
        return ZINA(0);
    }
}

currency_t &Balances::operator[](CPKey hash) {
    auto it = _balances_table.find(hash);
    if (it != _balances_table.end()) {
        return it->second;
    } else {
        _balances_table[hash] = ZINA(0);
        return _balances_table[hash];
    }
}

std::ostream &operator<<(std::ostream &out, const Balances &balances) {
    for (auto it = balances._balances_table.begin(); it != balances._balances_table.end(); ++it) {
        out << it->first << " " << it->second << std::endl;
    }
    return out;
}

void Balances::dbg() const {
    std::cerr << "Balances" << std::endl;
    std::cerr << "balances_table :" << std::endl;
    for (auto it = _balances_table.begin(); it != _balances_table.end(); ++it) {
        std::cerr << "\thash: " << it->first << "\tvalue: " << it->second << std::endl;
    }
}
