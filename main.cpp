#include "mainwindow.h"
#include <QApplication>

#include "T_Golf_engine.h"#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

T_Golf_engine Golf_engine_global;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    (void) RUN_ALL_TESTS();

    return a.exec();
}
