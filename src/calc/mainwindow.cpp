#include "mainwindow.h"

#include <string.h>

#include <QMessageBox>
#include <iostream>

#include "ui_mainwindow.h"

QString old_label;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // Инициализация окон
  CScale = new scale();
  connect(CScale, &scale::ScaleWindow, this, &MainWindow::show);
  CGraph = new graph();
  connect(CGraph, &graph::GraphWindowForScale, this, &scale::show);
  Credit = new CreditCalc();
  connect(Credit, &CreditCalc::CreditWindow, this, &MainWindow::show);
  Deposit = new DepositCalc();
  connect(Deposit, &DepositCalc::DepositWindow, this, &MainWindow::show);
  //Подключение сигналов
  connect(this, SIGNAL(SendData(QString)), CScale, SLOT(receiveData(QString)));
  connect(
      CScale, SIGNAL(SendDataForGraph(QString, double, double, double, double)),
      this, SLOT(receiveDataForGraph(QString, double, double, double, double)));
  connect(this,
          SIGNAL(SendDataFromMain(double, double, double, double, double *,
                                  double *)),
          CGraph,
          SLOT(receiveDataFromMain(double, double, double, double, double *,
                                   double *)));
  //Клавиатура
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_multiple, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(math_operations()));

  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(bracket()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(bracket()));
  //    connect(ui->pushButton_equal,SIGNAL(clicked()),this,SLOT(on_pushButton_equal_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text();

  if (ui->result_show->text().endsWith(")")) {
    new_label += "*";
    old_label = new_label;
    new_label += button->text();
  } else {
    int size_old = old_label.size();
    new_label.remove(0, size_old);

    if (!new_label.contains(".") && button->text() != "x") {
      double all_numbers;
      all_numbers = (new_label + button->text()).toDouble();
      new_label = QString::number(all_numbers, 'g', 15);
    } else if (!new_label.contains("x") && new_label.contains(".")) {
      new_label = new_label + button->text();
    } else {
      new_label = "x";
    }

    new_label.prepend(old_label);
  }

  ui->result_show->setText(new_label);
}
void MainWindow::receiveDataForGraph(QString new_label, double ymax,
                                     double ymin, double xmax, double xmin) {
  char *str = new char(new_label.length());
  QByteArray barr = new_label.toLatin1();
  strncpy(str, barr, new_label.length() + 1);
  double xBegin = xmin, xEnd = xmax, h = 0.1, X = xmin;
  int N = (xEnd - xBegin) / h + 1;
  double arrx[N];
  double arry[N];

  for (int i = 0; i <= N; i++) {
    arrx[i] = X;
    s21_smartcalc(str, &arry[i], X);
    //         fprintf(stderr, "x= %lf\n",arrx[i]);
    X += h;
  }
  SendDataFromMain(ymax, ymin, xmax, xmin, arrx, arry);
  CGraph->show();
}

void MainWindow::on_pushButton_dot_clicked() {
  QString new_label = ui->result_show->text();

  int size_old = old_label.size();
  new_label.remove(0, size_old);
  if (!new_label.contains('.')) {
    //        fprintf(stderr, "DEBUG new_label = [%c]", new_label[0]);
    new_label.prepend(old_label);
    ui->result_show->setText(new_label + ".");
  }
}

void MainWindow::bracket() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text();
  if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    int amount_left_bracket = new_label.count("(");
    int amount_right_bracket = new_label.count(")");
    if (amount_right_bracket < amount_left_bracket) {
      new_label += ")";
    }
  }
  ui->result_show->setText(new_label);
  old_label = new_label;
}

