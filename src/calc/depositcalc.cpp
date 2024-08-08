#include "depositcalc.h"

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_pushButton_clicked() {
  emit DepositWindow();
  this->close();
}

void DepositCalc::on_pushButton_2_clicked() {
  double DepositAmount = 0, InterestRate = 0, TaxRate = 0;
  int Term = 0, PeriodPayments = 0, Capital = 0;
  Refill_calc StRefill = {0, 0};
  Withdrawal_calc StWithdrawal = {0, 0};
  DepositAmount = ui->lineDepositAmount->text().toDouble();
  InterestRate = ui->lineInterestRate->text().toInt();
  TaxRate = ui->lineTaxRate->text().toDouble();
  StWithdrawal.Withdrawal = ui->lineWithdrawal->text().toDouble();
  Term = ui->lineTerm->text().toInt();
  StRefill.refill = ui->lineRefill->text().toDouble();
  if (ui->checkBoxCapital->isChecked() == 1) {
    Capital = 1;
  }
  if (ui->comboBox_3->currentIndex() == 0) {
    Term *= 12;
  }
  if (ui->comboBoxPeriodPay->currentIndex() == 0) {
    PeriodPayments = Term;
  } else if (ui->comboBoxPeriodPay->currentIndex() == 1) {
    PeriodPayments = 12;
  } else if (ui->comboBoxPeriodPay->currentIndex() == 2) {
    PeriodPayments = 6;
  } else if (ui->comboBoxPeriodPay->currentIndex() == 3) {
    PeriodPayments = 3;
  } else if (ui->comboBoxPeriodPay->currentIndex() == 4) {
    PeriodPayments = 1;
  }
  if (ui->comboBoxWithdrawal->currentIndex() == 0) {
    StWithdrawal.period = 0;
    StWithdrawal.Withdrawal = 0;
  } else if (ui->comboBoxPeriodWithdrawal->currentIndex() == 0) {
    StWithdrawal.period = 12;
  } else if (ui->comboBoxPeriodWithdrawal->currentIndex() == 1) {
    StWithdrawal.period = 6;
  } else if (ui->comboBoxPeriodWithdrawal->currentIndex() == 2) {
    StWithdrawal.period = 3;
  } else if (ui->comboBoxPeriodWithdrawal->currentIndex() == 3) {
    StWithdrawal.period = 2;
  } else if (ui->comboBoxPeriodWithdrawal->currentIndex() == 4) {
    StWithdrawal.period = 1;
  }
  if (ui->comboBoxRefill->currentIndex() == 0) {
    StRefill.refill = 0;
    StRefill.period = 0;
  } else if (ui->comboBoxPeriodRefill->currentIndex() == 0) {
    StRefill.period = 12;
  } else if (ui->comboBoxPeriodRefill->currentIndex() == 1) {
    StRefill.period = 6;
  } else if (ui->comboBoxPeriodRefill->currentIndex() == 2) {
    StRefill.period = 3;
  } else if (ui->comboBoxPeriodRefill->currentIndex() == 3) {
    StRefill.period = 2;
  } else if (ui->comboBoxPeriodRefill->currentIndex() == 4) {
    StRefill.period = 1;
  }
  Deposit_res result =
      deposit_calc(DepositAmount, Term, InterestRate, TaxRate, PeriodPayments,
                   Capital, StRefill, StWithdrawal);
  QString DepositAmountResult, TaxAmount, InterestCharges;
  DepositAmountResult = QString::number(result.DepositAmountResult, 'd', 2);
  TaxAmount = QString::number(result.TaxAmount, 'd', 2);
  InterestCharges = QString::number(result.InterestCharges, 'd', 2);
  ui->lineDepositAmountResult->setText(DepositAmountResult);
  ui->lineTaxAmount->setText(TaxAmount);
  ui->lineInterestCharges->setText(InterestCharges);
}
