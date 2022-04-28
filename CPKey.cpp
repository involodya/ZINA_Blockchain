#include "CPKey.h"

CPKey::CPKey() : data_(nullptr) {}

CPKey::CPKey(const public_key_t& public_key)
        : data_(new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE]) {
    size_t len = COMPRESSED_PUBLIC_KEY_SIZE;
    auto return_val = secp256k1_ec_pubkey_serialize(ctx_, data_, &len,
                                                    &public_key, SECP256K1_EC_COMPRESSED);
    //TODO Exception
}

CPKey::CPKey(const CPKey &other)
        : data_(new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE]) {
    size_t len = COMPRESSED_PUBLIC_KEY_SIZE;
    public_key_t pubkey = other.getPublic();
    auto return_val = secp256k1_ec_pubkey_serialize(ctx_, data_, &len,
                                                    &pubkey, SECP256K1_EC_COMPRESSED);
    //TODO Exception
}

CPKey &CPKey::operator=(const CPKey &other) {
    data_ = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];
    size_t len = COMPRESSED_PUBLIC_KEY_SIZE;
    public_key_t pubkey = other.getPublic();
    auto return_val = secp256k1_ec_pubkey_serialize(ctx_, data_, &len,
                                                    &pubkey, SECP256K1_EC_COMPRESSED);
    return *this;
    //TODO Exception
}

CPKey::~CPKey() {
    delete[] data_;
    secp256k1_context_destroy(ctx_);
}

public_key_t CPKey::getPublic() const {
    secp256k1_pubkey pubkey;
    auto returnval = secp256k1_ec_pubkey_parse(ctx_, &pubkey, data_, COMPRESSED_PUBLIC_KEY_SIZE);
//    assert(returnval);
    return pubkey;
}

void CPKey::dbg() const {
    std::cerr << "CPKey:" << std::endl;
    std::cerr << "\tkey: " << *this << std::endl;
}

uint8_t *CPKey::getDataPointer() const {
    return data_;
}


std::ostream &operator<<(std::ostream &out, const CPKey &key) {
    out << "0x";
    out.setf(std::ios::hex, std::ios::basefield);
    for (size_t i = 0; i < COMPRESSED_PUBLIC_KEY_SIZE; ++i) {
        // out << static_cast<int>(key.getDataPointer()[i]) << ' ';
        out << std::setw(2) << std::setfill('0') << static_cast<int>(key.getDataPointer()[i]);

    }
    out.unsetf(std::ios::hex);
    return out;
}

bool CPKey::operator==(const CPKey &other) const {
    for (size_t i = 0; i < COMPRESSED_PUBLIC_KEY_SIZE; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool CPKey::operator<(const CPKey &other) const {
    for (size_t i = 0; i < COMPRESSED_PUBLIC_KEY_SIZE; ++i) {
        if (data_[i] < other.data_[i]) {
            return true;
        } else if (data_[i] > other.data_[i]) {
            return false;
        }
    }
    return false;
}
