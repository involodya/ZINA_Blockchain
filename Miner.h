#pragma once
// #include "definitions.h"
#include "Block.cpp"
#include "BlockChain.cpp"
// #include "Transaction.h"
#include <set>

class Miner {
public:
    Block mine(const Block&);
    bool verifyTransaction(const Transaction&);
    bool verifyBlock(const Block&);
    Block getBlock(); // Where do we get it from? #TODO
    Transaction getTransaction(); // Where do we get it from? #TODO
    void sendBlock();
    void createBlock();
    void addBlock();
private:
    Block _currentBlock;
    BlockChain _currentBlockChain;
    hash_t _get_hash_of_last();
    std::set<Transaction> _unproceedTransactions;
    
    friend class Block;
};