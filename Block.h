#include <list>
#include "Transaction.h"
#include "definitions.h"

class Block {
public:

private:
    nonce_t _nonce = 0;
    std::list<Transaction> _listOfTransactions;
    hash_t _previousBlockHash;
    hash_t _currentBlockHash;
};