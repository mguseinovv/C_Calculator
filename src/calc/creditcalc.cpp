#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  Annuity = new CreditAnnuity();
  connect(Annuity, &CreditAnnuity::AnnuityWindow, this, &CreditCalc::show);
  Diff = new CreditDiff();
  connect(Diff, &CreditDiff::DiffWindow, this, &CreditCalc::show);
  connect(this, SIGNAL(SendDataForAnnuity(double, double, double)), Annuity,
          SLOT(receiveDataForAnnuity(double, double, double)));
  connect(this, SIGNAL(SendDataForDiff(double *, double, double, int)), Diff,
          SLOT(receiveDataForDiff(double *, double, double, int)));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_Result_clicked() {
  double totalAmount = 0, interestRate = 0;
  int type = 0, term = 0;
  totalAmount = ui->lineTotalAmount->text().toDouble();
  interestRate = ui->lineInterestRate->text().toDouble();
  term = ui->lineTerm->text().toInt();
  if (ui->comboBox_2->currentIndex() == 0) {
    term *= 12;
  }
  if (ui->comboBoxType->currentIndex() == 0) {
    type = 0;
    Result_calc result = {NULL, 0, 0, OK};
    result = credit_calc(totalAmount, term, interestRate, type);
    if (result.status == OK) {
      emit SendDataForAnnuity(result.monthly_payment[0], result.overpayment,
                              result.all_payment);
      Annuity->show();
    }

    free(result.monthly_payment);
  } else {
    type = 1;
    Result_calc result = {NULL, 0, 0, OK};
    result = credit_calc(totalAmount, term, interestRate, type);
    if (result.status == OK) {
      emit SendDataForDiff(result.monthly_payment, result.overpayment,
                           result.all_payment, term);
      Diff->show();
    }

    free(result.monthly_payment);
  }
  //    Result_calc result = {NULL,0,0,OK};
  //    result = credit_calc(totalAmount, term, interestRate, type);
  //    QString monthlyPayment, allPayment, overPayment;
  //    monthlyPayment = QString:: number(result.monthly_payment[0], 'd',2);
  //    allPayment = QString:: number(result.all_payment, 'd',2);
  //    overPayment = QString:: number(result.overpayment, 'd',2);
  //    ui->label_Overpayment->setText(overPayment);
  //    ui->label_MonthlyPayment->setText(monthlyPayment);
  //    ui->label_AllPayment->setText(allPayment);
  //    free(result.monthly_payment);
}

void CreditCalc::on_pushButton_Quit_clicked() {
  emit CreditWindow();
  this->close();
}
