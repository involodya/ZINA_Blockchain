#include "Miner.h"
#include "constants.h"
#include "hash_functions.cpp"

Block Miner::mine(const Block& block_to_mine) {
    Block mined_block = block_to_mine;
    for (nonce_t current_nonce = 0; current_nonce < MAX_NONCE; ++current_nonce) {
        mined_block.setNonce(current_nonce);
        hash_t current_hash = calculateHash(mined_block);
        if (hashIsCorrect(current_hash)) {
            return mined_block;
        }
    }
    std::cerr << "Couldn't find nonce for this block";
    return block_to_mine;
}

void Miner::create_block() {
    Block new_block;
    for (auto transaction: _unproceedTransactions) {
        new_block._listOfTransactions.push_back(transaction);
    }
    new_block._previousBlockHash = _get_hash_of_last();
    new_block._currentBlockHash = calculateHash(new_block);
}

void Miner::send_block() { // TODO:
    
}

hash_t Miner::_get_hash_of_last() { // TODO:
    
}

void Miner::add_block() { 
    _currentBlockChain.add_block(_currentBlock);
}

bool Miner::verify_coinbase_transaction(const Coinbase&) {
    return true;
}

// #TODO: @andzh1
//      _get_hash_of_last()
//     bool verifyTransaction(const Transaction&);
//     bool verifyBlock(const Block&);
//     Block getBlock(); // Where do we get it from? #TODO
//     Transaction getTransaction(); // Where do we get it from? #TODO
