#include "../deps/criterion-2.4.2/include/criterion/criterion.h"
#include "../deps/criterion-2.4.2/include/criterion/new/assert.h"
#include "../src/lint.h"

Test(from_str, 1, .description = "Положительное число: str = \"13459678\"") {
  lint_t got = from_str("3459678");
  cr_assert(all(got.digits[0] == 78, got.digits[1] == 96, got.digits[2] == 45,
                got.digits[3] == 3, got.size == 4, got.is_positive == true), );
  destroy_lint(&got);
}

Test(from_str, 2,
     .description = "Отрицательное число: str = \"-41234134578\"") {
  lint_t got = from_str("-41234134578");
  cr_assert(all(got.digits[0] == 78, got.digits[1] == 45, got.digits[2] == 13,
                got.digits[3] == 34, got.digits[4] == 12, got.digits[5] == 4,
                got.size == 6, got.is_positive == false), );
  destroy_lint(&got);
}

Test(from_str, 3, .description = "Пустая строка: str = \"\"") {
  lint_t got = from_str("");
  cr_assert(all(got.digits == NULL, got.size == 0, got.is_positive == true), );
  destroy_lint(&got);
}

Test(from_str, 4, .description = "Запрещенные символы: str = \"%78test\"") {
  lint_t got = from_str("%78test");
  cr_assert(all(got.digits == NULL, got.size == 0, got.is_positive == true), );
  destroy_lint(&got);
}

Test(from_str, 5, .description = "Число с \"полным\" buff: str = \"4567\"") {
  lint_t got = from_str("4567");
  cr_assert(all(got.digits[0] == 67, got.digits[1] == 45, got.size == 2,
                got.is_positive == true), );
  destroy_lint(&got);
}

Test(from_str, 6, .description = "Число с \"неполным\" buff: str = \"567\"") {
  lint_t got = from_str("567");
  cr_assert(all(got.digits[0] == 67, got.digits[1] == 5, got.size == 2,
                got.is_positive == true), );
  destroy_lint(&got);
}
