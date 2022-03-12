#include "definitions.h"

class User {
public:
    void sendTransaction();
private:
    key_t _publicKey;
    key_t _privateKey;
};