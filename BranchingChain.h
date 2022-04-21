#pragma once

#include "Block.h"
#include "Balances.h"
#include <list>
#include <map>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

// #TODO Singleton
class BranchingChain {
    struct Node {
        Block block;
        int index_of_prev;
        std::vector<int> successors;

        void dbg() const {
            std::cerr << "N_E_X_T_N_O_D_E\n";
            std::cerr << "~~~~~~~~~~~~~~~\n";
            // std::cerr << "Node in BranchingChain:" << std::endl;
            block.dbg();
            std::cerr << "index_of_prev = " << index_of_prev << std::endl;
            std::cerr << "successors:    ";
            for (auto s: successors) std::cerr << s << ' ';
            std::cerr << std::endl;
            std::cerr << "~~~~~~~~~~~~~~~";
            std::cerr << std::endl;
        }
    };

public:
    void add_block(const Block &to_add);

    Block get_block_to_push();

    BranchingChain(const Block &first_block = Block());

    size_t size() const {
        return _nodes.size() - 1;
    }

    size_t length_of_max_chain() {
        return _get_length_of_chain(0) - 1;
    }

    void dbg() const;

// private:
    std::vector<int> _indexes_of_all_blocks_of_subchain(int index);

    void _remove_unnecessary_chains();

    size_t _get_length_of_chain(size_t index);

    std::queue<int> _get_indexes_of_suitable_chains();

    std::map<hash_t, int> _index_of_block;
    std::vector<Node> _nodes;
};

