#include "Coinbase.h"
#include <cassert>

void test1() {
    Coinbase t("his_hash", ZINA(1, 337), "Send this to Pavel");
    t.dbg();
    std::cerr << t;
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