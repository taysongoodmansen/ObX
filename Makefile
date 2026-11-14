CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

SRC = $(wildcard src/*.c)
TARGET = obx

.PHONY: all build test clean

all: build

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

test: build
	./$(TARGET) tests/test.obx

clean:
	rm -f $(TARGET)