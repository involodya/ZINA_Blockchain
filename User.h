#include "definitions.h"
#include "Transaction.h"
#include "hash_functions.h"

class User {
public:
    User();

    explicit User(const secret_key_t &secret_key);

    ~User();

    void dbg() const;

    static void sendTransaction(Transaction &transaction);

    static void signTransaction(Transaction &transaction);

    static void fill_random(uint8_t *data, size_t size);

    static void print_hex(const uint8_t *data, size_t size);

private:
    ecc_pair_t _keys{};
    uint8_t compressed_pubkey[COMPRESSED_PUBLIC_KEY_SIZE]{};
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_SIGN);
};
