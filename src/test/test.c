#include <check.h>
#include <stdlib.h>

#include "../calc/back/credit_calc.h"
#include "../calc/back/deposit_calc.h"
#include "../calc/back/s21_smartcalc.h"

START_TEST(parse_test_1) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("3 - sin(  -3)", out);
  ck_assert_str_eq(out, "3 3 ~ s - ");
}
END_TEST

START_TEST(parse_test_2) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("1+1*(3+4 *2)", out);
  ck_assert_str_eq(out, "1 1 3 4 2 * + * + ");
}
END_TEST

START_TEST(parse_test_3) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("tan(  -log(   -3)) + 3 / 8 ", out);
  ck_assert_str_eq(out, "3 ~ g ~ t 3 8 / + ");
}
END_TEST

START_TEST(parse_test_4) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("3^2^4", out);
  ck_assert_str_eq(out, "3 2 ^ 4 ^ ");
}
END_TEST

START_TEST(parse_test_5) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("(3 + sin(3) - 8)", out);
  ck_assert_str_eq(out, "3 3 s + 8 - ");
}
END_TEST

START_TEST(parse_test_6) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("(x + sin(x) - 8)", out);
  ck_assert_str_eq(out, "x x s + 8 - ");
}
END_TEST

START_TEST(parse_test_7) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("ln(-1) + 1 * cos(sin(2))", out);
  ck_assert_str_eq(out, "1 ~ n 1 2 s c * + ");
}
END_TEST

START_TEST(parse_neg_1) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("(3 + sin(3) - 8", out);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(parse_neg_2) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("((((((", out);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(parse_neg_3) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("())", out);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(parse_neg_4) {
  int err = 0;
  char out[512] = {'\0'};
  err = translate_from_infix_to_polish("aboba", out);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(calc_test_1) {
  int err = 0;
  double out = 0;
  err = s21_smartcalc("sin(3)", &out, 0);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, sin(3), 1e-7);
  else
    ck_assert_double_nan(sin(3));
}
END_TEST

START_TEST(calc_test_2) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("2^3^4", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, pow(pow(2,3),4), 1e-7);
  else
    ck_assert_double_nan(pow(pow(2,3),4));
}
END_TEST

START_TEST(calc_test_3) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("1+1*(3+4 *2)", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, 1 + 1 * (3 + 4 * 2), 1e-7);
  else
    ck_assert_double_nan(1 + 1 * (3 + 4 * 2));
}
END_TEST

START_TEST(calc_test_4) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("tan(-log(-3)) + 3 / 8 ", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, tan(-log10(-3)) + 3 / 8, 1e-7);
  else
    ck_assert_double_nan(tan(-log10(-3)) + 3 / 8);
}
END_TEST

START_TEST(calc_test_5) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("56-3", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, 56 - 3, 1e-7);
  else
    ck_assert_double_nan(56 - 3);
}
END_TEST

START_TEST(calc_test_6) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("ln(x)", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 4);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, log(4), 1e-7);
  else
    ck_assert_double_nan(log(4));
}
END_TEST

START_TEST(calc_test_7) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("ln(x) - 4 mod x", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, -2.32);
  if (!isnan(out))
    ck_assert_double_eq_tol(out, log(-2.32) - fmod(4, -2.32), 1e-7);
  else
    ck_assert_double_nan(log(-2.32) - fmod(4, -2.32));
}
END_TEST

START_TEST(calc_neg_1) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("ln(-1", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(calc_neg_2) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("ln(-+-+/1)", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(calc_neg_3) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("3+ 2 -", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(calc_neg_4) {
  int err = 0;
  char a[512] = {'\0'};
  err = translate_from_infix_to_polish("3 +", a);
  double out = 0;
  err = (err == INCORRECT_INPUT) ? err : calculating(a, &out, 0);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(credit_test) {
  Result_calc a = credit_calc(10000, 12, 3, 0);
  Result_calc d = credit_calc(10000, 12, 3, 1);
  ck_assert_int_eq(a.all_payment, 10163);
  ck_assert_int_eq(a.overpayment, 163);
  ck_assert_int_eq(a.monthly_payment[0], 846);
  ck_assert_int_eq(d.monthly_payment[0], 858);
  ck_assert_int_eq(d.monthly_payment[1], 856);
  ck_assert_int_eq(d.overpayment, 162);
  ck_assert_int_eq(d.all_payment, 10162);
}
END_TEST

START_TEST(deposit_test) {
  Refill_calc ref = {0, 0};
  Withdrawal_calc wit = {0, 0};
  ref.period = 0;
  ref.refill = 0;
  wit.period = 0;
  wit.Withdrawal = 0;
  Deposit_res nr = deposit_calc(100000, 12, 15, 13, 3, 1, ref, wit);
  ck_assert_int_eq(nr.InterestCharges, 15865);
  ck_assert_int_eq(nr.TaxAmount, 0);
  ck_assert_int_eq(nr.DepositAmountResult, 115865);
  ref.period = 1;
  ref.refill = 100;
  wit.period = 0;
  wit.Withdrawal = 0;
  Deposit_res wa = deposit_calc(100000, 12, 15, 13, 6, 1, ref, wit);
  ck_assert_int_eq(wa.InterestCharges, 15700);
  ck_assert_int_eq(wa.TaxAmount, 0);
  ck_assert_int_eq(wa.DepositAmountResult, 116900);
  ref.period = 2;
  ref.refill = 100;
  wit.period = 0;
  wit.Withdrawal = 0;
  Deposit_res wa2 = deposit_calc(100000, 12, 15, 13, 12, 1, ref, wit);
  ck_assert_int_eq(wa2.InterestCharges, 15090.00);
  ck_assert_int_eq(wa2.TaxAmount, 0);
  ck_assert_int_eq(wa2.DepositAmountResult, 115690);
  ref.period = 0;
  ref.refill = 0;
  wit.period = 1;
  wit.Withdrawal = 300;
  Deposit_res wd = deposit_calc(100000, 12, 15, 13, 1, 1, ref, wit);
  ck_assert_int_eq(wd.InterestCharges, 15769);
  ck_assert_int_eq(wd.TaxAmount, 0);
  ck_assert_int_eq(wd.DepositAmountResult, 112169);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, parse_test_1);
  tcase_add_test(tc1_1, parse_test_2);
  tcase_add_test(tc1_1, parse_test_3);
  tcase_add_test(tc1_1, parse_test_4);
  tcase_add_test(tc1_1, parse_test_5);
  tcase_add_test(tc1_1, parse_test_6);
  tcase_add_test(tc1_1, parse_test_7);

  tcase_add_test(tc1_1, parse_neg_1);
  tcase_add_test(tc1_1, parse_neg_2);
  tcase_add_test(tc1_1, parse_neg_3);
  tcase_add_test(tc1_1, parse_neg_4);

  tcase_add_test(tc1_1, calc_test_1);
  tcase_add_test(tc1_1, calc_test_2);
  tcase_add_test(tc1_1, calc_test_3);
  tcase_add_test(tc1_1, calc_test_4);
  tcase_add_test(tc1_1, calc_test_5);
  tcase_add_test(tc1_1, calc_test_6);
  tcase_add_test(tc1_1, calc_test_7);

  tcase_add_test(tc1_1, calc_neg_1);
  tcase_add_test(tc1_1, calc_neg_2);
  tcase_add_test(tc1_1, calc_neg_3);
  tcase_add_test(tc1_1, calc_neg_4);

  tcase_add_test(tc1_1, credit_test);
  tcase_add_test(tc1_1, deposit_test);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
