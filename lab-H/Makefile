# Компилятор и флаги
CC     := gcc
CFLAGS := -std=c11 -Wall -Wextra -O2

# Ваш единственный исходник
SRC      := skew_heap_full.c

# Итоговые исполняемые
OUT      := outDebug
TEST_EXE := test_runner

# Объявляем «фантомные» цели
.PHONY: all test run clean

# По умолчанию собираем приложение и тесты
all: $(OUT) $(TEST_EXE)

# Сборка основного приложения
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# Сборка тестового раннера (тот же SRC, но с -DTEST)
$(TEST_EXE): $(SRC)
	$(CC) $(CFLAGS) -DTEST $< -o $@

# Запуск тестов
test: $(TEST_EXE)
	./$(TEST_EXE)

# Быстрый запуск программы с input.txt → output.txt
run: $(OUT)
	./$(OUT) input.txt output.txt

# Очистка артефактов
clean:
	rm -f $(OUT) $(TEST_EXE) *.o
