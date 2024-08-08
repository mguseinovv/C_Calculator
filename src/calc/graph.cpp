#include "graph.h"

#include "ui_graph.h"

graph::graph(QWidget *parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);
}

graph::~graph() { delete ui; }

void graph::on_pushButton_clicked() {
  this->close();
  emit GraphWindowForScale();
}
void graph::receiveDataFromMain(double ymax, double ymin, double xmax,
                                double xmin, double *arrx, double *arry) {
  QVector<double> x, y;
  ui->widget->xAxis->setRange(xmin, xmax);
  ui->widget->yAxis->setRange(ymin, ymax);
  int N = (xmax - xmin) / 0.1 + 1;
  for (int i = 0; i <= N; i++) {
    y.push_back(arry[i]);
    x.push_back(arrx[i]);
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->replot();
}

// void graph::CalculatingGraph(QString new_label, double ymax, double ymin,
// double xmax, double xmin)
//{

//}
