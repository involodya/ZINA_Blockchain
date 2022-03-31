#include "VerifiedChain.h"

void VerifiedChain::dbg() const {
    std::cerr << "VerifiedChain" << std::endl;
    std::cerr << "_chain_of_blocks:" << std::endl;
    if (size() == 0) {
        std::cerr << "Is empty" << std::endl;
        return;
    }
    for (auto it: _chain_of_blocks) {
        it.dbg();
    }
    std::cerr << std::endl;
}

// VerifiedChain::VerifiedChain() {
//     push_block(Block());
// }

const Block VerifiedChain::_last_block() {
    if (size() == 0) {
        throw std::logic_error("VerifiedChain is empty, you can not get it's last block!");
        return Block();
    }
    return *(--_chain_of_blocks.end());

}

bool VerifiedChain::_adding_block_has_correct_parent(const Block& block_to_check) {
    if (size() == 0) return true;
    return block_to_check._previousBlockHash == _last_block()._currentBlockHash;
}

void VerifiedChain::push_block(const Block& block_to_push) {
    if (_adding_block_has_correct_parent(block_to_push)) {
        _chain_of_blocks.push_back(block_to_push);
    } else {
        block_to_push.dbg();
        throw std::logic_error("Incorrect parent hash!");
    }
}
