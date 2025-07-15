#!/usr/bin/env python3

import random

# Максимальное количество десятичных цифр
MAX_DIGITS = 512

# Количество тестов
NUM_TESTS = 100

# Генерация случайного большого числа (до 512 цифр)
def generate_big_number():
    length = random.randint(1, MAX_DIGITS)
    digits = [str(random.randint(1, 9))]  # первая цифра ≠ 0
    digits += [str(random.randint(0, 9)) for _ in range(length - 1)]
    num_str = ''.join(digits)
    if random.choice([True, False]):
        num_str = '-' + num_str
    return int(num_str)

# Вычисление операции и возврат строки вида "<a> <op> <b> = <result>"
def generate_expression():
    a = generate_big_number()
    b = generate_big_number()
    op = random.choice(['+', '-', '*', '/'])

    # Обработка деления: избегаем деления на ноль и делаем результат целым
    if op == '/':
        # Обеспечить b ≠ 0
        while b == 0:
            b = generate_big_number()
        # Обеспечить |a| > |b|
        if abs(a) < abs(b):
            a, b = b, a
        result = a // b
        op_str = '/'
    elif op == '+':
        result = a + b
        op_str = '+'
    elif op == '-':
        result = a - b
        op_str = '-'
    elif op == '*':
        result = a * b
        op_str = '*'
    return f"{a} {op_str} {b} = {result}"

# Генерация и запись в файл
with open("number_test_data.txt", "w") as f:
    for _ in range(NUM_TESTS):
        f.write(generate_expression() + "\n")
