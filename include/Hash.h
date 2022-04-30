#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <unordered_map>

// #define BOOST_ERROR_CODE_HEADER_ONLY
// #include <boost/system/error_code.hpp>
// #include <boost/asio/ssl/impl/src.hpp>
#include <openssl/sha.h>


#include <secp256k1.h>


#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>


const size_t HASH_SIZE = SHA256_DIGEST_LENGTH;


struct Hash {
    uint8_t *_hash = nullptr;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    Hash();

    explicit Hash(const std::string &hash_object);

    Hash(const Hash &other);

    Hash &operator=(const Hash &other);

    Hash &set(const std::string &hash);

    ~Hash();

    bool operator==(const Hash &other) const;

    bool operator<(const Hash &other) const;

    void dbg() const;
};


std::ostream &operator<<(std::ostream &out, const Hash &hash);


static Hash THRESHOLD_HASH = Hash().set("0x0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");