void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text();
  int length = new_label.size();

  QString numbers = "1234567890x";

  if (button->text() == "+" && !((ui->result_show->text().endsWith("+")) ||
                                 (ui->result_show->text().endsWith("-")) ||
                                 (ui->result_show->text().endsWith("*")) ||
                                 (ui->result_show->text().endsWith("/")) ||
                                 (ui->result_show->text().endsWith("mod")))) {
    if (ui->result_show->text().endsWith("^")) {
      new_label += "(+";
    } else {
      new_label += "+";
    }
  }
  if (button->text() == "-" && !((ui->result_show->text().endsWith("+")) ||
                                 (ui->result_show->text().endsWith("-")) ||
                                 (ui->result_show->text().endsWith("*")) ||
                                 (ui->result_show->text().endsWith("/")) ||
                                 (ui->result_show->text().endsWith("mod")))) {
    if (ui->result_show->text().endsWith("^")) {
      new_label += "(";
    } else {
      new_label += "-";
    }
  }
  if (button->text() == "*" && !((ui->result_show->text().endsWith("+")) ||
                                 (ui->result_show->text().endsWith("-")) ||
                                 (ui->result_show->text().endsWith("*")) ||
                                 (ui->result_show->text().endsWith("/")) ||
                                 (ui->result_show->text().endsWith("mod")) ||
                                 ui->result_show->text().endsWith("sin(") ||
                                 ui->result_show->text().endsWith("asin(") ||
                                 ui->result_show->text().endsWith("cos(") ||
                                 ui->result_show->text().endsWith("acos(") ||
                                 ui->result_show->text().endsWith("tan(") ||
                                 ui->result_show->text().endsWith("atan(") ||
                                 ui->result_show->text().endsWith("sqrt(") ||
                                 ui->result_show->text().endsWith("log(") ||
                                 ui->result_show->text().endsWith("ln(") ||
                                 ui->result_show->text().endsWith("^") ||
                                 ui->result_show->text().endsWith("("))) {
    new_label += "*";
  }
  if (button->text() == "/" && !((ui->result_show->text().endsWith("+")) ||
                                 (ui->result_show->text().endsWith("-")) ||
                                 (ui->result_show->text().endsWith("*")) ||
                                 (ui->result_show->text().endsWith("/")) ||
                                 (ui->result_show->text().endsWith("mod")) ||
                                 ui->result_show->text().endsWith("sin(") ||
                                 ui->result_show->text().endsWith("asin(") ||
                                 ui->result_show->text().endsWith("cos(") ||
                                 ui->result_show->text().endsWith("acos(") ||
                                 ui->result_show->text().endsWith("tan(") ||
                                 ui->result_show->text().endsWith("atan(") ||
                                 ui->result_show->text().endsWith("sqrt(") ||
                                 ui->result_show->text().endsWith("log(") ||
                                 ui->result_show->text().endsWith("ln(") ||
                                 ui->result_show->text().endsWith("^") ||
                                 ui->result_show->text().endsWith("("))) {
    new_label += "/";
  }
  if (button->text() == "mod" && !((ui->result_show->text().endsWith("+")) ||
                                   (ui->result_show->text().endsWith("-")) ||
                                   (ui->result_show->text().endsWith("*")) ||
                                   (ui->result_show->text().endsWith("/")) ||
                                   (ui->result_show->text().endsWith("mod")) ||
                                   ui->result_show->text().endsWith("sin(") ||
                                   ui->result_show->text().endsWith("asin(") ||
                                   ui->result_show->text().endsWith("cos(") ||
                                   ui->result_show->text().endsWith("acos(") ||
                                   ui->result_show->text().endsWith("tan(") ||
                                   ui->result_show->text().endsWith("atan(") ||
                                   ui->result_show->text().endsWith("sqrt(") ||
                                   ui->result_show->text().endsWith("log(") ||
                                   ui->result_show->text().endsWith("ln(") ||
                                   ui->result_show->text().endsWith("^") ||
                                   ui->result_show->text().endsWith("("))) {
    new_label += "mod";
  }
  if (button->text() == "cos" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "cos(";
  }
  if (button->text() == "acos" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "acos(";
  }
  if (button->text() == "sin" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "sin(";
  }
  if (button->text() == "asin" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "asin(";
  }
  if (button->text() == "tan" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "tan(";
  }
  if (button->text() == "atan" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "atan(";
  }
  if (button->text() == "sqrt" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "sqrt(";
  }
  if (button->text() == "ln" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "ln(";
  }
  if (button->text() == "log" &&
      (length == 0 || !numbers.contains(new_label[length - 1]))) {
    new_label += "log(";
  }
  if (button->text() == "^" && !((ui->result_show->text().endsWith("+")) ||
                                 (ui->result_show->text().endsWith("-")) ||
                                 (ui->result_show->text().endsWith("*")) ||
                                 (ui->result_show->text().endsWith("/")) ||
                                 (ui->result_show->text().endsWith("mod")) ||
                                 ui->result_show->text().endsWith("sin(") ||
                                 ui->result_show->text().endsWith("asin(") ||
                                 ui->result_show->text().endsWith("cos(") ||
                                 ui->result_show->text().endsWith("acos(") ||
                                 ui->result_show->text().endsWith("tan(") ||
                                 ui->result_show->text().endsWith("atan(") ||
                                 ui->result_show->text().endsWith("sqrt(") ||
                                 ui->result_show->text().endsWith("log(") ||
                                 ui->result_show->text().endsWith("ln(") ||
                                 ui->result_show->text().endsWith("^") ||
                                 ui->result_show->text().endsWith("("))) {
    new_label += "^";
  }
  ui->result_show->setText(new_label);
  old_label = ui->result_show->text();
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->result_show->setText(" ");
  old_label = " ";
}

void MainWindow::on_pushButton_equal_clicked() {
  QString new_label = ui->result_show->text();
  char *str = new char(ui->result_show->text().length());
  QByteArray barr = ui->result_show->text().toLatin1();
  strncpy(str, barr, ui->result_show->text().length() + 1);
  double result;
  int status = s21_smartcalc(str, &result, 1);
  if (status == OK) {
    if (new_label.count("x") > 0) {
      emit SendData(new_label);
      CScale->show();
      ui->result_show->setText(" ");
    } else {
      ui->result_show->setText(QString::number(result));
      old_label = ui->result_show->text();
    }
  } else {
    ui->result_show->setText("INCORRECT VALUE");
    old_label = " ";
  }
}

void MainWindow::on_result_show_linkActivated() {}

void MainWindow::on_pushButtonCreditCalc_clicked() {
  this->close();
  Credit->show();
}

void MainWindow::on_pushButton_clicked() {
  this->close();
  Deposit->show();
}
