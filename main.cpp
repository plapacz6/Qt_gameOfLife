#include "mainwindow.h"
#include <QApplication>
#include "T_Golf_engine.h"

T_Golf_engine Golf_engine_global;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
