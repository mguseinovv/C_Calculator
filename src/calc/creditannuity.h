#ifndef CREDITANNUITY_H
#define CREDITANNUITY_H

#include <QDialog>

namespace Ui {
class CreditAnnuity;
}

class CreditAnnuity : public QDialog {
  Q_OBJECT

signals:
  void AnnuityWindow();

public slots:
  void receiveDataForAnnuity(double monthly_payment, double overpayment,
                             double all_payment);

public:
  explicit CreditAnnuity(QWidget *parent = nullptr);
  ~CreditAnnuity();

private:
  Ui::CreditAnnuity *ui;
};

#endif // CREDITANNUITY_H
