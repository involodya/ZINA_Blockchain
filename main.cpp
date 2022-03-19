// #include "definitions.h"
//#include "Miner.h"
#include "Transaction.h"
#include "Block.cpp"
#include "hash_functions.cpp"


int main() {
    Transaction t1(sha256("1"), sha256("2"), 100);
    Transaction t2(sha256("2"), sha256("1"), 100);
    Block b1;
    b1.addTransaction(t1);
    b1.addTransaction(t2);

    std::cerr << calculateHash(b1) << std::endl;

}
