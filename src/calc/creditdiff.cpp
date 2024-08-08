#include "creditdiff.h"

#include "ui_creditdiff.h"

CreditDiff::CreditDiff(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditDiff) {
  ui->setupUi(this);
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget->setColumnCount(2); // Указываем число колонок
  ui->tableWidget->setShowGrid(true); // Включаем сетку
  // Разрешаем выделение только одного элемента
  ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  // Разрешаем выделение построчно
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  // Растягиваем последнюю колонку на всё доступное пространство
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

CreditDiff::~CreditDiff() { delete ui; }

void CreditDiff::receiveDataForDiff(double *monthly_payment, double overpayment,
                                    double all_payment, int term) {
  for (int i = 0; i < term; i++) {
    ui->tableWidget->insertRow(i);
    QString month, pay;
    month = QString::number(i + 1);
    pay = QString::number(monthly_payment[i], 'd', 2);
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(month));
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(pay));
  }
  QString allPayment, overPayment;
  allPayment = QString::number(all_payment, 'd', 2);
  overPayment = QString::number(overpayment, 'd', 2);
  ui->label_Overpayment->setText(overPayment);
  ui->label_AllPayment->setText(allPayment);
}
