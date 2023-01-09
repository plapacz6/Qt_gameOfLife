#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    int box_size;
    qDebug() << QString("box_size: %1, table->height(): %2, board.rowCount(): %3")
                .arg(box_size)
                .arg(ui->tableView->height())
                .arg(board.rowCount());


    ui->setupUi(this);

    ui->tableView->setModel(&board);

    box_size = ui->tableView->height()/board.rowCount();

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

}

MainWindow::~MainWindow()
{
    delete ui;
}
