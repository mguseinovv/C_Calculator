#include "creditannuity.h"

#include "ui_creditannuity.h"

CreditAnnuity::CreditAnnuity(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditAnnuity) {
  ui->setupUi(this);
}

CreditAnnuity::~CreditAnnuity() { delete ui; }

void CreditAnnuity::receiveDataForAnnuity(double monthly_payment,
                                          double overpayment,
                                          double all_payment) {
  QString monthlyPayment, allPayment, overPayment;
  monthlyPayment = QString::number(monthly_payment, 'd', 2);
  allPayment = QString::number(all_payment, 'd', 2);
  overPayment = QString::number(overpayment, 'd', 2);
  ui->label_Overpayment->setText(overPayment);
  ui->label_MonthlyPayment->setText(monthlyPayment);
  ui->label_AllPayment->setText(allPayment);
}
