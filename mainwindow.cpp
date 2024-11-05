#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
// #include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int box_size = ui->tableView->height()/board.rowCount();
    qDebug() << QString("box_size: %1, table->height(): %2, board.rowCount(): %3")
                .arg(box_size)
                .arg(ui->tableView->height())
                .arg(board.rowCount());

    ui->tableView->setModel(&board);

    ui->tableView->rowHeight(box_size);
    ui->tableView->columnWidth(box_size);

//    ui->tableView->setFixedHeight(box_size * 10); //dotyczy calej tabeli
//    ui->tableView->setFixedWidth(box_size * 10);

    ui->tableView->show();
    qDebug() << QString("box_size: %1, table->height(): %2, board.rowCount(): %3")
                .arg(box_size)
                .arg(ui->tableView->height())
                .arg(board.rowCount());

    QTableView listRule;
    listRule.setModel(&rule_list);
    listRule.rowHeight(30);
    listRule.columnWidth(50);
    listRule.show();

    qDebug() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

    qDebug() << "connecting: timeout() -> board.slot_Calculate() :";
    qDebug() << connect(&data_calculate_timer,
                        SIGNAL(timeout()),
                        &board,
                        SLOT(slot_GolfCalculate()));

    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardClear(): ";
    qDebug() << connect(ui->pushButton_clear,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardClear())
                        );

    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardClear(): ";
    qDebug() << connect(ui->pushButton_initial,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardInitial())
                        );
    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardClear(): ";
    qDebug() << connect(ui->pushButton_setPattern,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardSetPattern())
                        );
    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardClear(): ";
    qDebug() << connect(ui->pushButton_set_pattern_glider,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardSetPattern_glider())
                        );

    //PROBLEM Z PODLACZANIEM SYGNALU Z PARAMETREM
    // qDebug() << "connecting : board.signal_GolfBoardCalculated(board.Golf_data) -> board.signal_GolfBoardCalculated(board.Golf_data):";
    // qDebug() << connect(&board,
    //                     SIGNAL(signal_GolfBoardCalculated(board.Golf_data)),
    //                     &board,
    //                     SLOT(slot_GolfBoardStateUpdate(board.Golf_data))
    //                     );
    qDebug() << "connecting : board.signal_GolfBoardCalculated() -> board.signal_GolfBoardCalculated():";
    qDebug() << connect(&board,
                        SIGNAL(signal_GolfBoardCalculated()),
                        &board,
                        SLOT(slot_GolfBoardStateUpdate())
                        );
    // qDebug() << "connecting : board.signal_GolfBoardSetPattern() -> board.slot_GolfBoardSetPattern():";
    // qDebug() << connect(&board,
    //                     SIGNAL(signal_GolfBoardSetPattern()),
    //                     &board,
    //                     SLOT(slot_GolfBoardSetPattern())
    //                     );



    data_calculate_timer.setInterval(100);
    data_calculate_timer.setSingleShot(false);
    data_calculate_timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//SYGNAŁY SĄ
//GENEROWANE SA PRZEZ MOC  w moc_mainwindow.cpp
