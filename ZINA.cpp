#include "ZINA.h"
#include <exception>

ZINA::ZINA(size_t integer_part) : _integer_part(integer_part),
                                  _fractional_part(0) {}

ZINA::ZINA(size_t integer_part, size_t fractional_part) : _integer_part(integer_part +
                                                                        fractional_part / MOD_OF_DECIMAL_PLACES),
                                                          _fractional_part(fractional_part % MOD_OF_DECIMAL_PLACES) {}

ZINA &ZINA::operator+=(const ZINA &other) {
    _fractional_part += other._fractional_part % MOD_OF_DECIMAL_PLACES;
    _integer_part += other._integer_part + _fractional_part / MOD_OF_DECIMAL_PLACES;
    _fractional_part %= MOD_OF_DECIMAL_PLACES;
    return *this;
}

ZINA &ZINA::operator-=(const ZINA &other) {
    if ((other._integer_part > _integer_part) or
        (other._integer_part == _integer_part and other._fractional_part > _fractional_part)) {
            throw std::logic_error("ZINA can not be lower than 0");
    }
    _integer_part -= other._integer_part;
    if (other._fractional_part > _fractional_part) {
        _integer_part -= 1;
        _fractional_part += MOD_OF_DECIMAL_PLACES;
    }

    _fractional_part -= other._fractional_part;

    return *this;
}

ZINA ZINA::operator+(const ZINA &other) const {
    ZINA newZINA = *this;
    return newZINA += other;
}

ZINA ZINA::operator-(const ZINA &other) const {
    ZINA newZINA = *this;
    return newZINA -= other;
}

bool ZINA::operator==(const ZINA &other) const {
    return _integer_part == other._integer_part and _fractional_part == other._fractional_part;
}

bool ZINA::operator!=(const ZINA &other) const {
    return !(*this == other);
}

bool ZINA::operator<(const ZINA &other) const {
    return (_integer_part < other._integer_part) or
           (_integer_part == other._integer_part and _fractional_part < other._fractional_part);
}

bool ZINA::operator<=(const ZINA &other) const {
    return *this < other or *this == other;
}

bool ZINA::operator>(const ZINA &other) const {
    return !(*this <= other);
}

bool ZINA::operator>=(const ZINA &other) const {
    return !(*this < other);
}

void ZINA::dbg() const {
    std::cerr << "{" << *this << "}" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const ZINA &zina) {
    out << zina._integer_part << '.' << zina._fractional_part;
    return out;
}
