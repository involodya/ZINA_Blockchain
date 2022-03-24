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
        std::vector<int> successors;
        void dbg() const {
            std::cerr << "Node in BranchingChain:" << std::endl;
            block.dbg();
            std::cerr << "index_of_prev = " << index_of_prev << std::endl;
            std::cerr << "successors:";
            for (auto s: successors) std::cerr << s << ' ';
            std::cerr << std::endl;
        }
    };
public:
    void add_block(const Block& to_add);
    Block get_block_to_push(); 
    BranchingChain();
    BranchingChain(const Block& first_block);

    size_t size() const {
        return _blocks.size();
    }

    size_t length_of_max_chain() {
        return _get_length_of_chain(0);
    }

    void dbg() const;
private:
    std::vector<int> _indexes_of_all_blocks_of_subchain(int index);
    void _remove_unnecessary_chains();
    size_t _get_length_of_chain(size_t index);
    std::queue<int> _get_indexes_of_suitable_chains();
    std::unordered_map<hash_t, int> _index_of_block;
    std::vector<Node> _blocks;
};

