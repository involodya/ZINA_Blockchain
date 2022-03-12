#pragma once
#include "Block.h"
#include <list>
#include <unordered_map>
#include <iterator>
#include <vector>

struct Node
{
    Block block;
    int index_of_prev;
    int index_of_next; // = -1, if this Node is list of our tree (it has no successor)
};


// #TODO Singleton
class BranchingChain {
public:
    void addBlock(Block to_add);
    Block push_to_blockchain(); // TODO

private:
    void removeUnnecessaryChains();
    // size_t _length_of_largest_chain;
    int _index_of_end_of_largest_chain;
    std::vector<Node> blocks;

};