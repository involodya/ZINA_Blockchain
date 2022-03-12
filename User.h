#include "definitions.h"

class User {
public:
    void sendTransaction();
private:
    user_key_t _publicKey;
    user_key_t _privateKey;
};