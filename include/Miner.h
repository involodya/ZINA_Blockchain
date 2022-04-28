#pragma once
#include "Block.cpp"
#include "BlockChain.cpp"
#include "Coinbase.h"
#include "constants.h"
#include <set>

class Miner {
public:
    ~Miner();

    Block mine(const Block &block);

    bool verify_transaction(Transaction &transaction);

    bool verify_coinbase_transaction(const Coinbase &coinbase);

    bool verify_block(const Block &block);

    Block get_block(); // Where do we get it from? #TODO:
    Transaction get_transaction(); // Where do we get it from? #TODO:
    void send_block();

    void create_block();

    void add_block();

private:
    secp256k1_context *ctx_ = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);

    Block _currentBlock;
    BlockChain _currentBlockChain;

    hash_t _get_hash_of_last();

    std::set<Transaction> _unproceedTransactions;

    friend class Block;
};

bool isHashCorrect(const hash_t &current_hash);