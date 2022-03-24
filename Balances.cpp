#include "Balances.h"

Balances::Balances(const VerifiedChain &verifiedChain) {
    for (auto block_iterator = verifiedChain._chain_of_blocks.begin();
         block_iterator != verifiedChain._chain_of_blocks.end(); ++block_iterator) {
        for (auto transaction_iterator = block_iterator->_listOfTransactions.begin();
             transaction_iterator != block_iterator->_listOfTransactions.end(); ++transaction_iterator) {

            _balances_table[transaction_iterator->_hashOfSender] -= transaction_iterator->_value;

            auto it = _balances_table.find(transaction_iterator->_hashOfRecipient);
            if (it != _balances_table.end()) {
                it->second += transaction_iterator->_value;
            } else {
                _balances_table[transaction_iterator->_hashOfRecipient] = transaction_iterator->_value;
            }

        }
    }
}

currency_t Balances::operator[](hash_t hash) const {
    auto it = _balances_table.find(hash);
    if (it != _balances_table.end()) {
        return it->second;
    } else {
        return ZINA(0);
    }
}

currency_t &Balances::operator[](hash_t hash) {
    auto it = _balances_table.find(hash);
    if (it != _balances_table.end()) {
        return it->second;
    } else {
        _balances_table[hash] = ZINA(0);
        return _balances_table[hash];
    }
}

void Balances::dbg() const {
    std::cerr << "Balances" << std::endl;
    std::cerr << "balances_table :" << std::endl;
    for (auto it = _balances_table.begin(); it != _balances_table.end(); ++it) {
        std::cerr << "\thash: " << it->first << "\tvalue: " << it->second << std::endl;
    }
}
