#include "board.h"

board::board(QWidget *parent):QWidget(parent){

    size = 0;
    displaying_matrix = Matrix();
    table = std::vector<std::vector<QLineEdit*>>();
    board_layout = nullptr;

}


void board::set_matrix(const Matrix& matrix){
    size = matrix.get_size();
    displaying_matrix = matrix;
    Sudoku_Solver solver1 = Sudoku_Solver(matrix);
    solver1.solve();
    solution_matrix = solver1.get_matrix();
    table = std::vector<std::vector<QLineEdit*>>();
    for (int i = 0; i < size; i++){
        std::vector<QLineEdit*> temp_vector = std::vector<QLineEdit*>();
        for (int j = 0; j < size; j++ ){
            QLineEdit* temp = new QLineEdit(this);
            QRegExp rx("[1-9]\\d{0,0}");
            QRegExpValidator *v = new QRegExpValidator(rx, this);
            temp->setValidator(v);
            temp->setMaxLength(1);
            temp->setFixedSize(100,100);
            temp->setAlignment(Qt::AlignCenter);
            temp_vector.push_back(temp);

            connect(temp,SIGNAL(textEdited(QString)),this,SLOT(slotValueChanged(QString)));

        }
        table.push_back(temp_vector);

    }
}

void board::slotValueChanged(QString testString){

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            QString input_qstr = table[i][j]->text();
            int num = input_qstr.toInt();
            displaying_matrix(i,j) = num;
        }
    }

}


bool board::check_answer() const{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (displaying_matrix(i,j) != solution_matrix(i,j)) {

                return false;
            }
        }
    }
    return true;
}

void board::set_style(QLineEdit* edit_ptr, bool read_only, int row, int col){
    edit_ptr->setReadOnly(read_only);
    int sqr_size = sqrt(size);
    bool flag = ((row/sqr_size*sqr_size+col/sqr_size) % 2) == 1;

    if (read_only){
        if (flag)  edit_ptr->setStyleSheet("font-size: 20pt; font-weight: bold; color: #0061ff; background: rgb(206, 255, 217);");
        else edit_ptr->setStyleSheet("font-size: 20pt; font-weight: bold; color: #0061ff; ");

    }
    else{
        if (flag) edit_ptr->setStyleSheet("font-size: 20pt; font-weight: bold; color: #87f1ff; background:  rgb(206, 255, 217);");
        else edit_ptr->setStyleSheet("font-size: 20pt; font-weight: bold; color: #87f1ff;");
    }
}

void board::display(){
    board_layout = new QGridLayout();
    board_layout->setSpacing(10);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
                //int value = 1;
                int value = displaying_matrix(i,j);
                std::string str = "";
                QLineEdit* lineedit_ptr = table[i][j];
                set_style(lineedit_ptr,true, i , j);
                switch(value){
                    case 0: str = ""; set_style(lineedit_ptr,false,i ,j ); break;
                    case 10: str = "A";break;
                    case 11: str = "B"; break;
                    case 12: str = "C";break;
                    case 13: str = "D"; break;
                    case 14: str = "E"; break;
                    case 15: str = "F";break;
                    case 16: str = "G"; break;
                    default: str= std::to_string(value);break;

                }
                QString txt_display = QString::fromStdString(str);
                lineedit_ptr->setText(txt_display);
                board_layout->addWidget(lineedit_ptr,i,j);



        }
    }
    this->setLayout(board_layout);

}
