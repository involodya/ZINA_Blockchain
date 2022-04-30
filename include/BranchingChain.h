#pragma once

#include "Block.h"
// #include "Balances.h" TODO: support balances in every branch
#include <list>
#include <map>
#include <iterator>
#include <queue>
#include <set>
#include <vector>
#include <exception>

// #TODO Singleton
struct BranchingChain {
    struct Node {
        Block block;
        int index_of_previous;
        std::vector<int> successors;

        void dbg() const;
    };

// public:
    void add_block(const Block &to_add);

    Block get_block_to_push();

    BranchingChain(const Block &first_block = Block());

    size_t size() const;

    size_t length_of_max_chain();

    void dbg() const;

    hash_t get_hash_of_last_block();

// private:
    std::vector<int> _indexes_of_all_blocks_of_subchain(int index);

    void _remove_unnecessary_chains();

    size_t _get_length_of_chain(size_t index);

    std::queue<int> _get_indexes_of_suitable_chains();

    std::map<hash_t, int> _index_of_block;
    std::vector<Node> _nodes;
};

std::ostream& operator<<(std::ostream& out, const BranchingChain& bch);
