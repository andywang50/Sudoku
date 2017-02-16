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

class board: public QWidget{
    Q_OBJECT
public:
    board(QWidget *parent = 0);

    void display();

    void set_matrix(const Matrix& matrix);

    Matrix get_matrix() const {return displaying_matrix;}

    Matrix get_solution_matrix() const {return solution_matrix;}

    void set_style(QLineEdit* edit_ptr, bool read_only, int row, int col);

    bool check_answer() const;
private slots:
    void slotValueChanged(QString);
private:
    int size;
    Matrix displaying_matrix;
    std::vector<std::vector<QLineEdit*>>table = std::vector<std::vector<QLineEdit*>>();
    QGridLayout* board_layout = nullptr;

    Matrix solution_matrix;

};

#endif // BOARD_H
