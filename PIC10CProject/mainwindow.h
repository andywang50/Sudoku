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
private:
    Ui::MainWindow *ui;

    board* my_board;
    QPushButton* check_button;
    QLabel* correctness_label;
};

#endif // MAINWINDOW_H
