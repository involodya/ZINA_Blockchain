#include "hash_functions.h"


static void fill_random(uint8_t *data, size_t size) {
    ssize_t res = getrandom(data, size, 0);
    if (!(res < 0 || static_cast<size_t>(res) != size)) {
        // TODO exception
    }
}

static void print_hex(uint8_t *data, size_t size) {
    std::cerr << "0x";
    std::cerr.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < size; ++i) {
        std::cerr << static_cast<int>(data[i]);
    }
    std::cerr.unsetf(std::ios::hex);
    std::cerr << std::endl;
}

void ecdsa() {
    Hash msg_hash = Hash("Hello, world!");
    msg_hash.dbg();

    secp256k1_pubkey pubkey;
    /* Спецификация в secp256k1.h указывает, что для secp256k1_ec_pubkey_create требуется
     * объект контекста, инициализированный для подписи, а для secp256k1_ecdsa_verify
     * нужен контекст, инициализированный для проверки, поэтому мы создаем контекст
     * как для подписи, так и для проверки с помощью флагов SECP256K1_CONTEXT_SIGN и
     * SECP256K1_CONTEXT_VERIFY. */
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    // TODO exception
    uint8_t randomize[32];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(ctx, randomize);
    assert(return_val);

    /*** Key Generation ***/

    uint8_t seckey[SECRET_KEY_SIZE];
    /* Если секретный ключ равен нулю или выходит за пределы допустимого диапазона (больше, чем порядок secp256k1), мы пытаемся выбрать новый ключ. Обратите внимание, что вероятность этого события ничтожно мала. */
    while (true) {
        fill_random(seckey, sizeof(seckey));
        if (secp256k1_ec_seckey_verify(ctx, seckey)) {
            break;
        }
    }

    return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);
    assert(return_val);

    uint8_t compressed_pubkey[COMPRESSED_PUBLIC_KEY_SIZE];
    size_t len = sizeof(compressed_pubkey);
    return_val = secp256k1_ec_pubkey_serialize(ctx, compressed_pubkey, &len, &pubkey, SECP256K1_EC_COMPRESSED);
    assert(return_val);
    assert(len == sizeof(compressed_pubkey));

    /*** Signing ***/

    secp256k1_ecdsa_signature sig;
    /* Генерация подписи ECDSA `noncefp` и `ndata` позволяет передать пользовательскую функцию одноразового номера, передача `NULL` будет использовать безопасное значение по умолчанию RFC-6979. Подписание с допустимым контекстом, проверенным секретным ключом и функцией одноразового номера по умолчанию никогда не должно давать сбоев. */
    return_val = secp256k1_ecdsa_sign(ctx, &sig, msg_hash._hash, seckey, nullptr, nullptr);
    assert(return_val);

    /* Сериализировать подпись в компактной форме*/
    uint8_t serialized_signature[SERIALIZED_SIGNATURE_SIZE];
    return_val = secp256k1_ecdsa_signature_serialize_compact(ctx, serialized_signature, &sig);
    assert(return_val);


    /*** Verification ***/

    if (!secp256k1_ecdsa_signature_parse_compact(ctx, &sig, serialized_signature)) {
        throw std::exception(); // Failed parsing the signature
    }
    if (!secp256k1_ec_pubkey_parse(ctx, &pubkey, compressed_pubkey, sizeof(compressed_pubkey))) {
        throw std::exception(); // Failed parsing the public key
    }

    /* Verify a signature. This will return 1 if it's valid and 0 if it's not. */
    int is_signature_valid = secp256k1_ecdsa_verify(ctx, &sig, msg_hash._hash, &pubkey);

    std::cerr << "Is the signature valid: " << (is_signature_valid ? "true" : "false") << "\n";
    std::cerr << "Secret Key: ";
    print_hex(seckey, sizeof(seckey));
    std::cerr << "Public Key: ";
    print_hex(compressed_pubkey, sizeof(compressed_pubkey));
    std::cerr << "Signature: ";
    print_hex(serialized_signature, sizeof(serialized_signature));

    // destroy and memory clear
    secp256k1_context_destroy(ctx);
    memset(seckey, 0, sizeof(seckey));
}

bool isHashCorrect(const hash_t &current_hash) { // hash is correct in our terms when it starts with
    /* TODO
     * retutn current_hash < SOME_HASH;
     */
    return true;
}
