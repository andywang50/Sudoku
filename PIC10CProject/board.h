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

class myLineEdit:public QLineEdit{
    Q_OBJECT
public:
    myLineEdit(QWidget *parent = 0):QLineEdit(parent){}
    void myLineEdit::contextMenuEvent(QContextMenuEvent *event){
        if (event) return;
        return;
    }

};

class board: public QWidget{
    Q_OBJECT
public:

    friend class Mainwindow;

    board(QWidget *parent = 0);

    void display();

    void set_matrix(const Matrix& matrix);

    Matrix get_matrix() const {return displaying_matrix;}

    Matrix get_solution_matrix() const {return solution_matrix;}

    void set_style(myLineEdit* edit_ptr, bool read_only, int row, int col);

    bool check_answer() const;

    void set_warning_style(myLineEdit* edit_ptr, bool read_only);

    int get_size(){return size;}

    std::vector<std::vector<myLineEdit*>>& get_table(){return table;}

    QTimer* get_warning_hint_timer() {return warning_hint_timer;}

    void set_matrix_value(Entry entry_to_be_modified, int answer){
        displaying_matrix(entry_to_be_modified) = answer;
    }

signals:
    void invokeSlotValueChanged();

private slots:
    void slotValueChanged();
    void recover_from_warning();

private:
    int size;
    Matrix displaying_matrix;
    std::vector<std::vector<myLineEdit*>>table = std::vector<std::vector<myLineEdit*>>();
    QGridLayout* board_layout = nullptr;

    Matrix solution_matrix;
    QTimer* warning_hint_timer;
    const QString editable_style1 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #006aff; background:  rgb(113, 186, 170);");
    const QString editable_style2 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #006aff;");
    const QString read_only_style1 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; background: rgb(113, 186, 170);");
    const QString read_only_style2 = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; ");
    const QString editable_warning_style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #4066e5; background: rgb(255, 0, 0);");
    const QString read_only_warning_style = QString::fromStdString("font-size: 20pt; font-weight: bold; color: #ffffff; background: rgb(255, 128,128);");





};

#endif // BOARD_H
