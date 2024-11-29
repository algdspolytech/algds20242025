#include "../deps/criterion-2.4.2/include/criterion/criterion.h"
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h"
#include "../src/lint.h"
#include <stdio.h>

Test(multiply, 1,
     .description = "Положительное с положительным: 34 * 19 = 646") {
  lint_t n1 = from_str("34");
  lint_t n2 = from_str("19");
  lint_t result = multiply(n1, n2);
  cr_assert(all(result.digits[0] == 46, result.digits[1] == 6, result.size == 2,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(multiply, 2,
     .description = "Положительное с отрицательным: 34 * (-999) = -33966") {
  lint_t n1 = from_str("34");
  lint_t n2 = from_str("-999");
  lint_t result = multiply(n1, n2);
  cr_assert(all(result.digits[0] == 66, result.digits[1] == 39,
                result.digits[2] = 03, result.size == 3,
                result.is_positive == false), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(multiply, 3,
     .description = "Отрицательное с отрицательным: -133 * (-199) = 26467") {
  lint_t n1 = from_str("-133");
  lint_t n2 = from_str("-199");
  lint_t result = multiply(n1, n2);
  cr_assert(all(result.digits[0] == 67, result.digits[1] == 64,
                result.digits[2] == 02, result.size == 3,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(multiply, 4, .description = "Умножение на 0: 133 * 0 = 0") {
  lint_t n1 = from_str("133");
  lint_t n2 = from_str("0");
  lint_t result = multiply(n1, n2);
  cr_assert(all(result.digits[0] == 0, result.size == 1,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(multiply, 5,
     .description = "Умножение больших чисел: 678933 * 598199 = 406137041667") {
  lint_t n1 = from_str("678933");
  lint_t n2 = from_str("598199");
  lint_t result = multiply(n1, n2);
  cr_assert(all(result.digits[0] == 67, result.digits[1] == 16,
                result.digits[2] == 04, result.digits[3] == 37,
                result.digits[4] == 61, result.digits[5] == 40,
                result.size == 6, result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}
