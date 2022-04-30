#pragma once

#include <iostream>

#include <secp256k1.h>

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>

struct ZINA {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned version);

    static const size_t NUMBER_OF_DECIMAL_PLACES = 8;
    static const size_t MOD_OF_DECIMAL_PLACES = 1e8;

    size_t _integer_part;
    size_t _fractional_part; // NUMBER_OF_DECIMAL_PLACES symbols

    explicit ZINA(size_t integer_part);

    ZINA() = default;

    ZINA(size_t integer_part, size_t fractional_part);

    ZINA &operator+=(const ZINA &other);
    ZINA &operator-=(const ZINA &other);

    ZINA operator+(const ZINA &other) const;
    ZINA operator-(const ZINA &other) const;

    bool operator==(const ZINA &other) const;
    bool operator!=(const ZINA &other) const;
    bool operator<(const ZINA &other) const;
    bool operator>(const ZINA &other) const;
    bool operator<=(const ZINA &other) const;
    bool operator>=(const ZINA &other) const;

    void dbg() const;
};

std::ostream &operator<<(std::ostream &out, const ZINA &zina);
std::istream &operator>>(std::istream &in, ZINA &zina);
