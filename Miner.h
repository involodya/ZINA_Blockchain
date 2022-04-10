#pragma once
// #include "definitions.h"
#include "Block.cpp"
#include "BlockChain.cpp"
#include "Coinbase.h"
// #include "Transaction.h"
#include <set>

class Miner {
public:
    Block mine(const Block&);
    bool verify_transaction(const Transaction&);
    bool verify_coinbase_transaction(const Coinbase&);
    bool verify_block(const Block&);
    Block get_block(); // Where do we get it from? #TODO
    Transaction get_transaction(); // Where do we get it from? #TODO
    void send_block();
    void create_block();
    void add_block();
private:
    Block _currentBlock;
    BlockChain _currentBlockChain;
    hash_t _get_hash_of_last();
    std::set<Transaction> _unproceedTransactions;
    
    friend class Block;
};