CC ?= clang

CFLAGS = -Wall -Wextra
# Путь к библиотеке для тестирования criterion
CI = deps/criterion-2.4.2/include/criterion
# Путь к исполняемым файлам criterion
CL = deps/criterion-2.4.2/lib
TARGET = build/main.out

.PHONY: run tests mem_check

tests:
	$(CC) $(CFLAGS) -I$(CI) test/*.c src/lint.c -o build/tests.out -L$(CL) -lcriterion -Wl,-R$(CL)
	build/tests.out --verbose
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes build/tests.out

run:
	$(CC) $(CFLAGS) -I$(CI) test/*.c src/lint.c -o build/tests.out -L$(CL) -lcriterion -Wl,-R$(CL)
	build/tests.out
	$(CC) $(CFLAGS) src/main.c src/lint.c -o build/main.out
	build/main.out

mem_check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose build/main.out
	
