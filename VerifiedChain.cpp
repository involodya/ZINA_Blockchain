#include "VerifiedChain.h"

void VerifiedChain::dbg() const {
    std::cerr << "VerifiedChain" << std::endl;
    std::cerr << "_chain_of_blocks:" << std::endl;
    for (auto it: _chain_of_blocks) {
        it.dbg();
    }
    std::cerr << std::endl;
}

const Block VerifiedChain::_last_block() {
    return *(--_chain_of_blocks.end());
}

bool VerifiedChain::_adding_block_has_correct_parent(const Block& block_to_check) {
    if (size() == 0) return true;
    return block_to_check._previousBlockHash == _last_block()._currentBlockHash;
}

void VerifiedChain::push_block(const Block& block_to_push) {
    _chain_of_blocks.insert(_chain_of_blocks.end(), block_to_push);
}
