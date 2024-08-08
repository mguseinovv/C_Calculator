#include "deposit_calc.h"

Deposit_res deposit_calc(double DepositAmount, int Term, double InterestRate,
                         double TaxRate, int PeriodPayments,
                         int InterestCapitalization, Refill_calc Refill,
                         Withdrawal_calc Withdrawal) {
  Deposit_res result = {0, 0, 0, 0};

  result.DepositAmountResult = DepositAmount;
  double PeriodSumm = 0;
  double buf = 0;
  for (int i = 0; i < Term; i++) {
    if (Refill.period != 0 && i % Refill.period == 0) {
      result.DepositAmountResult += Refill.refill;
    }
    if (Withdrawal.period != 0 && i % Withdrawal.period == 0) {
      result.DepositAmountResult -= Withdrawal.Withdrawal;
    }
    buf = (result.DepositAmountResult * InterestRate * PeriodPayments *
           DAYINMONTH) /
          (365 * 100);
    if ((i + 1) % PeriodPayments == 0) {
      result.InterestCharges += buf;
      PeriodSumm += buf;
      result.DepositAmountResult = (InterestCapitalization == 0)
                                       ? result.DepositAmountResult
                                       : result.DepositAmountResult + buf;
    }
    if ((i + 1) % 12 == 0 && i >= PeriodPayments) {
      if (PeriodSumm >= NOTAXABLEAMOUNT) {
        result.TaxAmount += (PeriodSumm - NOTAXABLEAMOUNT) * TaxRate / 100;
      }
      PeriodSumm = 0;
    }
  }
  buf = (result.DepositAmountResult * InterestRate * (Term % PeriodPayments) *
         DAYINMONTH) /
        (365 * 100);
  PeriodSumm += buf;
  result.InterestCharges += buf;
  if (PeriodSumm >= NOTAXABLEAMOUNT) {
    result.TaxAmount += (PeriodSumm - NOTAXABLEAMOUNT) * TaxRate / 100;
  }
  PeriodSumm = 0;
  return result;
}
