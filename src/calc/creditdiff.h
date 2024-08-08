#ifndef CREDITDIFF_H
#define CREDITDIFF_H

#include <QDialog>

namespace Ui {
class CreditDiff;
}

class CreditDiff : public QDialog {
  Q_OBJECT

signals:
  void DiffWindow();
public slots:
  void receiveDataForDiff(double *monthly_payment, double overpayment,
                          double all_payment, int term);

public:
  explicit CreditDiff(QWidget *parent = nullptr);
  ~CreditDiff();

private:
  Ui::CreditDiff *ui;
};

#endif // CREDITDIFF_H
