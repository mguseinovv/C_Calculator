#include "credit_calc.h"

Result_calc credit_calc(double total_amount, int term, double interest_rate,
                        int type) {
  Result_calc result = {NULL, 0, 0, OK};
  if (!(total_amount >= 0 && interest_rate >= 0.01 && term >= 0 &&
        (type == 0 || type == 1))) {
    result.status = INCORRECT_INPUT;
  } else if (type == 0) {
    result.monthly_payment = calloc(1, sizeof(double));
    result.monthly_payment[0] =
        total_amount * (interest_rate / (100 * 12)) /
        (1 - pow((1 + (interest_rate / (100 * 12))), -term));
    result.all_payment = result.monthly_payment[0] * term;
    result.overpayment = result.all_payment - total_amount;
  } else {
    result.monthly_payment = calloc(term, sizeof(double));
    double buf = total_amount;
    for (int i = 0; i < term; i++) {
      result.monthly_payment[i] =
          total_amount / 12 + (buf * interest_rate) / 1200;
      result.all_payment += result.monthly_payment[i];
      buf -= total_amount / term;
    }
    result.overpayment = result.all_payment - total_amount;
  }
  return result;
}
