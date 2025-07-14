#include "number.h"

// проверка базовой инициализации из uint64_t
void test_init() {   
    Number nums[] = {
        num_new(0),
        num_new(1),        
        num_new(10),
        num_new(99),
        num_new(100),
        num_new(101),
    };

    assert(nums[0].nums_num == 0);
    assert(nums[0].nums[0] == 0);

    assert(nums[1].nums_num == 1);
    assert(nums[1].nums[0] == 1);

    assert(nums[2].nums_num == 1);
    assert(nums[2].nums[0] == 10);

    assert(nums[3].nums_num == 1);
    assert(nums[3].nums[0] == 99);

    assert(nums[4].nums_num == 2);
    assert(nums[4].nums[0] == 0);
    assert(nums[4].nums[1] == 1);

    assert(nums[5].nums_num == 2);
    assert(nums[5].nums[0] == 1);
    assert(nums[5].nums[1] == 1);

}

void check_str(const char *val, const char *should_be) {
    if (strcmp(val, should_be)) {
        printf("check_str: fail val '%s', should_be '%s'\n", val, should_be);
        abort();
    }
}

// проверка корректности сериализации в строку
void test_print() {
    Number  nums[] = { 
        num_new(0),            // 0
        num_new(1),            // 1
        num_new(2),            // 2
        // проверка на магических числах
        num_new(1010322),      // 3
        // проверка на магических числах
        num_new(10103220),     // 4
        num_new_str("0"),         // 5
        num_new_str("1"),         // 6
        num_new_str("123456789"), // 7
    };

    char buf[256] = {};

    num_prints(nums[0], buf, sizeof(buf));    
    check_str(buf, "0");

    num_prints(nums[1], buf, sizeof(buf));
    check_str(buf, "1");

    num_prints(nums[2], buf, sizeof(buf));
    check_str(buf, "2");

    num_prints(nums[3], buf, sizeof(buf));    
    check_str(buf, "1010322");

    num_prints(nums[4], buf, sizeof(buf));
    check_str(buf, "10103220");

    num_prints(nums[5], buf, sizeof(buf));
    check_str(buf, "0");

    num_prints(nums[6], buf, sizeof(buf));
    check_str(buf, "1");

    num_prints(nums[7], buf, sizeof(buf));
    check_str(buf, "123456789");
}

// сравнение a == b, a < b, a > b
// XXX: не проверяет крайние случаи
//Например:
//сравнение двух чисел с одинаковыми цифрами но разной длиной (01 vs 1)
//сравнение чисел с ведущими нулями (если такие допускаются)
void test_cmp() {
    Number  a = num_new(0),
            b = num_new(1),
            c = num_new_str("123456789"),
            d = num_new_str("123406789"),
            e = num_new_str("0"),
            f = num_new_str("1"),
            // g = num_new_str("123456789"),
            k = num_new_str("123406789");

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

// сумма чисел, от простых до больших
void test_add() {
    assert(num_cmp(num_add(num_new(900), num_new(100)), num_new_str("1000")) == 0);
    assert(num_cmp(num_add(num_new(100), num_new(900)), num_new_str("1000")) == 0);

    assert(num_cmp(num_add(num_new(1), num_new(2)), num_new_str("3")) == 0);
    assert(num_cmp(num_add(num_new(10), num_new(90)), num_new_str("100")) == 0);
    assert(num_cmp(num_add(num_new(100), num_new(912)), num_new_str("1012")) == 0);

    assert(num_cmp(num_add(num_new(12345), num_new(77777)), num_new_str("90122")) == 0);
}

// покомпонентный доступ
void test_digit_get() {
    assert(num_digit_get(num_new(0), 0) == 0);
    assert(num_digit_get(num_new(1), 0) == 1);
    assert(num_digit_get(num_new(10), 0) == 0);
    assert(num_digit_get(num_new(11), 0) == 1);
    assert(num_digit_get(num_new(120), 1) == 2);
    assert(num_digit_get(num_new(120), 2) == 1);
    assert(num_digit_get(num_new(23456), 4) == 2);
}

// покомпонентная модификация
void test_digit_set() {
    assert(num_cmp(num_digit_set(num_new(0), 0, 7), num_new(7)));
    assert(num_cmp(num_digit_set(num_new(10), 1, 8), num_new(80)));
    assert(num_cmp(num_digit_set(num_new(12345), 2, 7), num_new(12745)));


    num_digit_set(num_new(1), 3, 5); // ожидание: assert или ошибка
}

int main() {
    test_init();
    test_print();
    test_cmp();

    // test_add();
    // test_digit_get();
    // test_digit_set();

    // num_new(0);
    // num_new(1234);

    // printf("%d\n", 0 / 2);
    // printf("%d\n", 1 / 2);
    // printf("%d\n", 2 / 2);
    // printf("%d\n", 3 / 2);
    // printf("%d\n", 4 / 2);
 
    Number x = num_new_str("7778889"); 
    printf("x '%s'\n", num_sprint(x));
    Number y = num_digit_set(x, 0, 1);
    printf("y '%s'\n", num_sprint(y));

    return 0;
}
