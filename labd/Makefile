CC ?= gcc

CFLAGS = -Wall -Wextra
TARGET = build/main.out

.PHONY: run tests mem_check debug

debug:
	$(CC) $(CFLAGS) src/*.c -lm -g -o build/debug/main.out
	build/debug/main.out

run:
	$(CC) $(CFLAGS) src/*.c -lm -o build/main.out
	build/main.out

mem_check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose build/main.out
	
