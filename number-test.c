/* vim: fdm=marker */

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
    struct {
        Number n;
        char *str;
    } nums[] = { 
        { num_new(0), "0" },
        { num_new(1), "1" },
        { num_new(2), "2" },
        // проверка на магических числах
        { num_new(1010322), "1010322" },
        // проверка на магических числах
        { num_new(10103220), "10103220" },
        { num_new_str("0"), "0" },
        { num_new_str("1"), "1" },
        { num_new_str("123456789"), "123456789" },
        { num_new(10103220), "10103220" },
    };

    int num = sizeof(nums) / sizeof(nums[0]);
    for (int i = 0; i < num; i++) {
        char buf[256] = {};
        num_prints(nums[i].n, buf, sizeof(buf));    
        check_str(buf, nums[i].str);
    }

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

void parse_file(
    const char *fname,
    // возвращает истину для прерывания цикла чтения
    bool (*parse_tok)(const char *tok, void *ctx),
    // возвращает истину для прерывания цикла чтения
    bool (*parse_newline)(void *ctx),
    void *ctx
) {
    assert(fname);
    assert(parse_tok);
    assert(parse_newline);

    FILE *f = fopen(fname, "r");
    if (!f) {
        perror("fopen");
        abort();
    }

    char line[1024 * (1 + 1 + 1 /* a + b = c */ )];
    while (fgets(line, sizeof(line), f)) {
        // Удаление символа перевода строки (если есть)
        line[strcspn(line, "\r\n")] = '\0';

        char *token = strtok(line, " ");
        while (token) {
            static char buf[1024];
            strncpy(buf, token, sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = '\0';

            // отладка:
            printf("token: '%s'\n", buf);

            if (parse_tok(buf, ctx)) {
                fclose(f);
                return;
            }

            token = strtok(NULL, " ");
        }

        if (parse_newline(ctx)) {
            fclose(f);
            return;
        }
    }

    fclose(f);
}

typedef enum TestExprState {
    TES_A,
    TES_OP,
    TES_B,
    TES_EQ,
    TES_RESULT,
} TestExprState;

typedef enum TestExprOp {
    TEO_PLUS,
    TEO_MINUS,
    TEO_MUL,
    TEO_DIV,
    TEO_LAST,
} TestExprOp;

typedef struct TestExpr {
    TestExprState state;
    TestExprOp    op;
    Number        a, b, result;
} TestExpr;

bool on_read_newline(void *ctx) {
    TestExpr *expr = ctx;
    memset(expr, 0, sizeof(*expr));
    return false;
}

bool on_read_tok(const char *tok, void *ctx) {
    printf("on_read: tok '%s'\n", tok);

    TestExpr *expr = ctx;
    switch (expr->state) {
        //case TES_NONE: memset(expr, 0, sizeof(*expr)); break;
        case TES_A: expr->a = num_new_str(tok); expr->state++; break;
        case TES_OP: {

            if (strcmp(tok, "-") == 0) {
                expr->op = TEO_MINUS;
            } else if (strcmp(tok, "+") == 0) {
                expr->op = TEO_PLUS;
            } else if (strcmp(tok, "*") == 0) {
                expr->op = TEO_MUL;
            } else if (strcmp(tok, "/") == 0) {
                expr->op = TEO_DIV;
            } else {
                fprintf(stderr, "Unknown operator '%s'\n", tok);
                abort();
            }

            expr->state++;

            break;
        }
        case TES_B: expr->b = num_new_str(tok); expr->state++; break;
        case TES_EQ: 
            if (strcmp(tok, "=") != 0) {
                fprintf(stderr, "Expected '=', got '%s'\n", tok);
                abort();
            }
            expr->state++; 
            break;
        case TES_RESULT: {
            expr->result = num_new_str(tok); 

            Number x = {};
            switch (expr->op) {
                case TEO_PLUS: x = num_add(expr->a, expr->b);  break;
                case TEO_MINUS: x = num_sub(expr->a, expr->b); break;
                case TEO_MUL: x = num_mul(expr->a, expr->b); break;
                case TEO_DIV: x = num_div(expr->a, expr->b); break;
                case TEO_LAST: break;
            }

            if (!num_eq(x, expr->result)) {
                // ошибочное выражение
                const char *s = (expr->op == TEO_PLUS ? "+" : 
                                 expr->op == TEO_MINUS ? "-" : 
                                 expr->op == TEO_MUL ? "*" : "/");
                fprintf(
                    stderr,
                    "FAIL: %s ? %s = %s, got %s\n",
                    num_sprint(expr->a), s, 
                    num_sprint(expr->b), num_sprint(x)
                );
                abort();
            }

            expr->state = 0;
            break;
        }
        //case TES_LAST: expr->state = 0; break;
    };

    return false;
}

void test_by_generated_data() {
    TestExpr expr = {};
    parse_file("number_test_data.txt", on_read_tok, on_read_newline, &expr);
}

int main() {
    test_init();
    test_print();
    test_cmp();
    test_by_generated_data();

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

    /*
    Number x = num_new_str("7778889"); 
    printf("x '%s'\n", num_sprint(x));
    Number y = num_digit_set(x, 0, 1);
    printf("y '%s'\n", num_sprint(y));
    */

    return 0;
}
