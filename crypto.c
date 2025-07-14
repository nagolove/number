#include "crypto.h"

#include <stdbool.h>

// флаг инициализации библиотеки
static _Atomic(bool) cr_inited = false;
// глобальный счетчик для вектора инициализации 
static _Atomic(uint32_t) cr_iv_counter = 0;


