// Легковесная библиотека симметричного шифрования на C11.
// Блоковая, с фиксированным размером блока 16 байт.
// Имеет систему инициализации, поддержку вектора инициализации (IV),
// и шифрование/дешифрование с использованием пользовательского ключа.

// Компилировать с опцией -std=c11
#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct Crypto CryptoS;

// Структура для хранения симметричного ключа
typedef struct CryptoS_Key {
    uint8_t key[256];
    // Минимальная длина ключа - 32 бита
    size_t  len;
} CryptoS_Key;

// Буфер входных данных для шифрования или дешифрования.
typedef struct CryptoS_BufIn {
    const uint8_t *data;
    // len всегда кратен 16 иначе CSE_INVALID_ARG
    size_t        len;
} CryptoS_BufIn;

// Буфер выходных данных. Память должна быть выделена вызывающей стороной.
// Размер должен быть не меньше входных данных.
typedef struct CryptoS_BufOut {
    uint8_t *data;
    size_t  len;
} CryptoS_BufOut;

typedef enum CryptoS_Err {
    // Успешное завершение
    CSE_OK,
    // Повторная инициализация cr_init() без вызова cr_shutdown()
    CSE_ALREADY_INITIALIZED,
    // Один или несколько аргументов равны NULL, или длина входного буфера некорректна
    CSE_INVALID_ARG,
    // Слишком короткий ключ, длина меньше 4 байт
    CSE_BAD_KEY,

    /*
    // Зарезервировано для будущих реализаций:
    CSE_IV_FAIL,
    CSE_ENOMEM,
    CSE_BAD_ALIGN,
     */

} CryptoS_Err;

// Глобальная инициализация библиотеки - установка счетчика для Initialization
// Vector(IV). Допустим только один вызов за всё время жизни процесса.
CryptoS_Err cr_init();
// Сброс глогального счетчика вектора инициализации
void cr_shutdown();

// InitVector для состояния - текущее время + глобальный счетчик
// Для каждого CryptoS свой вектор инициализации.
CryptoS *cr_new();
void cr_free(CryptoS *cs);

// Шифровать данные. 
// Возвращает ошибку если указатели NULL.
// Возвращает ошибку если ключ короток.
CryptoS_Err cr_encrypt(
    CryptoS *cs, const CryptoS_BufIn *in, CryptoS_BufOut *out, CryptoS_Key k
);

// Расшифровать данные. 
// Возвращает ошибку если указатели NULL.
// Возвращает ошибку если ключ короток.
CryptoS_Err cr_decrypt(
    CryptoS *cs, const CryptoS_BufIn *in, CryptoS_BufOut *out, CryptoS_Key k
);

// Получить строковое представление ошибки.
const char *cr_errstr(CryptoS_Err e);
