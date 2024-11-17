#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "golf_board.h"
#include <QDateTime>
#include <QPushButton>
#include "T_Golf_engine.h"

enum {one_second = 1000};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    T_Golf_engine& Golf_engine;
public:
    int period;
    QTimer data_calculate_timer;
    T_GolfBoard board;
    // gOfL_ruleList rule_list;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void slot_button_edit();
    void slot_button_timer();
    void slot_data_calculate_timer_pause();
    void slot_data_calculate_timer_run();
    void slot_set_period(int);
    void slot_set_torus(int);
public:
signals:
    void signal_data_calculate_timer_pause();
    void signal_data_calculate_timer_run();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
