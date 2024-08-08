#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define NUMBER_FOUND 3
#define INCORRECT_INPUT 1

typedef struct Result_calc {
  double* monthly_payment;
  double overpayment;
  double all_payment;
  int status;
} Result_calc;

Result_calc credit_calc(double total_amount, int term, double interest_rate,
                        int type);

#endif  // CREDIT_CALC_H
