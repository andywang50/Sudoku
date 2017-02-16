#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include "board.h"
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
};

#endif // MAINWINDOW_H
