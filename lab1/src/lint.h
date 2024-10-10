#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#define BASE 100

typedef struct {
  int size;
  uint8_t *digits;
  bool is_positive;
} lint_t;

lint_t from_str(const char str[]);
void destroy_lint(lint_t *n);
lint_t add(lint_t n1, lint_t n2);
bool equals(lint_t n1, lint_t n2);
lint_t multiply(lint_t n1, lint_t n2);
lint_t lint_pow(lint_t n1, lint_t n2);
lint_t copy(lint_t n);
void lint_print(lint_t n);
bool is_zero(lint_t n);
