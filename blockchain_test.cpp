#include "BlockChain.h"
#include <cassert>

void verified_chain_test() {
    VerifiedChain v;
    // v.dbg();
    Block first_block;
    // first_block._previousBlockHash = v._last_block()._currentBlockHash;
    first_block._currentBlockHash = "1";
    v.push_block(first_block);
    Block b [10];
    for (size_t i = 0; i < 10; ++i) {
        b[i].coinbase_transaction = Coinbase("his_hash", ZINA(1, 337), "Send this to Pavel");
        b[i]._currentBlockHash = std::string(static_cast<int>(i) + 2, '1');
        b[i]._previousBlockHash = std::string(static_cast<int>(i) + 1, '1');
        Transaction t("his_hash", "his_hash", ZINA(1, 337), "Send this to Pavel");
        for (size_t j = 0; j < 10; ++j) {
            b[i].addTransaction(Transaction("his_hash", "his_hash", ZINA(i, j), "Send this to Pavel"));
        }
        assert(b[i]._listOfTransactions.size() == 10);
        // b[i].dbg();
        v.push_block(b[i]);
    }
    assert(v.size() == 11);
    // v.dbg();
}

void branching_chain_test() {
    BranchingChain bc;
    Block first_block;
    first_block._currentBlockHash = "SHAHAHAHAHAH";
    bc = BranchingChain(first_block);
    // first_block._previousBlockHash = v._last_block()._currentBlockHash;
    // bc.dbg();
    // std::cerr << "----------------------------------\n";

    Block second_block;
    second_block._previousBlockHash = "SHAHAHAHAHAH";
    second_block._currentBlockHash = "abobus";
    bc.add_block(second_block);
    // bc.add_block(second_block);
    // bc.add_block(second_block);
    // bc.add_block(second_block);
    // bc.dbg();
    assert(bc.length_of_max_chain() == 2);
    // v.dbg();
}


int main() {
    // verified_chain_test();
    // std::cerr << "VerifiedChain tests passed\n";
    branching_chain_test();
    std::cerr << "BranchingChain tests passed\n";

    // std::cout << x;
}