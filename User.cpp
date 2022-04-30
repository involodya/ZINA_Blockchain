#include "User.h"


User::User() {
    // TODO exception
    uint8_t randomize[SECRET_KEY_SIZE];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(_ctx, randomize);
    assert(return_val);

    /*** Key Generation ***/

    auto seckey = new uint8_t[SECRET_KEY_SIZE];
    /* Если секретный ключ равен нулю или выходит за пределы допустимого диапазона 
    (больше, чем порядок secp256k1), мы пытаемся выбрать новый ключ. 
    Обратите внимание, что вероятность этого события ничтожно мала. */
    while (true) {
        fill_random(seckey, SECRET_KEY_SIZE);
        if (secp256k1_ec_seckey_verify(_ctx, seckey)) {
            break;
        }
    }
    _keys.secret_key = seckey;

    return_val = secp256k1_ec_pubkey_create(_ctx, &_keys.public_key, _keys.secret_key);
    assert(return_val);

    _compressed_pubkey = CPKey(_keys.public_key);
}

User::User(const secret_key_t &secret_key) {
    _keys.secret_key = secret_key;

    auto return_val = secp256k1_ec_pubkey_create(_ctx, &_keys.public_key, _keys.secret_key);
    assert(return_val);

    _compressed_pubkey = CPKey(_keys.public_key);
}

void User::fill_random(uint8_t *data, size_t size) {
    ssize_t res = getrandom(data, size, 0);
    if (!(res < 0 || static_cast<size_t>(res) != size)) {
        // TODO exception
    }
}

void User::print_hex(const uint8_t *data, size_t size) {
    std::cerr << "0x";
    std::cerr.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < size; ++i) {
        std::cerr << static_cast<int>(data[i]);
    }
    std::cerr.unsetf(std::ios::hex);
    std::cerr << std::endl;
}

void User::sendTransaction(Transaction &transaction) {
    signTransaction(transaction);

    //TODO send to network
}

void User::signTransaction(Transaction &transaction) {
//    /* Генерация подписи ECDSA `noncefp` и `ndata` позволяет передать пользовательскую функцию одноразового номера, передача `NULL` будет использовать безопасное значение по умолчанию RFC-6979. Подписание с допустимым контекстом, проверенным секретным ключом и функцией одноразового номера по умолчанию никогда не должно давать сбоев. */

    std::cerr << transaction.getValueHash() << std::endl;
    auto return_val = secp256k1_ecdsa_sign(_ctx, &transaction._signature, transaction.getValueHash()._hash,
                                           _keys.secret_key, nullptr, nullptr);
    assert(return_val);

//    /* Сериализировать подпись в компактной форме*/
    return_val = secp256k1_ecdsa_signature_serialize_compact(_ctx, transaction.serialized_signature,
                                                             &transaction._signature);
    assert(return_val);
}

void User::dbg() const {
    std::cerr << "User" << std::endl;
    std::cerr << "\tSecret Key: ";
    print_hex(_keys.secret_key, SECRET_KEY_SIZE);
    std::cerr << "\tPublic Key: " << _compressed_pubkey << std::endl;
}

User::~User() {
    secp256k1_context_destroy(_ctx);
}

CPKey User::getCPKey() const {
    return _compressed_pubkey;
}

