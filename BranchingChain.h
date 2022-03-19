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
    Block push_to_blockchain(); // TODO:
    BranchingChain();
    BranchingChain(const Block& first_block);

    size_t size() const {
        return _blocks.size();
    }
private:
    std::vector<int> _indexes_of_all_blocks_of_subchain(int index);
    void removeUnnecessaryChains();
    int get_length_of_chain(int index);
    std::queue<int> get_indexes_of_suitable_chains();
    // size_t _length_of_largest_chain;
    std::unordered_map<hash_t, int> _index_of_block;
    std::vector<Node> _blocks;
};