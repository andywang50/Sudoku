#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include "board.h"
#include <QTimer>
#include <QTime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void check_answer();
    void start_newgame();
    void solve_for_me();
    void restart();
    void hint();
    void empty();

    void hint_incorrect_recover();
    void hint_nextstep_recover();

    void updateDisplay() {
         int secs = time.elapsed() / 1000;
         int mins = (secs / 60) % 60;
         int hours = (secs / 3600);
         secs = secs % 60;
         timeLabel->setText(QString("%1:%2:%3")
                             .arg(hours, 2, 10, QLatin1Char('0'))
                             .arg(mins, 2, 10, QLatin1Char('0'))
                             .arg(secs, 2, 10, QLatin1Char('0')) );
     }

private:


    Ui::MainWindow *ui;

    board* my_board;
    QLabel* correctness_label;

    Matrix original_matrix;

    QLabel* title_label;
    QPushButton* check_button;
    QPushButton* newgame_button;
    QPushButton* quit_button;
    QPushButton* solve_button;
    QPushButton* restart_button;
    QPushButton* hint_button;
    QPushButton* empty_button;

    QLabel *timeLabel;
    QTime time;
    QTimer timer;

    const QString menuBar_Style = QString::fromStdString("QMenuBar {\
                                                         color:#aaaaaa;\
                                                      }\
                                                      QMenuBar::item {\
                                                         color:#ffffff; \
                                                          spacing: 3px; /* spacing between menu bar items */\
                                                          padding: 1px 4px;\
                                                          background: transparent;\
                                                          border-radius: 4px;\
                                                      }\
                                                      QMenuBar::item:selected { /* when selected using mouse or keyboard */\
                                                         background: #a8a8a8;\
                                                      }\
                                                      QMenuBar::item:pressed {\
                                                         background: #888888;\
                                                      }");
    const QString menuMenu_Style = QString::fromStdString("QMenu {\
                                                           margin: 2px; /* some spacing around the menu */\
                                                      }\
                                                      QMenu::item {\
                                                          color:#ffffff;\
                                                          padding: 2px 25px 2px 20px;\
                                                          border: 1px solid transparent; /* reserve space for selection border */\
                                                      }\
                                                      QMenu::item:disabled {\
                                                          color:#777777;\
                                                          padding: 2px 25px 2px 20px;\
                                                          border: 1px solid transparent; /* reserve space for selection border */\
                                                      }\
                                                      QMenu::item:selected {\
                                                          border-color: darkblue;\
                                                          background: rgba(100, 100, 100, 150);\
                                                      }\
                                                      QMenu::icon:checked { /* appearance of a 'checked' icon */\
                                                          background: gray;\
                                                          border: 1px inset gray;\
                                                          position: absolute;\
                                                          top: 1px;\
                                                          right: 1px;\
                                                          bottom: 1px;\
                                                          left: 1px;\
                                                      }\
                                                      QMenu::separator {\
                                                          height: 2px;\
                                                          background: lightblue;\
                                                          margin-left: 10px;\
                                                          margin-right: 5px;\
                                                      }\
                                                     ");
    const QString title_Style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #88aaff; "); //font-size: 20pt; font-weight: bold; color: #87f1ff;

    const QString bg_Style = QString::fromStdString("font-family:  Georgia, Serif; background:  rgb(70, 72, 76);"); //font-size: 20pt; font-weight: bold; color: #87f1ff;
    const QString button_Style = QString::fromStdString(":enabled{font-size: 20pt; font-weight: bold; color: #ffffff; background:  rgb(90, 92, 96);} "
                                                        ":disabled{font-size: 20pt; font-weight: bold; color: #424344; background:  rgb(90, 92, 96);}");
    const QString label_Style = QString::fromStdString("font-size: 13pt; font-weight: bold; color: #ffffff;");

    Entry next_to_update = Entry(-1,-1);

    int incorrect_row = -1;
    int incorrect_column = -1;

    //QTimer* incorrect_hint_timer;
    //QTimer* nextstep_hint_timer;

    const QString hint_style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #4066e5; background:  rgb(255, 233, 0);");

};

#endif // MAINWINDOW_H
