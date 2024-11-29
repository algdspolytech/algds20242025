#include "../deps/criterion-2.4.2/include/criterion/criterion.h"
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h"
#include "../src/lint.h"

Test(add, 1,
     .description =
         "Положительное с положительным: 3459479 + 1999301 = 5458780") {
  lint_t n1 = from_str("3459479");
  lint_t n2 = from_str("1999301");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 80, result.digits[1] == 87,
                result.digits[2] == 45, result.digits[3] == 5, result.size == 4,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(add, 2,
     .description =
         "Положительное с отрицательным: 3459479 + (-3314199) = 145280") {
  lint_t n1 = from_str("3459479");
  lint_t n2 = from_str("-3314199");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 80, result.digits[1] == 52,
                result.digits[2] == 14, result.size == 3,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(add, 3,
     .description =
         "Отрицательное с отрицательным: -3459479 + (-1999301) = -5458780") {
  lint_t n1 = from_str("-3459479");
  lint_t n2 = from_str("-1999301");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 80, result.digits[1] == 87,
                result.digits[2] == 45, result.digits[3] == 5, result.size == 4,
                result.is_positive == false), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(add, 4, .description = "Большая разница в размере: 999999 + 1 = 1000000") {
  lint_t n1 = from_str("999999");
  lint_t n2 = from_str("1");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 00, result.digits[1] == 00,
                result.digits[2] == 00, result.digits[3] == 01,
                result.size == 4, result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(add, 5, .description = "Cложение с 0: 999999 + 0 = 999999") {
  lint_t n1 = from_str("999999");
  lint_t n2 = from_str("0");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 99, result.digits[1] == 99,
                result.digits[2] == 99, result.size == 3,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(add, 6, .description = "Сокращение размера числа: 10000 + (-99900) = 100") {
  lint_t n1 = from_str("10000");
  lint_t n2 = from_str("-9900");
  lint_t result = add(n1, n2);
  cr_assert(all(result.digits[0] == 00, result.digits[1] == 01,
                result.size == 2,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}
