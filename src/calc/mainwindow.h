#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <creditcalc.h>
#include <depositcalc.h>
#include <graph.h>
#include <scale.h>

#include <QMainWindow>

#ifdef __cplusplus
extern "C" {
#include "back/s21_smartcalc.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void receiveDataForGraph(QString new_label, double ymax, double ymin,
                           double xmax, double xmin);

signals:
  void SendData(QString new_label);
  void SendDataForGraph(QString new_label, double ymax, double ymin,
                        double xmax, double xmin);
  void SendDataFromMain(double ymax, double ymin, double xmax, double xmin,
                        double *arrx, double *arry);

private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  void math_operations();
  void bracket();
  void on_result_show_linkActivated();
  void on_pushButtonCreditCalc_clicked();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  graph *CGraph;
  scale *CScale;
  CreditCalc *Credit;
  DepositCalc *Deposit;
};
#endif // MAINWINDOW_H
