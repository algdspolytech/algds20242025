#include "../deps/criterion-2.4.2/include/criterion/criterion.h"
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h"
#include "../src/lint.h"
#include <stdio.h>

Test(lint_pow, 1, .description = "Положительное число: 34 ^ 8 = 1785793904896") {
  lint_t n1 = from_str("34");
  lint_t n2 = from_str("8");
  lint_t result = lint_pow(n1, n2);
  cr_assert(all(result.digits[0] == 96, result.digits[1] == 48,
                result.digits[2] == 90, result.digits[3] == 93,
                result.digits[4] == 57, result.digits[5] == 78,
                result.digits[6] == 1, result.size == 7,
                result.is_positive == true), );
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(lint_pow, 2, .description = "Большое число в резльтате: 49 ^ 150 = 33838570200749104093688312191360663049723538032163586311882583029937928817155484694868047033872426464394494995988271332913954603498574472214519578172866008667274238025742281231442261927858597726462360331182430633401319955052400299452568317841001584180001") {
  lint_t n1 = from_str("49");
  lint_t n2 = from_str("150");
  lint_t result = lint_pow(n1, n2);
  lint_t expected = from_str("33838570200749104093688312191360663049723538032163586311882583029937928817155484694868047033872426464394494995988271332913954603498574472214519578172866008667274238025742281231442261927858597726462360331182430633401319955052400299452568317841001584180001");
  cr_assert(equals(result, expected));
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(lint_pow, 3, .description = "Отрицательное число в четой степени: -34 ^ 12 = 2386420683693101056") {
  lint_t n1 = from_str("-34");
  lint_t n2 = from_str("12");
  lint_t result = lint_pow(n1, n2);
  lint_t expected = from_str("2386420683693101056");
  cr_assert(equals(result, expected));
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}

Test(lint_pow, 4, .description = "Отрицательное число в нечетой степени: -34 ^ 13 = -81138303245565435904") {
  lint_t n1 = from_str("-34");
  lint_t n2 = from_str("13");
  lint_t result = lint_pow(n1, n2);
  lint_t expected = from_str("-81138303245565435904");
  cr_assert(equals(result, expected));
  destroy_lint(&result);
  destroy_lint(&n1);
  destroy_lint(&n2);
}
