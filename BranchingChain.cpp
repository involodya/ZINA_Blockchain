#include "BranchingChain.h"
#include <exception>

void BranchingChain::dbg() const {
    std::cerr << "BranchingChain" << std::endl;
    std::cerr << "_blocks:" << std::endl;
    for (auto it: _blocks) {
        it.dbg();
    }
    std::cerr << "_index_of_block:" << std::endl;
    for (auto i: _index_of_block) {
        std::cerr << i.first << " - " << i.second << std::endl;
    }
}

BranchingChain::BranchingChain() {
    Node default_node;
    default_node.block = Block();
    default_node.index_of_prev = -1;
    _blocks.push_back(default_node);
    _index_of_block[default_node.block._currentBlockHash] = 0;
}

BranchingChain::BranchingChain(const Block& first_block) {
    Node default_node;
    default_node.block = first_block;
    default_node.index_of_prev = -1;
    _blocks.push_back(default_node);
    _index_of_block[default_node.block._currentBlockHash] = 0;
}

void BranchingChain::add_block(const Block& block_to_add) {
    Node node_to_add;
    node_to_add.block = block_to_add;
    if (_blocks.size() != 0) {
        node_to_add.index_of_prev = _index_of_block[block_to_add._previousBlockHash];
    }
    _index_of_block[block_to_add._currentBlockHash] = _blocks.size();
    _blocks.push_back(node_to_add);
    int index_of_prev = _index_of_block[block_to_add._previousBlockHash];
    _blocks[index_of_prev].successors.push_back(_blocks.size());
    _blocks.push_back(node_to_add);
}

size_t BranchingChain::_get_length_of_chain(size_t index) {
    if (_blocks[index].successors.size() == 0) return 0;
    size_t answer = 0;
    for (auto next: _blocks[index].successors) {
        answer = std::max(answer, _get_length_of_chain(next));
    }
    return answer + 1;
}

std::queue<int> BranchingChain::_get_indexes_of_suitable_chains() {
    int max_len = _get_length_of_chain(0) - 1;
    std::queue<int> suitable_chains;
    for (auto index : _blocks[0].successors) {
        int current_len = _get_length_of_chain(index);
        if (current_len == max_len) {
            suitable_chains.push(index);
        }
    }
    return suitable_chains;
}

std::vector<int> BranchingChain::_indexes_of_all_blocks_of_subchain(int index) {
    std::vector<int> indexes_of_current_subchain;
    indexes_of_current_subchain.push_back(index);
    if (_blocks[index].successors.size() == 0) {
        return indexes_of_current_subchain;
    }
    for (auto next : _blocks[index].successors) {
        std::vector<int> current_indexes = _indexes_of_all_blocks_of_subchain(next);
        for (auto element : current_indexes) {
            indexes_of_current_subchain.push_back(element);
        }
    }
    return indexes_of_current_subchain;
}

void BranchingChain::_remove_unnecessary_chains() {
    if (_get_length_of_chain(0) < MAX_LENGTH_OF_BRANCHING_CHAIN) return;
    // If our BranchingChain is small, we don't need to remove unnecessary chains
    BranchingChain new_chain (_blocks[0].block);
    std::queue<int> blocks_to_transfer = _get_indexes_of_suitable_chains();
    // blocks_to_transfer.push(index_of_max_chain);
    while (!blocks_to_transfer.empty()) {
        int current_index = blocks_to_transfer.front();
        blocks_to_transfer.pop();
        new_chain.add_block(_blocks[current_index].block);
        for (auto index : _blocks[current_index].successors) {
            blocks_to_transfer.push(index);
        }
    }
    *this = new_chain;
}

Block BranchingChain::get_block_to_push() {
    _remove_unnecessary_chains();
    /*Here we suppose that our BranchingChain has only one parent, because probability of fact 
    that we have at least 2 chaing of length MAX_LENGTH_OF_BRANCHING_CHAIN is extremelly small
    (we actually set MAX_LENGTH_OF_BRANCHING_CHAIN such that this probability is very small)
    */
    int index_of_new_begin = _get_indexes_of_suitable_chains().front();
    Block block_to_push = _blocks[0].block;
    BranchingChain new_chain (_blocks[index_of_new_begin].block);
    std::vector<int> blocks_to_transfer = _indexes_of_all_blocks_of_subchain(index_of_new_begin);
    for (int i = 1; i < blocks_to_transfer.size(); ++i) {
        new_chain.add_block(_blocks[i].block);
    }
    *this = new_chain;
    return block_to_push;
}

