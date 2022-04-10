#include "hash_functions.h"

/*
// TODO realization
rsa_pair_t generateKeys() {
    uint8_t *a = new uint8_t;
    uint8_t *b = new uint8_t;
    return {a, b};
}
*/

static void fill_random(uint8_t *data, size_t size) {
    ssize_t res = getrandom(data, size, 0);
    if (!(res < 0 || static_cast<size_t>(res) != size)) {
        // TODO exception
    }
}

static void print_hex(uint8_t *data, size_t size) {
    std::cerr << "0x";
    for (size_t i = 0; i < size; ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    std::cerr << std::endl;
}

hash_t sha256(const std::string &hash_object) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hash_object.c_str(), hash_object.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (uint8_t i: hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return ss.str();
}

void ecdsa() {
    // SHA-256 from Hello, world!
    uint8_t msg_hash[32] = {
            0x31, 0x5F, 0x5B, 0xDB, 0x76, 0xD0, 0x78, 0xC4,
            0x3B, 0x8A, 0xC0, 0x06, 0x4E, 0x4A, 0x01, 0x64,
            0x61, 0x2B, 0x1F, 0xCE, 0x77, 0xC8, 0x69, 0x34,
            0x5B, 0xFC, 0x94, 0xC7, 0x58, 0x94, 0xED, 0xD3,
    };
    print_hex(msg_hash, 32);

    secp256k1_pubkey pubkey;
    secp256k1_ecdsa_signature sig;
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

    uint8_t seckey[32];
    /* Если секретный ключ равен нулю или выходит за пределы допустимого диапазона (больше, чем порядок secp256k1), мы пытаемся выбрать новый ключ. Обратите внимание, что вероятность этого события ничтожно мала. */
    while (true) {
        fill_random(seckey, sizeof(seckey));
        if (secp256k1_ec_seckey_verify(ctx, seckey)) {
            break;
        }
    }

    return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);
    assert(return_val);

    uint8_t compressed_pubkey[33];
    size_t len = sizeof(compressed_pubkey);
    return_val = secp256k1_ec_pubkey_serialize(ctx, compressed_pubkey, &len, &pubkey, SECP256K1_EC_COMPRESSED);
    assert(return_val);
    assert(len == sizeof(compressed_pubkey));

    /*** Signing ***/

    /* Генерация подписи ECDSA `noncefp` и `ndata` позволяет передать пользовательскую функцию одноразового номера, передача `NULL` будет использовать безопасное значение по умолчанию RFC-6979. Подписание с допустимым контекстом, проверенным секретным ключом и функцией одноразового номера по умолчанию никогда не должно давать сбоев. */
    return_val = secp256k1_ecdsa_sign(ctx, &sig, msg_hash, seckey, nullptr, nullptr);
    assert(return_val);

    /* Сериализировать подпись в компактной форме*/
    uint8_t serialized_signature[64];
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
    int is_signature_valid = secp256k1_ecdsa_verify(ctx, &sig, msg_hash, &pubkey);

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

hash_t calculateHash(const Block &block) {
    std::stringstream ss;
    ss << block._nonce << block._previousBlockHash << block._currentBlockHash;
    for (const Transaction &transaction: block._listOfTransactions) {
        ss << '{' << transaction << '}';
    }
    return sha256(ss.str());
}

bool hashIsCorrect(hash_t current_hash) { // hash is correct in our terms when it starts with
    for (int i = 0; i < REQUIRED_LEN_OF_ZEROS_PREFIX_IN_HASH; ++i) {
        if (current_hash[i] != '0') {
            return false;
        }
    }
    return true;
}
