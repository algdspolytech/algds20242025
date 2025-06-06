COMPILER = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
SRC = treap.c
TREAP_EX = treap

TEST_EX = test
TEST = tests.c
TESTFLAGS = -lcheck

all: treap

treap: clean
	$(COMPILER)  $(SRC) -o $(TREAP_EX)

test: treap
	$(COMPILER) $(TESTFLAGS) $(TEST) -o $(TEST_EX)

clean:
	rm -rf $(TREAP_EX) $(TEST_EX)