#include "mainwindow.h"
#include "pausewidget.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    pausewidget *pw = new pausewidget();
    w.show();
    pw->setAbsence(w.getAbsCash(), w.getAbsTime());
    pw->show();

    return a.exec();
}
