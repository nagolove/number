#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_MAX 20

typedef struct Number {
    uint8_t     nums[NUM_MAX]; // 256ричная  или 100ричная система
    size_t      nums_num;
} Number;

struct Number num_init(uint64_t x) {
    struct Number n = {};
    while (x) {
        // printf("%d\n", x % 100);
        n.nums[n.nums_num++] = x % 100;
        assert(n.nums_num < NUM_MAX);
        x /= 100;
    }   
    return n;
}

// только числа >= 0
struct Number num_inits(const char *s) {
    assert(s);
    struct Number n = {};
    const char *last = s;

    while (*last) {
        assert(isdigit(*last));
        last++;
    }

    last -= 1;
    
    while (last + 1 != s) {
        // printf("*last '%c'\n", *last);
        n.nums[n.nums_num++] = *last - '0';
        assert(n.nums_num < NUM_MAX);
        last--;
    }

    return n;
}

size_t num_prints(struct Number n, char *buf, size_t maxchars) {
    printf("num_prints: n.nums_num %zu, maxchars %zu\n", n.nums_num, maxchars);

    // писать символы справа на лево
    assert(buf);

    char tmp[maxchars], *ptmp = tmp;
    memset(tmp, 0, sizeof(tmp));
    size_t written = 0;

    if (!maxchars)
        return 0;
        
    printf("n.nums[0] = %d\n", (int)n.nums[0]);

    // printf("num_prints: n.num_num %zu\n", n.nums_num);
    if (!n.nums_num || (n.nums_num == 1 && n.nums[0] == 0)) {
        printf("zero\n");
        *buf++ = '0';
        *buf = 0;
        return 1;
    }

    for (int i = n.nums_num - 1; i >= 0; i--) {
        // printf("n.nums[%d] = %d\n", i, n.nums[i]);

        int hi = n.nums[i] / 10, lo = n.nums[i] % 10;

        // printf("hi %d, lo %d\n", hi, lo);

        // if (hi)
            *ptmp++ = hi + '0', written++;

        if (written >= maxchars) {
            // printf("written >= maxchars 1\n");
            return written;
        }

        *ptmp++ = lo + '0', written++;

        if (written >= maxchars) {
            // printf("written >= maxchars 2\n");
            return written;
        }
    }

    ptmp = tmp;

    // printf("num_prints: tmp '%s'\n", tmp);
    // /*
    while (*ptmp + 1) {
        if (*ptmp == '0') {
            // ptmp--;
            // break;
            ptmp++;
        } else 
            break;        
    }
    // */
    // printf("num_prints: ptmp '%s'\n", ptmp);

    //memmove();
    strcpy(buf, ptmp);

    printf("num_prints: buf after removing leading zeros '%s'\n", buf);
    return written;
}

char *num_sprint(struct Number n) {
    static char buf[NUM_MAX];
    num_prints(n, buf, NUM_MAX);
    return buf;
}

struct Number num_add(struct Number a, struct Number b) {
    struct Number n = {};
    return n;
}

// 235424352_3_1234237987
// Возвращает -1 если num ошибочен
int num_digit_get(struct Number n, int num) {
    printf("num_digit_get: num %d\n", num);
    if (num >= n.nums_num) {
        printf("num >= n.nums_num\n");
        return -1;
    }
    int digit = n.nums[num / 2];
    // return digit % 2 ? digit % 10 : digit / 10;
    
    if (digit % 2 == 0) {
        // lo
        return digit / 10;
    } else 
        // lo
        return digit % 10;
}

// Если цифра num выходит за границы цисла, то вызывается исключительная ситуация.
struct Number num_digit_set(struct Number n, int num, int digit) {
    assert(digit >= 0);
    assert(digit <= 10);
    if (num >= n.nums_num) {
        abort();
    }
    uint8_t *_digit = &n.nums[num / 2];
    if (num % 2) {
        // lo
        *_digit = *_digit + *_digit / 10;
    } else {
        // hi
        *_digit = *_digit * 10 + digit / 10;
    }
    return n;
}

void test_init() {   
    Number nums[] = {
        num_init(0),
        num_init(1),        
        num_init(10),
        num_init(99),
        num_init(100),
        num_init(101),
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

void test_print() {
    Number  nums[] = { 
        num_init(0),            // 0
        num_init(1),            // 1
        num_init(2),            // 2
        num_init(1010322),      // 3
        num_init(10103220),     // 4
        num_inits("0"),         // 5
        num_inits("1"),         // 6
        num_inits("123456789"), // 7
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

// a > b    => 1
// a == b   => 0
// a < b    => -1
int num_cmp(struct Number a, struct Number b) {
    int maxlen = a.nums_num > b.nums_num ? a.nums_num : a.nums_num;
    for (int i = maxlen - 1; i > 0; i--) {
        if (a.nums[i] > b.nums[i])
            return 1;
        else if (a.nums[i] <= b.nums[i])
            return -1;
    }
    return 0;
}

bool num_eq(struct Number a, struct Number b) {
    return !num_cmp(a, b);
}

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