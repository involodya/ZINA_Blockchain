#pragma once
#include "Block.h"
#include "BranchingChain.cpp"
#include "VerifiedChain.cpp"
#include <list>
#include <unordered_map>
#include <iterator>


// #TODO Singleton
class BlockChain {
public:
    // BlockChain static getInstance() { 
    //     if (_pointerToInstance == nullptr) {  // #TODO figure out how to check existance of object
    //         BlockChain instance = BlockChain();
    //         *_pointerToInstance = instance;
    //     }
    //     return *_pointerToInstance;
    // }
    void update(); // Download latest version of blockchain from source
    void add_block(const Block& block_to_add);
    void dbg() const;
private:
    void _proceed_block_to_chain();
    VerifiedChain _verified_chain;
    BranchingChain _unverified_chain;
};