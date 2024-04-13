#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator tra;
    tra.load("ru_RU",".");
    qApp->installTranslator(&tra);

    MainWindow w;
    w.show();
    return a.exec();
}
