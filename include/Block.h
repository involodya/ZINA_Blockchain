#pragma once

#include <list>
#include "Transaction.h"
#include "Coinbase.h"

struct Block {
    Block();

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    void setNonce(nonce_t new_nonce);
    void addTransaction(const Transaction& transaction);

    hash_t calculateHash() const;

    void dbg() const;

    nonce_t _nonce;

    hash_t _previousBlockHash;
    hash_t _currentBlockHash;

    std::list<Transaction> _listOfTransactions;
    Coinbase coinbase_transaction;
};

std::ostream& operator<<(std::ostream& out, const Block& block);
