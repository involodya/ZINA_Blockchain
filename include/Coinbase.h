#pragma once

#include "constants.cpp"

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>

struct Coinbase {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    hash_t _hashOfRecipient;
    currency_t _value = BASIC_VALUE_OF_COINBASE_TRANSACTION;
    std::string _message;

    Coinbase(const hash_t &hashOfRecipient,
                currency_t value, const std::string& message);
    Coinbase() = default;
    void dbg();
};

std::ostream &operator<<(std::ostream &out, const Coinbase &coinbase);