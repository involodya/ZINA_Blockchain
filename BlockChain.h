#include "Block.h"
#include <list>

class BlockChain {
public:
    BlockChain static getInstance() { 
        if (_pointerToInstance == nullptr) {  // #TODO figure out how to check existance of object
            BlockChain instance = BlockChain();
            *_pointerToInstance = instance;
        }
        return *_pointerToInstance;
    }
    void update();
    
private:
    static BlockChain* _pointerToInstance;
    BlockChain() {
    }
    std::list<Block> currentBlockChain;
    std::list<Block> currentBlockChain;
};