#include "BranchingChain.h"

void BranchingChain::addBlock(Block block_to_add) {
    Node node_to_add;
    node_to_add.block = block_to_add;
    node_to_add.index_of_next = -1;
    node_to_add.index_of_prev = _index_of_end_of_largest_chain;
    blocks.push_back(node_to_add);
    blocks[_index_of_end_of_largest_chain].index_of_next = blocks.size() - 1;
}


// TODO @andzh1

//     Block push_to_blockchain(); // TODO

//     void removeUnnecessaryChains();
//     // size_t _length_of_largest_chain;
//     int _index_of_end_of_largest_chain;
//     std::vector<Node> blocks;

// };