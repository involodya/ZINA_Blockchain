#include "VerifiedChain.h"


void VerifiedChain::dbg() const {
    std::cerr << "VerifiedChain" << std::endl;
    std::cerr << "_chain_of_blocks:" << std::endl;
    if (size() == 0) {
        std::cerr << "Is empty" << std::endl;
        return;
    }
    for (auto it: _chain_of_blocks) {
        it.dbg();
    }
    std::cerr << std::endl;
}

std::ostream& operator<<(std::ostream& out, const VerifiedChain& vch) {
    for (auto it: vch._chain_of_blocks) {
        out << it;
    }
    return out;
}


/* 
Constructs VerifiedChain from file of concrete format:
[cpkey of sender] [cpkey of recipient] [value] [message]
*/
// std::istream& operator>>(std::istream& in, VerifiedChain& vch) {
//     size_t number_of_transactions;
//     in >> number_of_transactions;
//     for (size_t i = 0; i < number_of_transactions; ++i) {
//         CPKey sender, recipient;
//         in >> sender >> recipient;
//         std::string value_as_string, message;
//         in >> value_as_string >> message;
//         Transaction new_transaction(sender, recipient, ZINA(value_as_string), message);

//     }
// }


const Block VerifiedChain::_last_block() {
    if (size() == 0) {
        throw std::logic_error("VerifiedChain is empty, you can not get it's last block!");
        return Block();
    }
    return *(--_chain_of_blocks.end());

}

bool VerifiedChain::_adding_block_has_correct_parent(const Block& block_to_check) {
    if (size() == 0) return true;
    return block_to_check._previousBlockHash == _last_block()._currentBlockHash;
}

void VerifiedChain::push_block(const Block& block_to_push) {
    if (_adding_block_has_correct_parent(block_to_push)) {
        _chain_of_blocks.push_back(block_to_push);
    } else {
        block_to_push.dbg();
        throw std::logic_error("Incorrect parent hash!");
    }
}
