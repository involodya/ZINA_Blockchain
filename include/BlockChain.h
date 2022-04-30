#pragma once
#include "BranchingChain.h"
#include "VerifiedChain.h"
#include <list>
#include <unordered_map>
#include <iterator>


// #TODO: Singleton
class BlockChain {
public:
    // BlockChain static getInstance() { 
    //     if (_pointerToInstance == nullptr) {  // #TODO: figure out how to check existance of object
    //         BlockChain instance = BlockChain();
    //         *_pointerToInstance = instance;
    //     }
    //     return *_pointerToInstance;
    // }
    void update(); //TODO: Download latest version of blockchain from source
    void add_block(const Block& block_to_add);
    void dbg() const;

    hash_t get_hash_of_last_block() {
        return _unverified_chain.get_hash_of_last_block();
    }
private:
    void _proceed_block_to_chain();
    VerifiedChain _verified_chain;
    BranchingChain _unverified_chain;

    friend std::ostream& operator<<(std::ostream& out, const BlockChain& miner);
};
