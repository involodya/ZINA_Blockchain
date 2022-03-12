#include "Transaction.h"
#include "definitions.h"

class MessageTransaction : Transaction {
public:
    MessageTransaction() = default;
    Transaction createTransaction() {
        return MessageTransaction();
    }
    MessageTransaction(std::string message);
private:
};

class MoneyTransaction : Transaction {
public:
    MoneyTransaction() = default;
    Transaction createTransaction() {
        return MoneyTransaction();
    }
    MoneyTransaction(std::string message, currency_t value);
private:

};