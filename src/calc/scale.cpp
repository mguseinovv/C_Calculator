#include "scale.h"

#include "ui_scale.h"

scale::scale(QWidget *parent) : QDialog(parent), ui(new Ui::scale) {
  ui->setupUi(this);
}

scale::~scale() { delete ui; }

void scale::on_pushButton_clicked() {
  QString new_label = ui->fromMain->text();

  double ymax = 0, ymin = 0, xmax = 0, xmin = 0;
  ymax = ui->lineYmax->text().toDouble();
  ymin = ui->lineYmin->text().toDouble();
  xmax = ui->lineXmax->text().toDouble();
  xmin = ui->lineXmin->text().toDouble();
  emit SendDataForGraph(new_label, ymax, ymin, xmax, xmin);
  this->close();
}

void scale::on_pushButton_2_clicked() {
  this->close();
  emit ScaleWindow();
}
void scale::receiveData(QString new_label) { ui->fromMain->setText(new_label); }
