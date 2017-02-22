#ifndef BOARD_H
#define BOARD_H
//#include "../Matrix.h"
#include "../Sudoku_Generator.h"
#include <QWidget>
#include <QGridLayout>
#include <QRegExpValidator>
#include <QRegExp>
#include <QLineEdit>
#include <QString>
#include <String>
#include <vector>
#include <iostream>
#include <QTimer>

class board: public QWidget{
    Q_OBJECT
public:

    friend class mainwindow;

    board(QWidget *parent = 0);

    void display();

    void set_matrix(const Matrix& matrix);

    Matrix get_matrix() const {return displaying_matrix;}

    Matrix get_solution_matrix() const {return solution_matrix;}

    void set_style(QLineEdit* edit_ptr, bool read_only, int row, int col);

    bool check_answer() const;

    void set_warning_style(QLineEdit* edit_ptr, bool read_only);

private slots:
    void slotValueChanged(QString);
    void recover_from_warning();

private:
    int size;
    Matrix displaying_matrix;
    std::vector<std::vector<QLineEdit*>>table = std::vector<std::vector<QLineEdit*>>();
    QGridLayout* board_layout = nullptr;

    Matrix solution_matrix;
    QTimer* warning_hint_timer;
    const QString editable_style1 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #4066e5; background:  rgb(113, 186, 170);");
    const QString editable_style2 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #4066e5;");
    const QString read_only_style1 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; background: rgb(113, 186, 170);");
    const QString read_only_style2 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; ");
    const QString editable_warning_style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #4066e5; background: rgb(255, 0, 0);");
    const QString read_only_warning_style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; background: rgb(255, 128,128);");





};

#endif // BOARD_H
