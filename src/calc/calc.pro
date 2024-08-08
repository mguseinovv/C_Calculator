QT += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4)
    : QT += widgets

          CONFIG += c++ 17

#You can make your code fail to compile if it uses deprecated APIs.
#In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE =                                     \
    0x060000 #disables all the APIs deprecated before Qt 6.0.0

      SOURCES += back / calculation.c back / credit_calc.c back /
                 deposit_calc.c back / dijkstra_algorithm.c back /
                 functions_for_calc_stack.c back / functions_for_stack.c back /
                 s21_smartcalc.c creditannuity.cpp creditcalc.cpp creditdiff
                     .cpp depositcalc.cpp graph.cpp main.cpp mainwindow
                     .cpp qcustomplot.cpp scale.cpp

                         HEADERS +=
      back / credit_calc.h back / deposit_calc.h back /
      s21_smartcalc.h creditannuity.h creditcalc.h creditdiff.h depositcalc
          .h graph.h mainwindow.h qcustomplot.h scale.h

              FORMS += creditannuity.ui creditcalc.ui creditdiff.ui depositcalc
                           .ui graph.ui mainwindow.ui scale.ui

                               TRANSLATIONS += calc_ru_RU.ts CONFIG +=
      lrelease CONFIG += embed_translations

#Default rules for deployment.
                             qnx : target.path =
          / tmp / $${TARGET} / bin else : unix : !android : target.path =
              / opt / $${TARGET} /
              bin !isEmpty(target.path) : INSTALLS += target
