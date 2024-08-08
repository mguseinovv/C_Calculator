#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>
//#ifdef __cplusplus
// extern "C" {
//#include "back/s21_smartcalc.h"
//}
//#endif
namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

public slots:
  void receiveDataFromMain(double ymax, double ymin, double xmax, double xmin,
                           double *arrx, double *arry);

signals:
  void GraphWindowForScale();

private slots:
  //функция записи переданных параметров графика
  //    void CalculatingGraph(QString new_label, double ymax, double ymin,
  //    double xmax, double xmin);
  //кнопк
  void on_pushButton_clicked();

private:
  Ui::graph *ui;
};

#endif // GRAPH_H
