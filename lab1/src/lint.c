#include "lint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lint_t from_str(const char str[]) {
  lint_t res;
  uint8_t *digits, *buff;
  int size, j, idx, buff_size;
  buff_size = 2;
  buff = calloc(buff_size, 1);
  size = 0;
  idx = 1;
  digits = NULL;
  if (strlen(str) == 0) {
    res.digits = digits;
    res.size = size;
    res.is_positive = true;
    return res;
  }
  if (str[0] == '-') {
    res.is_positive = false;
    j = 1;
  } else {
    res.is_positive = true;
    j = 0;
  }
  for (int i = strlen(str) - 1; i >= j; i--) {
    if (str[i] >= '0' && str[i] <= '9') {
      buff[idx--] = str[i];
      if (idx < 0) {
        idx = 1;
        digits = realloc(digits, (size + 1));
        digits[size++] = atoi(buff);
        memset(buff, 0, 2);
      }
    } else {
      fprintf(stderr,
              "Ошибка from_str(): строка содержит недопустимые символы\n");
      free(digits);
      res.digits = NULL;
      res.size = 0;
      res.is_positive = true;
      return res;
    }
  }
  if (idx != 1) {
    digits = realloc(digits, (size + 1));
    digits[size++] = atoi(buff + buff_size - 1 - idx);
  }
  res.digits = digits;
  res.size = size;
  return res;
}

void destroy_lint(lint_t *n) { free(n->digits); }

lint_t _add(lint_t n1, lint_t n2) {
  lint_t res;
  uint8_t *digits, a;
  res.size = n1.size;
  digits = calloc(res.size, 1);
  for (int i = 0; i < n1.size; i++) {
    if (i > n2.size) {
      a = 0;
    } else {
      a = n2.digits[i];
    }
    if (n1.is_positive != n2.is_positive) {
      if (n1.digits[i] < a) {
        for (int j = 1; i + j < n1.size; j++) {
          if (n1.digits[i + j] == 0) {
            n1.digits[i + j] = BASE - 1;
          } else {
            n1.digits[i + j]--;
            break;
          }
        }
        digits[i] += BASE - a + n1.digits[i];
      } else {
        digits[i] += n1.digits[i] - a;
      }
    } else {
      digits[i] += n1.digits[i] + a;
      if (digits[i] / BASE != 0) {
        if (res.size <= i + 1) {
          digits = realloc(digits, res.size + 1);
          digits[res.size++] += 1;
          digits[i] %= BASE;
        } else {
          digits[i + 1] += 1;
          digits[i] %= BASE;
        }
      }
    }
  }
  int actual_size = res.size;
  while (actual_size > 1 && digits[actual_size - 1] == 0) {
    actual_size--;
  }
  if (actual_size != res.size) {
    digits = realloc(digits, actual_size);
    if (!digits)
      return res;
    res.size = actual_size;
  }
  res.digits = digits;
  return res;
}

lint_t add(lint_t n1, lint_t n2) {
  lint_t res;
  if (n1.size > n2.size) {
    res = _add(n1, n2);
  } else if (n1.size < n2.size) {
    res = _add(n2, n1);
  } else {
    if (n1.digits[n1.size - 1] < n2.digits[n2.size - 1]) {
      res = _add(n2, n1);
    } else {
      res = _add(n1, n2);
    }
  }
  return res;
}

lint_t _multiply(lint_t n1, lint_t n2) {
  lint_t res;
  uint16_t a, b, tmp;
  uint8_t *digits;
  res.size = n1.size + n2.size;
  digits = calloc(res.size, sizeof(uint8_t));
  for (int i = 0; i < n1.size; i++) {
    a = 0;
    for (int j = 0; j < n2.size; j++) {
      b = n1.digits[i] * n2.digits[j];
      tmp = digits[i + j] + b + a;
      digits[i + j] = tmp % 100;
      a = tmp / 100;
    }
    digits[i + n2.size] += a;
  }
  while (res.size > 1 && digits[res.size - 1] == 0) {
    res.size--;
  }
  digits = realloc(digits, res.size);
  res.is_positive = (n1.is_positive == n2.is_positive);
  res.digits = digits;
  return res;
}

lint_t multiply(lint_t n1, lint_t n2) {
  lint_t res;
  if (n1.size > n2.size) {
    res = _multiply(n1, n2);
  } else if (n1.size < n2.size) {
    res = _multiply(n2, n1);
  } else {
    if (n1.digits[n1.size - 1] < n2.digits[n2.size - 1]) {
      res = _multiply(n2, n1);
    } else {
      res = _multiply(n1, n2);
    }
  }
  return res;
}

lint_t divide_by_two(lint_t n) {
  lint_t res;
  uint16_t current, tmp;
  res.size = n.size;
  res.digits = malloc(res.size);
  for (int i = n.size - 1; i >= 0; i--) {
    current = tmp * 100 + n.digits[i];
    res.digits[i] = current / 2;
    tmp = current % 2;
  }
  while (res.size > 1 && res.digits[res.size - 1] == 0) {
    res.size--;
  }
  return res;
}

lint_t lint_pow(lint_t n1, lint_t n2) {
  lint_t res, base;
  if (is_zero(n2)) {
    return from_str("1");
  }
  res = from_str("1");
  bool sign = (n2.digits[0] % 2 == 0);
  base = copy(n1);
  while (!is_zero(n2)) {
    if (n2.digits[0] % 2 == 1) {
      lint_t tmp = multiply(res, base);
      destroy_lint(&res);
      res = copy(tmp);
      destroy_lint(&tmp);
    }
    n2 = divide_by_two(n2);
    lint_t tmp = multiply(base, base);
    destroy_lint(&base);
    base = copy(tmp);
    destroy_lint(&tmp);
  }
  destroy_lint(&base);
  res.is_positive = sign;
  return res;
}

lint_t copy(lint_t n) {
  lint_t res;
  uint8_t *digits;
  digits = malloc(n.size);
  memcpy(digits, n.digits, n.size);
  res.digits = digits;
  res.size = n.size;
  res.is_positive = n.is_positive;
  return res;
}

bool equals(lint_t n1, lint_t n2) {
  if (n1.digits == NULL && n2.digits == NULL) {
    return true;
  }
  if (n1.size == n2.size) {
    return memcmp(n1.digits, n2.digits, n1.size) == 0;
  } else {
    return false;
  }
}

bool is_zero(lint_t n) {
  if (n.size == 1 && n.digits[0] == 0 && n.is_positive) {
    return true;
  } else {
    return false;
  }
}

void lint_print(lint_t n) {
  for (int i = 0; i < n.size; i++) {
    printf("%2d ", n.digits[i]);
  }
  putchar('\n');
}
