#pragma once

#include <iostream>

struct ZINA {
    static const size_t NUMBER_OF_DECIMAL_PLACES = 8;
    static const size_t MOD_OF_DECIMAL_PLACES = 1e8;

    size_t _integer_part;
    size_t _fractional_part; // NUMBER_OF_DECIMAL_PLACES symbols

    explicit ZINA(size_t integer_part);

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
