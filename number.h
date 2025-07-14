/*
Библиотека длинной арифметики. 
Число хранится в 100ричной системе счисления.
для удобного извлечения десятичной цифры.

TODO: Умножение Карацубы
 */

#pragma once

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_MAX 256

typedef struct Number {
    // 100ричная система для быстрого сдвига и извлечения числа
    uint8_t     nums[NUMBER_MAX]; 
    size_t      nums_num;
} Number;

/*
typedef struct NumberRat {
    // NumberRat = p / q
    Number  p, q;
    // наличие ошибки округления
    bool    exact;
} NumberRat;
*/

static inline Number num_new(uint64_t x) {
    Number n = {};
    while (x) {
        // printf("%d\n", x % 100);
        n.nums[n.nums_num++] = x % 100;
        assert(n.nums_num < NUMBER_MAX);
        x /= 100;
    }   
    return n;
}

// только числа >= 0, знак нуля не поддеживается
static inline Number num_new_str(const char *s) {
    assert(s);
    Number n = {};
    const char *last = s;

    while (*last) {
        assert(isdigit(*last));
        last++;
    }

    last -= 1;
    
    while (last + 1 != s) {
        // printf("*last '%c'\n", *last);
        n.nums[n.nums_num++] = *last - '0';
        assert(n.nums_num < NUMBER_MAX);
        last--;
    }

    return n;
}

// создание числа из сырых данных.
// XXX: Какова максимальная длина len?
// XXX: Где находится старший и младший разряд?
static inline Number num_new_raw(const uint8_t *data, size_t len) {
    Number n = {};
    return n;
}

// распечатать число в буфер buf, максимальное количество символов - maxchars
// XXX: Каково максимальное количество символов для NUMBER_MAX?
size_t num_prints(Number n, char *buf, size_t maxchars) {
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

char *num_sprint(Number n) {
    // TODO: Добавить слоты
    static char buf[NUMBER_MAX];
    num_prints(n, buf, NUMBER_MAX);
    return buf;
}

static inline Number num_add(Number a, Number b) {
    Number n = {};
    return n;
}

// 235424352_3_1234237987
// Возвращает -1 если num ошибочен
int num_digit_get(Number n, int num) {
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

// XXX: Как сделать обработку если цифра num выходит за границы цисла?
static inline Number num_digit_set(Number n, int num, int digit) {
    assert(digit >= 0);
    assert(digit <= 10);
    if (num >= n.nums_num) {
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

// a > b    => 1
// a == b   => 0
// a < b    => -1
int num_cmp(Number a, Number b) {
    int maxlen = a.nums_num > b.nums_num ? a.nums_num : a.nums_num;
    for (int i = maxlen - 1; i > 0; i--) {
        if (a.nums[i] > b.nums[i])
            return 1;
        else if (a.nums[i] <= b.nums[i])
            return -1;
    }
    return 0;
}

bool num_eq(Number a, Number b) {
    return !num_cmp(a, b);
}

static inline Number num_mul_simple(Number a, Number b) {
    return (Number){};
}

static inline Number num_mul_karatsuba(Number a, Number b) {
    return (Number){};
}

static inline Number num_mul(Number a, Number b) {
    if (a.nums_num < 32 || b.nums_num < 32)
        return num_mul_simple(a, b);
    else
        return num_mul_karatsuba(a, b);
    //return (Number){};
}
