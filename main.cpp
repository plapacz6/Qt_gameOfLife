#include "mainwindow.h"
#include <QApplication>

#include "T_Golf_engine.h"
#include "T_GolfPreviewCfg.h"
#include "T_GolfPatternStorehouse.h"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

T_Golf_engine Golf_engine_global;
T_GolfPreviewCfg GolfPrevieCfg_global(Golf_engine_global);
T_GolfPatternStorehouse GolfStoreHouse_pattern_global;

// #define TESTING_NOW

int main(int argc, char *argv[])
{

#ifdef TESTING_NOW
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    GolfPrevieCfg_global.height(50);
    GolfPrevieCfg_global.center_row();
    GolfPrevieCfg_global.width(50);
    GolfPrevieCfg_global.center_col();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif //TESTING_NOW
}
#undef TESTING_NOW
