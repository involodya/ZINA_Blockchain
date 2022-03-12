#include "definitions.h"
#include "Block.h"
#include "BlockChain.h"
#include "Transaction.h"
#include <set>

class Miner {
public:
    nonce_t mine(const Block&);
    bool verifyTransaction(const Transaction&);
    bool verifyBlock(const Block&);
    Block getBlock(); // Where do we get it from? #TODO
    Transaction getTransaction(); // Where do we get it from? #TODO
    void sendBlock();
    void createBlock();
    void addBlock();
private:
    Block _currentDlock;
    BlockChain _currentBlockChain;

    std::set<Transaction> _unproceedTransactions;
    
};