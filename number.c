#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

typedef struct Number {
    uint8_t     nums;
    int         sign;
    size_t      nums_num, nums_cap;
} Number;

/*
Требования:
    Сложение
        На месте
        С созданием нового экземпляра        
    Печать с выводом в десятичную систему
    Получение и изменение цифр числа в десятичной системе
*/

struct Number num_init(int64_t x) {

}

void num_shutdown(struct Number *n) {
    assert(n);
}

int main() {
    Number  a = num_init(0), 
            b = num_init(0);

    char buf_a[256] = {}, buf_b[256] = {};
    num_prints(buf, sizeof(buf));

    printf("a %s, b %s\n", buf_a, buf_b);

    num_shutdown(&a);
    num_shutdown(&b);

    return 0;
}