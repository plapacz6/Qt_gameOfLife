#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QItemSelection>
#include "TQ_GolfBoardPreview.h"
#include "TQ_GolfPatternsList.h"

// #include "T_Golf_engine.h"

enum {one_second = 1000};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    T_Golf_engine& Golf_engine;
public:
    QString choosenPatternName;
    int period;
    QTimer data_calculate_timer;
    T_GolfBoardPreview board;    
    // gOfL_ruleList rule_list;
    TQ_GolfPatternsList pattern_list;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QItemSelectionModel *sm_tv;
    QItemSelectionModel *sm_pl;

public slots:
    void slot_button_edit();
    void slot_button_timer();
    void slot_data_calculate_timer_pause();
    void slot_data_calculate_timer_run();
    void slot_set_period(int);
    void slot_set_torus(int);
    void slot_choose_pattern();
    void slot_paste_pattern();
    void slot_keep_pattern();
    void slot_print_pattern(T_GolfPatternDescription& pt);
public:
signals:
    void signal_data_calculate_timer_pause();
    void signal_data_calculate_timer_run();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
