#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <creditannuity.h>
#include <creditdiff.h>

#include <QDialog>

#ifdef __cplusplus
extern "C" {
#include "back/credit_calc.h"
}
#endif

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

signals:
  void CreditWindow();

public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

signals:
  void SendDataForDiff(double *, double, double, int);
  void SendDataForAnnuity(double, double, double);

private slots:
  void on_pushButton_Result_clicked();
  void on_pushButton_Quit_clicked();

private:
  Ui::CreditCalc *ui;
  CreditAnnuity *Annuity;
  CreditDiff *Diff;
};

#endif // CREDITCALC_H
