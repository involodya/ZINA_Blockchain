#include "Miner.h"
#include "constants.h"
#include "hash_functions.h"

Block Miner::mine(const Block &block_to_mine) {
    Block mined_block = block_to_mine;
    for (nonce_t current_nonce = 0; current_nonce < MAX_NONCE; ++current_nonce) {
        mined_block.setNonce(current_nonce);
        hash_t current_hash = mined_block.calculateHash();
        if (isHashCorrect(current_hash)) {
            return mined_block;
        }
    }
    std::cerr << "Couldn't find nonce for this block";
    return block_to_mine;
}

void Miner::create_block() {
    Block new_block;
    for (auto transaction: _unproceedTransactions) {
        new_block._listOfTransactions.push_back(transaction);
    }
    new_block._previousBlockHash = _get_hash_of_last();
    new_block._currentBlockHash = new_block.calculateHash();
}

void Miner::send_block() { // TODO:

}

hash_t Miner::_get_hash_of_last() { // TODO:
    return Hash();
}

void Miner::add_block() {
    _currentBlockChain.add_block(_currentBlock);
}

bool Miner::verify_coinbase_transaction(const Coinbase &) {
    return true;
}

bool Miner::verify_transaction(Transaction &transaction) {
    CPKey sender_ckey = transaction._keyOfSender;
    if (!secp256k1_ecdsa_signature_parse_compact(ctx_, &transaction._signature, transaction.serialized_signature)) {
        throw std::exception(); // Failed parsing the signature
    }

    secp256k1_pubkey pubkey;
    if (!secp256k1_ec_pubkey_parse(ctx_, &pubkey, sender_ckey.getDataPointer(), COMPRESSED_PUBLIC_KEY_SIZE)) {
        throw std::exception(); // Failed parsing the public key
    }

    // Verify a signature. This will return 1 if it's valid and 0 if it's not.
    int is_signature_valid = secp256k1_ecdsa_verify(ctx_, &transaction._signature,
                                                    transaction.getValueHash()._hash, &pubkey);
    return is_signature_valid;

}

bool Miner::verify_block(const Block &block) {
    // TODO
    return true;
}

Miner::~Miner() {
    secp256k1_context_destroy(ctx_);
}

// #TODO: @andzh1
//      _get_hash_of_last()
//     bool verifyTransaction(const Transaction&);
//     bool verifyBlock(const Block&);
//     Block getBlock(); // Where do we get it from? #TODO
//     Transaction getTransaction(); // Where do we get it from? #TODO
