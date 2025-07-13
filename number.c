/*
Библиотека длинной арифметики. Число хранится в 100ричной системе счисления
для удобного извлечения десятичной цифры.

TODO: Умножение Карацубы
 */

#include "number.h"

void test_cmp() {
    Number  a = num_init(0),
            b = num_init(1),
            c = num_inits("123456789"),
            d = num_inits("123406789"),
            e = num_inits("0"),
            f = num_inits("1"),
            // g = num_inits("123456789"),
            k = num_inits("123406789");

    assert(num_cmp(a, a) == 0);
    assert(num_cmp(b, b) == 0);
    assert(num_cmp(c, c) == 0);
    assert(num_cmp(d, d) == 0);

    assert(num_cmp(a, e) == 0);
    assert(num_cmp(b, f) == 0);
    assert(num_cmp(d, k) == 0);

    assert(num_cmp(a, b) == -1);
    assert(num_cmp(b, a) == 1);

    assert(num_cmp(c, d) == 1);
    assert(num_cmp(d, c) == -1);
}

void test_add() {
    assert(num_eq(num_add(num_init(900), num_init(100)), num_inits("1000")) == 0);
    assert(num_eq(num_add(num_init(100), num_init(900)), num_inits("1000")) == 0);

    assert(num_eq(num_add(num_init(1), num_init(2)), num_inits("3")) == 0);
    assert(num_eq(num_add(num_init(10), num_init(90)), num_inits("100")) == 0);
    assert(num_eq(num_add(num_init(100), num_init(912)), num_inits("1012")) == 0);

    assert(num_eq(num_add(num_init(12345), num_init(77777)), num_inits("90122")) == 0);
}

void test_digit_get() {
    assert(num_digit_get(num_init(0), 0) == 0);
    assert(num_digit_get(num_init(1), 0) == 1);
    assert(num_digit_get(num_init(10), 0) == 0);
    assert(num_digit_get(num_init(11), 0) == 1);
    assert(num_digit_get(num_init(120), 1) == 2);
    assert(num_digit_get(num_init(120), 2) == 1);
    assert(num_digit_get(num_init(23456), 4) == 2);
}

void test_digit_set() {
    assert(num_eq(num_digit_set(num_init(0), 0, 7), num_init(7)));
    assert(num_eq(num_digit_set(num_init(10), 1, 8), num_init(80)));
    assert(num_eq(num_digit_set(num_init(12345), 2, 7), num_init(12745)));
}

int main() {
    test_init();
    test_print();
    // test_cmp();

    // test_add();
    // test_digit_get();
    // test_digit_set();

    // num_init(0);
    // num_init(1234);

    // printf("%d\n", 0 / 2);
    // printf("%d\n", 1 / 2);
    // printf("%d\n", 2 / 2);
    // printf("%d\n", 3 / 2);
    // printf("%d\n", 4 / 2);
 
    Number x = num_inits("7778889"); 
    printf("x '%s'\n", num_sprint(x));
    Number y = num_digit_set(x, 0, 1);
    printf("y '%s'\n", num_sprint(y));

    return 0;
}
