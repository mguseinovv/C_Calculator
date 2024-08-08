#ifndef SCALE_H
#define SCALE_H

#include <graph.h>

#include <QDialog>

namespace Ui {
class scale;
}

class scale : public QDialog {
  Q_OBJECT

public:
  explicit scale(QWidget *parent = nullptr);
  ~scale();
public slots:
  void receiveData(QString new_label);

signals:
  void ScaleWindow();
  void SendDataForGraph(QString new_label, double ymax, double ymin,
                        double xmax, double xmin);

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

private:
  Ui::scale *ui;
};

#endif // SCALE_H
