#pragma once
#include "Block.h"
#include <list>
#include <unordered_map>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

class VerifiedChain {
public:
    std::list<Block> _chain_of_blocks;

    void push_block(const Block &block_to_push);

    size_t size() const {
        return _chain_of_blocks.size();
    }

    void dbg() const;

private:
// public:
    const Block _last_block();

    bool _adding_block_has_correct_parent(const Block &block_to_add);
};

std::ostream& operator<<(std::ostream& out, const VerifiedChain& miner);
