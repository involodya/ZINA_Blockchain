#include "User.h"


User::User() {
//    ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_SIGN);
    // TODO exception
    uint8_t randomize[32];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(ctx, randomize);
    assert(return_val);

    /*** Key Generation ***/

    auto seckey = new uint8_t[32];
    /* Если секретный ключ равен нулю или выходит за пределы допустимого диапазона (больше, чем порядок secp256k1), мы пытаемся выбрать новый ключ. Обратите внимание, что вероятность этого события ничтожно мала. */
    while (true) {
        fill_random(seckey, SECRET_KEY_SIZE);
        if (secp256k1_ec_seckey_verify(ctx, seckey)) {
            break;
        }
    }
    *this = User(seckey);
}

User::User(const secret_key_t &secret_key) {
    _keys.secret_key = secret_key;

    uint8_t randomize[SECRET_KEY_SIZE];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(ctx, randomize);
    assert(return_val);

    return_val = secp256k1_ec_pubkey_create(ctx, &_keys.public_key, secret_key);
    assert(return_val);

    size_t len = sizeof(compressed_pubkey);
    return_val = secp256k1_ec_pubkey_serialize(ctx, compressed_pubkey, &len, &_keys.public_key,
                                               SECP256K1_EC_COMPRESSED);
    assert(return_val);
    assert(len == sizeof(compressed_pubkey));
}

void User::fill_random(uint8_t *data, size_t size) {
    ssize_t res = getrandom(data, size, 0);
    if (!(res < 0 || static_cast<size_t>(res) != size)) {
        // TODO exception
    }
}

void User::print_hex(const uint8_t *data, size_t size) {
    std::cerr << "0x";
    for (size_t i = 0; i < size; ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    std::cerr << std::endl;
}

void User::sendTransaction(Transaction &transaction) {
    signTransaction(transaction);

    //TODO send to network
}

//TODO realization
void User::signTransaction(Transaction &transaction) {
    transaction._signature;
}

void User::dbg() const {
    std::cerr << "User" << std::endl;
    std::cerr << "\tSecret Key: ";
    print_hex(_keys.secret_key, SECRET_KEY_SIZE);
    std::cerr << "\tPublic Key: ";
    print_hex(compressed_pubkey, COMPRESSED_PUBLIC_KEY_SIZE);
}

User::~User() {
    secp256k1_context_destroy(ctx);
    memset(_keys.secret_key, 0, SECRET_KEY_SIZE);
}
