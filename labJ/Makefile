CC = gcc
CHECK_LIBS = $(shell pkg-config --cflags --libs check)

SRC = HashTable.c
TEST_SRC = test.c
TEST_EXE = test_hashtable

all: $(TEST_EXE)

$(TEST_EXE): $(SRC) $(TEST_SRC)
	$(CC) $(SRC) $(TEST_SRC) -o $@ $(CHECK_LIBS)
	./$(TEST_EXE)

test: $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f $(TEST_EXE)

.PHONY: all test clean