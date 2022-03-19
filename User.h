#include "definitions.h"
#include "Transaction.h"
#include "hash_functions.h"

class User {
public:
    User();

    explicit User(rsa_pair_t _keys);

    static void sendTransaction(Transaction &transaction);

    static void signTransaction(Transaction &transaction);

private:
    hash_t _user_hash;
    user_key_t _public_key;
    user_key_t _private_key;
};
