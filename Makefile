# Makefile для splay tree

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
SRC = splay_tree_full.c
OUT = outDebug
TEST_EXE = test_runner

.PHONY: all test run clean

all: $(OUT) $(TEST_EXE)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

$(TEST_EXE): $(SRC)
	$(CC) $(CFLAGS) -DTEST $< -o $@

test: $(TEST_EXE)
	./$(TEST_EXE)

run: $(OUT)
	./$(OUT) input.txt output.txt

clean:
	rm -f $(OUT) $(TEST_EXE) *.o
