#include "ZINA.h"
#include <cassert>

void test1() {
    ZINA x (17, 98);
    ZINA y (12, 10);
    x -= y;
    assert(x == ZINA(5, 88));
    assert(x + ZINA(0, 0) == ZINA(5, 88));
    assert(x - ZINA(1, 0) == ZINA(4, 88));
    x += (x - x);
    assert(x == ZINA(5, 88));
    x += ZINA(1, ZINA::MOD_OF_DECIMAL_PLACES - 1);
    assert(x == ZINA(7, 87));
    x -= ZINA(1, ZINA::MOD_OF_DECIMAL_PLACES - 1);
    assert(x == ZINA(5, 88));
}

void test2() {
    ZINA x (17, 98);
    ZINA y (12, 17);
    
    assert(x >= ZINA(5, 88));
    assert(x >= y);
    assert(x != y);
    try
    {
        y -= x;
    }
    catch(const std::logic_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int main() {
    test1();
    std::cerr << "Test 1 passed\n";
    test2();
    std::cerr << "Test 2 passed\n";
    // std::cout << x;
}