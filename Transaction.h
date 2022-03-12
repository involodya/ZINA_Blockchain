#include "definitions.h"

class Transaction {
public:
    Transaction createTransaction();
private:
    hash_t _hashOfSender;
    hash_t _hashOfRecipient;
    currency_t _value;
    hash_t _signature;
};