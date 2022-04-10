#include "BlockChain.h"

void BlockChain::dbg() const {
    std::cerr << "BlockChain" << std::endl;
    std::cerr << "Contains of:" << std::endl;
    _verified_chain.dbg();
    std::cerr << std::endl;
    _unverified_chain.dbg();
    std::cerr << std::endl;
}

void BlockChain::_proceed_block_to_chain() {
    _verified_chain.push_block(_unverified_chain.get_block_to_push());
}

void BlockChain::add_block(const Block& block_to_add) {
    _unverified_chain.add_block(block_to_add);
    if (_unverified_chain.length_of_max_chain() > MAX_LENGTH_OF_BRANCHING_CHAIN) {
        _proceed_block_to_chain();
    }
}