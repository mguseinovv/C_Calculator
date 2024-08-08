#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QDialog>

#ifdef __cplusplus
extern "C" {
#include "back/deposit_calc.h"
}
#endif

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QDialog {
  Q_OBJECT
signals:
  void DepositWindow();

public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

private:
  Ui::DepositCalc *ui;
};

#endif // DEPOSITCALC_H
