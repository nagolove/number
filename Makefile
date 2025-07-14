# Makefile для number-test

CC = gcc
CFLAGS = -Wall -std=c2x
LDFLAGS = -lm
TARGET = number-test.exe
SRC = number-test.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

run: all
	reset && ./$(TARGET)

clean:
	rm -f $(TARGET)

