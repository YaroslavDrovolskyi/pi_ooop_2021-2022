#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.resize(1000, 500);
//    w.setWindowTitle("Lab_2");
    w.show();
    return a.exec();
}
