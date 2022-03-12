#include "BlockChain.h"

hash_t BlockChain::getHashOfLast() {
    return _chain.back()._currentBlockHash;
}

void BlockChain::addBlock(Block to_add) { // #TODO How to push exactly in required branch of blockchain?
    std::bidirectional_iterator_tag place_to_insert = _positionOfBlock[to_add._previousBlockHash];

    _chain.push_back(to_add);

}




// // #TODO Singleton
// class BlockChain {
// public:
//     // BlockChain static getInstance() { 
//     //     if (_pointerToInstance == nullptr) {  // #TODO figure out how to check existance of object
//     //         BlockChain instance = BlockChain();
//     //         *_pointerToInstance = instance;
//     //     }
//     //     return *_pointerToInstance;
//     // }
//     void update();
//     hash_t getHashOfLast();
// private:
//     // static BlockChain* _pointerToInstance;
//     // BlockChain() {
//     // }
//     std::list<Block> _chain;
//     // std::list<Block> currentBlockChain;
// };