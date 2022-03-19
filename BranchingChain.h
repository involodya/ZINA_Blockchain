#pragma once
#include "Block.cpp"
#include <list>
#include <unordered_map>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

// #TODO Singleton
class BranchingChain {
    struct Node
    {
        Block block;
        int index_of_prev;
        std::vector<int> successors; // = -1, if this Node is list of our tree (it has no successor)
    };
public:
    void addBlock(const Block& to_add);
    Block get_block_to_push(); // TODO:
    BranchingChain();
    BranchingChain(const Block& first_block);

    size_t size() const {
        return _blocks.size();
    }

    size_t length_of_max_chain() {
        return _get_length_of_chain(0);
    }
private:
    std::vector<int> _indexes_of_all_blocks_of_subchain(int index);
    void _remove_unnecessary_chains();
    size_t _get_length_of_chain(size_t index);
    std::queue<int> _get_indexes_of_suitable_chains();
    std::unordered_map<hash_t, int> _index_of_block;
    std::vector<Node> _blocks;
};