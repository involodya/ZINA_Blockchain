#pragma once
#include "Block.cpp"
#include <list>
#include <unordered_map>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

class VerifiedChain {

public:
    void push_block(const Block& to_add);

private:
    bool _adding_block_has_correct_parent();
    std::list<Block> _chain_of_blocks;
    // std::unordered_map<hash_t, int> _index_of_block;
    // std::vector<Node> _blocks;
};