# Makefile для number-test

CC = gcc
CFLAGS = -Wall -std=c2x -g3
LDFLAGS = -lm
TARGET = number-test.exe
SRC = number-test.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	reset && ./$(TARGET)

clean:
	rm -f $(TARGET)

