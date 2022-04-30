#include "Block.h"
#include <cassert>

void test1() {
    Block b;
    b.coinbase_transaction = Coinbase("his_hash", ZINA(1, 337), "Send this to Pavel");
    Transaction t("his_hash", "his_hash", ZINA(1, 337), "Send this to Pavel");
    for (size_t i = 0; i < 10; ++i) {
        b.addTransaction(Transaction("his_hash", "his_hash", ZINA(i, i), "Send this to Pavel"));
    }
    assert(b._listOfTransactions.size() == 10);
    b.dbg();
    /*
    Transaction(const hash_t &hashOfSender, const hash_t &hashOfRecipient,
                currency_t value, std::string message="");
    */
}


int main() {
    test1();
    std::cerr << "Test 1 passed\n";
    // std::cout << x;
}