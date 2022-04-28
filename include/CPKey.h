#pragma once

#include "constants.h"

struct CPKey {
private:
    secp256k1_context *ctx_ = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    uint8_t *data_;
public:
    CPKey();

    CPKey(const public_key_t &public_key);

    CPKey(const CPKey &other);

    CPKey &operator=(const CPKey &other);

    ~CPKey();

    public_key_t getPublic() const;
    uint8_t * getDataPointer() const;

    void dbg() const;
};


std::ostream &operator<<(std::ostream &out, const CPKey &key);
