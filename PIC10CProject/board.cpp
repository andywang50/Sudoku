#include "board.h"

board::board(QWidget *parent):QWidget(parent){

    connect(this,SIGNAL(invokeSlotValueChanged()),this,SLOT(slotValueChanged()));
    size = 0;
    displaying_matrix = Matrix();
    table = std::vector<std::vector<QLineEdit*>>();
    //board_layout = nullptr;
    board_layout = new QGridLayout();
    board_layout->setSpacing(10);
    this->setLayout(board_layout);
    warning_hint_timer = new QTimer(this);
    connect(warning_hint_timer,SIGNAL(timeout()),this,SLOT(recover_from_warning()));
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

            connect(temp,SIGNAL(textEdited(QString)),this,SLOT(slotValueChanged()));
        }
        table.push_back(temp_vector);

    }
}

void board::slotValueChanged(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            QString input_qstr = table[i][j]->text();
            int num = input_qstr.toInt();
            displaying_matrix(i,j) = num;
        }
    }

    //int violating_count = 0;

    std::unordered_map<int,bool> violating_entries = std::unordered_map<int,bool>();
    Sudoku_Solver temp_solver = Sudoku_Solver(displaying_matrix);
    for (int i = 0; i < size; i++){
        for (int j = 0; j<size; j++){
            Entry current_entry = Entry(i,j);
            bool read_only_current = table[i][j]->isReadOnly();
            int current_key = i*size+j;

            int current_num = displaying_matrix(current_entry);
            if (current_num == 0) continue;
            std::vector<Entry> neighbors = temp_solver.get_row(current_entry);

            for (Entry temp_entry:neighbors){
                 if (temp_entry == current_entry) continue;
                 int temp_num = displaying_matrix(temp_entry);
                 if(temp_num ==0 || temp_num != current_num) continue;
                 int row = temp_entry.get_row();
                 int col = temp_entry.get_col();
                 bool read_only_temp = table[row][col]->isReadOnly();
                 violating_entries.insert ({row*size+col,read_only_temp});
                 violating_entries.insert ({current_key,read_only_current});

            }
            neighbors = temp_solver.get_col(current_entry);

            for (Entry temp_entry:neighbors){
                if (temp_entry == current_entry) continue;
                int temp_num = displaying_matrix(temp_entry);
                if(temp_num ==0 || temp_num != current_num) continue;
                int row = temp_entry.get_row();
                int col = temp_entry.get_col();
                bool read_only_temp = table[row][col]->isReadOnly();
                violating_entries.insert ({row*size+col,read_only_temp});
                violating_entries.insert ({current_key,read_only_current});

            }
            neighbors = temp_solver.get_square(current_entry);
            for (Entry temp_entry:neighbors){
                if (temp_entry == current_entry) continue;
                int temp_num = displaying_matrix(temp_entry);
                if(temp_num ==0 || temp_num != current_num) continue;
                int row = temp_entry.get_row();
                int col = temp_entry.get_col();
                bool read_only_temp = table[row][col]->isReadOnly();
                violating_entries.insert ({row*size+col,read_only_temp});
                violating_entries.insert ({current_key,read_only_current});

            }

        }
    }
    //violating_count = violating_entries.size();

    //std::cout<<violating_count << std::endl;
    for (auto pair:violating_entries){
        int key = pair.first;
        int row = key/size;
        int col = key%size;
        QLineEdit* temp = table[row][col];
        bool read_only =temp->isReadOnly();
        set_warning_style(temp,read_only);
    }
    warning_hint_timer->start(500);

}

void board::set_warning_style(QLineEdit *edit_ptr, bool read_only){

    if (read_only){

        edit_ptr->setStyleSheet(read_only_warning_style);

    }
    else{
        edit_ptr->setStyleSheet(editable_warning_style);

    }
}
void board::recover_from_warning(){
    warning_hint_timer->stop();
    for(int row = 0; row <size; row++){
        for (int col = 0; col<size; col++){
            QLineEdit* edit_ptr = table[row][col];
            bool read_only = edit_ptr->isReadOnly();
            int sqr_size = sqrt(size);
            bool flag = ((row/sqr_size*sqr_size+col/sqr_size) % 2) == 1;

            if (read_only){
                if (flag)  edit_ptr->setStyleSheet(this->read_only_style1);

                else edit_ptr->setStyleSheet(this->read_only_style2);

            }
            else{
                if (flag) edit_ptr->setStyleSheet(this->editable_style1);
                else edit_ptr->setStyleSheet(this->editable_style2);
            }

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
        if (flag)  edit_ptr->setStyleSheet(this->read_only_style1);

        else edit_ptr->setStyleSheet(this->read_only_style2);

    }
    else{
        if (flag) edit_ptr->setStyleSheet(this->editable_style1);
        else edit_ptr->setStyleSheet(this->editable_style2);
    }

}

void board::display(){

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


}
