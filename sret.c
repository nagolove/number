#include <stdint.h>

struct Big { uint8_t x[256]; };
struct Big foo() {
    struct Big b = {{0}};
    b.x[0] = 42;
    return b;
}

int main() {
    foo();
    return 0;
}
