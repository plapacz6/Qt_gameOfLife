#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gofl_board.h"
#include "gofl_rulelist.h"
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer data_calculate_timer;
    T_GolfBoard board;
    gOfL_ruleList rule_list;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

public:
signals:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
