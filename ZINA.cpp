#include "ZINA.h"
#include <exception>

ZINA::ZINA(size_t integer_part) : _integer_part(integer_part),
                                  _fractional_part(0) {}

ZINA::ZINA(size_t integer_part, size_t fractional_part) : _integer_part(integer_part +
                                                                        fractional_part / MOD_OF_DECIMAL_PLACES),
                                                          _fractional_part(fractional_part % MOD_OF_DECIMAL_PLACES) {}

ZINA::ZINA(const std::string& zina_as_string) {
    std::string local_zina_as_string = zina_as_string;
    if (local_zina_as_string == "") local_zina_as_string = "0";
    std::string decimal_part = local_zina_as_string, fractional_part = "0";
    for (size_t i = 0; i < local_zina_as_string.size(); ++i) {
        if (local_zina_as_string[i] == '.') {
            decimal_part = local_zina_as_string.substr(0, i);
            fractional_part = local_zina_as_string.substr(i + 1);
            break;
        }
    }
    fractional_part += std::string(ZINA::NUMBER_OF_DECIMAL_PLACES - fractional_part.size(), '0');
    *this = {std::stoull(decimal_part), std::stoull(fractional_part)};
}


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

template<class Archive>
void ZINA::serialize(Archive &ar, const unsigned int version) {
    ar & _integer_part;
    ar & _fractional_part;
}

std::ostream &operator<<(std::ostream &out, const ZINA &zina) {
    std::string fractional_part = std::to_string(zina._fractional_part);
    while (fractional_part.size() > 1 && fractional_part.back() == '0') fractional_part.pop_back();
    out << zina._integer_part << '.' << fractional_part;
    return out;
}


std::istream &operator>>(std::istream &in, ZINA &zina) {
    in >> zina._integer_part >> zina._fractional_part;
    return in;
}

std::string ZINA::toString() const {
    std::stringstream s;
    s << *this;
    return s.str();
}