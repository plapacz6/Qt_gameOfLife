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
    double boxSize = windowHight / board.rowCount();

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


    //setting width of buttons sections
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


    //!!!!!!!!!!!!!!!!!!!!!   setting tableView size and place and main window size
    ui->tableView->setMinimumHeight((board.rowCount() ) * boxSize);
    ui->tableView->setMaximumHeight((board.rowCount() ) * boxSize);
    ui->tableView->setMinimumWidth((board.columnCount() ) * boxSize);
    ui->tableView->setMaximumWidth((board.columnCount() )* boxSize);


    //setting preview region on center of Golf_engine board
    board.slot_GolfBoardSetPreviewStartRow(
        (Golf_R > Golf_ROWS)
        ? (Golf_R - Golf_ROWS) / 2
        :   0
    );
    board.slot_GolfBoardSetPreviewStartCol(
        (Golf_C > Golf_COLS)
        ? (Golf_C - Golf_COLS) / 2
        :   0
    );

    //experimental scalling
    //off                      not work as expected (not equal size of cells)
    // ui->tableView->horizontalHeader()->stretchLastSection();
    // ui->tableView->resizeColumnsToContents();
    // ui->tableView->verticalHeader()->stretchLastSection();
    // ui->tableView->resizeRowsToContents();

    //setting status bar
    ui->lineEdit_board_size->setParent(nullptr);
    ui->lineEdit_x_info->setParent(nullptr);
    ui->lineEdit_y_info->setParent(nullptr);

    ui->lineEdit_board_size->setText(QString("board: %1 x %2").arg(Golf_engine.get_rows()).arg(Golf_engine.get_cols()));
    ui->lineEdit_x_info->setText(QString("view start c: %1").arg(board.starting_col_of_view));
    ui->lineEdit_y_info->setText(QString("view start r: %1").arg(board.starting_row_of_view));

    ui->statusBar->addWidget(ui->lineEdit_board_size);
    ui->statusBar->addWidget(ui->lineEdit_y_info);
    ui->statusBar->addWidget(ui->lineEdit_x_info);


    //setting period control (animation's speed)
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

    qDebug() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");



    //conneting slots
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

    // qDebug() << "connecting pushButton_EditSwitch() -> board.slot_GolfBoardSwitchEditor(): ";
    /* actions sequence is crutial in switching edit mode, so this slot is called directly by slot for edit button */
    // qDebug() << connect(ui->pushButton_EditSwitch,
    //                     SIGNAL(clicked()),
    //                     &board,
    //                     SLOT(slot_GolfBoardSwitchEditor())
    //                     );
    qDebug() << "connecting pushButton_EditSwitch() -> this.pushButton_EditSwitch(): ";
    qDebug() << connect(ui->pushButton_EditSwitch,
                        SIGNAL(clicked()),
                        this,
                        SLOT(slot_button_edit())
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
    qDebug() << __PRETTY_FUNCTION__;

    if(ui->pushButton_EditSwitch->text() == QString("accept pattern")) {
        QItemSelectionModel *sm = ui->tableView->selectionModel();
        QModelIndexList isml = sm->selectedIndexes();
        qDebug() << "isml.size(): " << isml.size();
        for(const QModelIndex& idx: isml) {
            qDebug() << "idx: " << idx;
            if(board.data(idx, Qt::UserRole).toBool() == false) {
                board.setData(idx, true, Qt::UserRole);
            }
            else {
                board.setData(idx, false, Qt::UserRole);
            }
            // int row = idx.row() + board.starting_row_of_view;
            // int col = idx.column() + board.starting_col_of_view;
            // if(Golf_engine.get_cell(row, col)) {
            //     Golf_engine.set_cell(row, col, false);
            // }
            // else {
            //     Golf_engine.set_cell(row, col, true);
            // }
        }
        sm->clearSelection();
        ui->pushButton_EditSwitch->setText(QString("edit pattern"));
        //not needed: this emit is made elsewere //emit board.dataChanged( board.index(0,0), board.index(Golf_ROWS - 1, Golf_COLS - 1) );

        board.slot_GolfBoardSwitchEditor();
    }
    else {
        ui->pushButton_EditSwitch->setText(QString("accept pattern"));
        board.slot_GolfBoardSwitchEditor();
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
    period = v;
    qDebug() << "period: " << period;
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
