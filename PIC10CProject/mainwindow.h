#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include "board.h"
#include <QTimer>
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

private:
    Ui::MainWindow *ui;

    board* my_board;
    QLabel* correctness_label;

    Matrix original_matrix;

    QPushButton* check_button;
    QPushButton* newgame_button;
    QPushButton* quit_button;
    QPushButton* solve_button;
    QPushButton* restart_button;

    const QString bg_Style = QString::fromStdString(" background:  rgb(70, 72, 76);"); //font-size: 20pt; font-weight: bold; color: #87f1ff;
    const QString button_Style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; background:  rgb(90, 92, 96);");
    const QString label_Style = QString::fromStdString("font-size: 13pt; font-weight: bold; color: #ffffff;");


};

#endif // MAINWINDOW_H
