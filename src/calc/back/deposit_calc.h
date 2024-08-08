#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define INCORRECT_INPUT 1
#define DAYINMONTH 365 / 12
#define NOTAXABLEAMOUNT 1000000 * 0.12
typedef struct Deposit_res {
  int status;
  double InterestCharges;
  double TaxAmount;
  double DepositAmountResult;
} Deposit_res;

typedef struct Refill_calc {
  int period;
  double refill;
} Refill_calc;

typedef struct Withdrawal_calc {
  int period;
  double Withdrawal;
} Withdrawal_calc;

Deposit_res deposit_calc(double DepositAmount, int Term, double InterestRate,
                         double TaxRate, int PeriodPayments,
                         int InterestCapitalization, Refill_calc Refill,
                         Withdrawal_calc Withdrawal);

#endif  // DEPOSIT_CALC_H
