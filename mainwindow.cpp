#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
// #include <QDateTime>


extern T_Golf_engine Golf_engine_global;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    Golf_engine(Golf_engine_global),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(&board);
    int windowWidth = 800;
    int windowHight = 600;
    double boxSize = windowHight / board.columnCount();

    // parent->setMaximumHeight()
    ui->centralWidget->setMinimumWidth(windowWidth);
    ui->centralWidget->setMinimumHeight((windowHight));

    /*
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layoutH_main;
    QVBoxLayout *layoutV_view;
    QTableView *tableView;
    QScrollBar *horizontalScrollBar;
    QVBoxLayout *layoutV_control_panel;
    QVBoxLayout *layoutV_control;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_StartStop;
    QGroupBox *groupBox_period;
    QSpinBox *spinBox;
    QScrollBar *horizontalScrollBar_2;
    QVBoxLayout *layoutV_set_pattern;
    QPushButton *pushButton_EditSwitch;
    QPushButton *pushButton_initial;
    QPushButton *pushButton_setPattern;
    QPushButton *pushButton_set_pattern_glider;
    QListView *listView_patterns;
    QPushButton *pushButton_choose;
    QVBoxLayout *layoutV_set_colors;
    QCheckBox *checkBox_Torus;
    QLineEdit *lineEdit_x_info;
    QLineEdit *lineEdit_y_info;
    QLineEdit *lineEdit_board_size;
    QPushButton *pushButton_conf;
    QScrollBar *verticalScrollBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    */

    int buttonWidth = 150;
    ui->pushButton_clear->setMinimumWidth(buttonWidth);
    ui->pushButton_EditSwitch->setMinimumWidth(buttonWidth);
    ui->pushButton_StartStop->setMinimumWidth(buttonWidth);
    ui->pushButton_initial->setMinimumWidth(buttonWidth);
    ui->pushButton_setPattern->setMinimumWidth(buttonWidth);
    ui->pushButton_set_pattern_glider->setMinimumWidth(buttonWidth);
    ui->pushButton_choose->setMinimumWidth(buttonWidth);
    ui->pushButton_conf->setMinimumWidth(buttonWidth);    
    ui->lineEdit_board_size->setMinimumWidth(buttonWidth);
    ui->lineEdit_x_info->setMinimumWidth(buttonWidth);
    ui->lineEdit_y_info->setMinimumWidth(buttonWidth);
    ui->checkBox_Torus->setMinimumWidth(buttonWidth);
    ui->spinBox_period->setMinimumWidth(buttonWidth);
    ui->horizontalScrollBar_period->setMinimumWidth(buttonWidth);

    ui->listView_patterns->setMinimumWidth(buttonWidth);
    ui->listView_patterns->setMinimumHeight(0);

   //  ui->tableView->rowHeight(boxSize);
   //  ui->tableView->columnWidth(boxSize);

   //  // ui->tableView->setGeometry();
   //  // ui->tableView->frameGeometry();
   //  // ui->tableView->rowViewportPosition(30/2);

    // ui->tableView->setMinimumHeight((board.rowCount() + 1) * boxSize);
    ui->tableView->setMaximumHeight((board.rowCount() + 1) * boxSize);
    // ui->tableView->setMinimumWidth((board.columnCount() + 1) * boxSize);
    ui->tableView->setMaximumWidth((board.columnCount() + 1)* boxSize);

   //  // ui->tableView->resizeColumnToContents(board.columnCount());
   //  // ui->tableView->resizeRowToContents(board.rowCount());
   //  // ui->tableView->resize(board.rowCount() * 10, board.columnCount() * 10);

   //  // ui->tableView->rowHeight(box_size);
   //  // ui->tableView->columnWidth(box_size);

   // ui->tableView->setFixedHeight(boxSize * board.rowCount()); //dotyczy calej tabeli
   // ui->tableView->setFixedWidth(boxSize * board.columnCount());


    board.slot_GolfBoardSetPreviewStartRow(25);
    board.slot_GolfBoardSetPreviewStartCol(25);


    // ui->centralWidget->  removeWidget(ui->lineEdit_board_size);
    // ui->layoutH_main->removeWidget(ui->lineEdit_x_info);
    // ui->layoutH_main->removeWidget(ui->lineEdit_y_info);

    ui->lineEdit_board_size->setParent(nullptr);
    ui->lineEdit_x_info->setParent(nullptr);
    ui->lineEdit_y_info->setParent(nullptr);

    ui->lineEdit_board_size->setText(QString("board: %1 x %2").arg(Golf_engine.get_rows()).arg(Golf_engine.get_cols()));
    ui->lineEdit_x_info->setText(QString("view start c: %1").arg(Golf_engine.get_cols()));
    ui->lineEdit_y_info->setText(QString("view start r: %1").arg(Golf_engine.get_rows()));

    ui->statusBar->addWidget(ui->lineEdit_board_size);
    ui->statusBar->addWidget(ui->lineEdit_y_info);
    ui->statusBar->addWidget(ui->lineEdit_x_info);


    period = 100; //ui->spinBox->value();
    ui->spinBox_period->setMaximum(one_second);
    ui->spinBox_period->setMinimum(1);
    ui->spinBox_period->setValue(period);
    ui->horizontalScrollBar_period->setMaximum(one_second);
    ui->horizontalScrollBar_period->setMinimum(1);
    ui->horizontalScrollBar_period->setValue(period);

    ui->tableView->show();





    // qDebug() << QString("box_size: %1, table->height(): %2, board.rowCount(): %3")
    //             .arg(box_size)
    //             .arg(ui->tableView->height())
    //             .arg(board.rowCount());

    // QTableView listRule;
    // listRule.setModel(&rule_list);
    // listRule.rowHeight(30);
    // listRule.columnWidth(50);
    // listRule.show();

    qDebug() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");



    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardClear(): ";
    qDebug() << connect(ui->pushButton_clear,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardClear())
                        );

    qDebug() << "connecting pushButton_initial() -> board.slot_GolfBoardInitial(): ";
    qDebug() << connect(ui->pushButton_initial,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardInitial())
                        );
    qDebug() << "connecting pushButton_setPattern() -> board.slot_GolfBoardSetPattern_blinker(): ";
    qDebug() << connect(ui->pushButton_setPattern,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardSetPattern_blinker())
                        );
    qDebug() << "connecting pushButton_clear() -> board.slot_GolfBoardSetPattern_glider(): ";
    qDebug() << connect(ui->pushButton_set_pattern_glider,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardSetPattern_glider())
                        );


    qDebug() << "connecting pushButton_EditSwitch() -> board.slot_GolfBoardSwitchEditor(): ";
    qDebug() << connect(ui->pushButton_EditSwitch,
                        SIGNAL(clicked()),
                        &board,
                        SLOT(slot_GolfBoardSwitchEditor())
                        );
    qDebug() << "connecting pushButton_EditSwitch() -> this.pushButton_EditSwitch(): ";
    qDebug() << connect(ui->pushButton_EditSwitch,
                        SIGNAL(clicked()),
                        this,
                        SLOT(slot_change_button_name(ui->pushButton_EditSwitch))
                        );



    qDebug() << "connecting pushButton_clear() -> board.slot_button_timer(): ";
    qDebug() << connect(ui->pushButton_StartStop,
                        SIGNAL(clicked()),
                        this,
                        SLOT(slot_button_timer())
                        );
    qDebug() << "connecting signal_data_calculate_timer_pause() -> this.slot_data_calculate_timer_pause(): ";
    qDebug() << connect(this,
                        SIGNAL(signal_data_calculate_timer_pause()),
                        this,
                        SLOT(slot_data_calculate_timer_pause())
                        );
    qDebug() << "connecting signal_data_calculate_timer_run() -> this.slot_data_calculate_timer_run(): ";
    qDebug() << connect(this,
                        SIGNAL(signal_data_calculate_timer_run()),
                        this,
                        SLOT(slot_data_calculate_timer_run())
                        );

    qDebug() << "connecting: timeout() -> board.slot_Calculate() :";
    qDebug() << connect(&data_calculate_timer,
                        SIGNAL(timeout()),
                        &board,
                        SLOT(slot_GolfCalculate()));

    qDebug() << "connecting : board.signal_GolfBoardCalculated() -> board.signal_GolfBoardCalculated():";
    qDebug() << connect(&board,
                        SIGNAL(signal_GolfBoardCalculated()),
                        &board,
                        SLOT(slot_GolfBoardStateUpdate())
                        );

    qDebug() << "connecting : ui->spinBox_period.valueChanged() -> this.slot_set_period():";
    qDebug() << connect(ui->spinBox_period,
                        SIGNAL(valueChanged(int)),
                        this,
                        SLOT(slot_set_period(int))
                        );
    qDebug() << "connecting : ui->horizontalScrollBar_period.valueChanged() -> this.slot_set_period():";
    qDebug() << connect(ui->horizontalScrollBar_period,
                        SIGNAL(valueChanged(int)),
                        this,
                        SLOT(slot_set_period(int))
                        );

    qDebug() << "connecting : ui->checkBox_Torus.stateChanged() -> this.slot_set_torus():";
    qDebug() << connect(ui->checkBox_Torus,
                        SIGNAL(stateChanged(int)),
                        this,
                        SLOT(slot_set_torus(int))
                        );

    data_calculate_timer.setInterval(period);
    data_calculate_timer.setSingleShot(false);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_button_edit()
{
    if(ui->pushButton_EditSwitch->text() == QString("edition enable")) {
        ui->pushButton_EditSwitch->setText(QString("edition disable"));
    }
    else {
        ui->pushButton_EditSwitch->setText(QString("edition enable"));
    }
}

void MainWindow::slot_button_timer()
{
    if(ui->pushButton_StartStop->text() == QString("START")) {
        emit signal_data_calculate_timer_run();
        ui->pushButton_StartStop->setText(QString("STOP"));
    }
    else {
        emit signal_data_calculate_timer_pause();
        ui->pushButton_StartStop->setText(QString("START"));
    }
}

void MainWindow::slot_data_calculate_timer_pause()
{
    data_calculate_timer.stop();
}

void MainWindow::slot_data_calculate_timer_run()
{
    data_calculate_timer.start(period);
}

void MainWindow::slot_set_period(int v)
{
    period = v; //ui->spinBox->value();
    qDebug() << "periond: " << period;
    ui->spinBox_period->setValue(period);   //this may emit signal, but only if current data differs
    ui->horizontalScrollBar_period->setValue(period);  //this may emit signal, but only if current data differs
    data_calculate_timer.stop();
    data_calculate_timer.start(period);
}

void MainWindow::slot_set_torus(int b)
{
    qDebug() << "slot_set_torus(" << b << ")";
    Golf_engine.Torus = static_cast<bool>(b);
}

//SYGNAŁY SĄ
//GENEROWANE SA PRZEZ MOC  w moc_mainwindow.cpp
