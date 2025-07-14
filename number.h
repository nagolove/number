/*
Библиотека длинной арифметики. 
Число хранится в 100ричной системе счисления.
для удобного извлечения десятичной цифры.
 */

#pragma once

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUMBER_MAX 256

typedef struct Number {
    // 100ричная система для быстрого сдвига и извлечения числа
    // Используется little-endian
    // nums[0] — младший стоичный разряд (least significant)
    // nums[len - 1] — старший стоичный разряд
    uint8_t     nums[NUMBER_MAX]; 
    size_t      nums_num;
    bool        nan, 
                neg;
} Number;

/*
typedef struct NumberRat {
    // NumberRat = p / q
    Number  p, q;
    // наличие ошибки округления
    bool    noexact;
} NumberRat;

typedef struct NumberC {
    NumberRat i, r;
    // наличие ошибки округления
    bool      noexact;
} NumberC;
*/

static inline bool num_is_nun(Number n) {
    return n.nan;
}

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
static inline Number num_new_raw(const uint8_t *data, size_t len) {
    Number n = {};
    if (!data || len > NUMBER_MAX) {
        n.nan = true;
        return n;
    }

    // допустим, data[0] — младший разряд
    for (size_t i = 0; i < len; i++) {
        if (data[i] >= 100) {
            n.nan = true;
            return n;
        }
        n.nums[i] = data[i];
    }
    n.nums_num = len;
    return n;

}

// распечатать число в буфер buf, максимальное количество символов - maxchars
// INFO: максимальное количество символов для NUMBER_MAX - maxchars = 2 * NUMBER_MAX + 1
size_t num_prints(Number n, char *buf, size_t maxchars) {
    if (!buf || maxchars == 0)
        return 0;

    if (n.nan) {
        snprintf(buf, maxchars, "nan");
        return 3;
    }

    if (n.nums_num == 0 || (n.nums_num == 1 && n.nums[0] == 0)) {
        buf[0] = '0';
        buf[1] = '\0';
        return 1;
    }

    char tmp[NUMBER_MAX * 2 + 1];
    size_t tmp_len = 0;

    for (int i = n.nums_num - 1; i >= 0; i--) {
        uint8_t val = n.nums[i];
        int hi = val / 10;
        int lo = val % 10;

        if (i == (int)(n.nums_num - 1)) {
            // Первая (старшая) ячейка: может быть одно- или двухзначной
            if (hi > 0) tmp[tmp_len++] = '0' + hi;
        } else {
            tmp[tmp_len++] = '0' + hi;
        }

        tmp[tmp_len++] = '0' + lo;
    }

    // Снимаем ведущие нули
    size_t i = 0;
    while (i < tmp_len && tmp[i] == '0') i++;

    if (i == tmp_len) {
        strcpy(buf, "0");
        return 1;
    }

    size_t len = tmp_len - i;
    len = (len < maxchars - 1) ? len : maxchars - 1;

    memcpy(buf, tmp + i, len);
    buf[len] = '\0';
    return len;
}

char *num_sprint(Number n) {
    static char pool[4][NUMBER_MAX * 2 + 1];
    static int index = 0;
    index = (index + 1) % 4;
    num_prints(n, pool[index], sizeof(pool[index]));
    return pool[index];
}

static inline Number num_add(Number a, Number b) {
    if (a.nan || b.nan)
        return (Number){ .nan = true };

    Number result = {};
    size_t maxlen = a.nums_num > b.nums_num ? a.nums_num : b.nums_num;

    int carry = 0;
    for (size_t i = 0; i < maxlen || carry; i++) {
        int av = i < a.nums_num ? a.nums[i] : 0;
        int bv = i < b.nums_num ? b.nums[i] : 0;

        int sum = av + bv + carry;
        if (i >= NUMBER_MAX) return (Number){ .nan = true };
        result.nums[i] = sum % 100;
        carry = sum / 100;
    }
    result.nums_num = maxlen + (carry != 0);
    if (carry)
        result.nums[maxlen] = carry;

    return result;
}

Number num_trim_leading_zeros(Number n) {
    if (n.nan)
        return n;

    return n;
}

// 235424352_3_1234237987
// Возвращает -1 если num ошибочен
int num_digit_get(Number n, int num) {
    if (n.nan)
        return -1;

    if (num >= n.nums_num) {
        return -1;
    }

    int byte_index = num / 2;
    if ((size_t)byte_index >= n.nums_num)
        return -1;

    uint8_t byte = n.nums[byte_index];
    return (num % 2 == 0) ? (byte % 10) : (byte / 10);
}

static inline Number num_digit_set(Number n, int num, int digit) {
    assert(digit >= 0);
    assert(digit <= 10);
    assert(num >= 0);
    assert(num < NUMBER_MAX);

    if (num >= n.nums_num) {
        n.nan = true;
        return n;
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
// Если одно или оба числа - nan, то возвращается INT_MIN
int num_cmp(Number a, Number b) {

    if (a.nan || b.nan) {
        return INT_MIN;
    }

    int maxlen = a.nums_num > b.nums_num ? a.nums_num : b.nums_num;
    for (int i = maxlen - 1; i >= 0; i--) {
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
