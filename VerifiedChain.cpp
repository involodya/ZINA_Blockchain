#include "VerifiedChain.h"

// #TODO Singleton
class VerifiedChain {

public:
    void push_block(const Block& to_add);

private:
    bool _adding_block_has_correct_parent(const Block& to_add);
    bool _adding_block_has_correct_parent(const Block& to_add);
    std::list<Block> _chain_of_blocks;
    // std::unordered_map<hash_t, int> _index_of_block;
    // std::vector<Node> _blocks;
};