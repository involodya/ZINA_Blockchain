#pragma once

#include "constants.cpp"

struct CPKey {
    CPKey();

    CPKey(const public_key_t &public_key);

    CPKey(const CPKey &other);

    CPKey &operator=(const CPKey &other);

    ~CPKey();

    public_key_t getPublic() const;
    uint8_t * getDataPointer() const;

    void dbg() const;

    void set(uint8_t* new_data);

    bool operator<(const CPKey &other) const;
    bool operator==(const CPKey &other) const;
private:
    secp256k1_context *ctx_ = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    uint8_t *data_;
};


std::ostream &operator<<(std::ostream &out, const CPKey &key);
std::istream& operator>>(std::istream& in, CPKey &key);
