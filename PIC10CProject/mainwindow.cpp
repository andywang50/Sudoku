#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menuBar->setStyleSheet(this->menuBar_Style);
    ui->menuMenu->setStyleSheet(this->menuMenu_Style);

    ui->actionClear->setEnabled(false);
    ui->actionCheck->setEnabled(false);
    ui->actionSolveForMe->setEnabled(false);
    ui->actionRestart->setEnabled(false);



    this->setWindowTitle("Sudoku Game");
    this->setStyleSheet(this->bg_Style);
    QHBoxLayout* main_layout = new QHBoxLayout();
    srand(unsigned(std::time(0)));

    //Matrix sudoku_file = Matrix("sudokutest.txt");
    //std::cout << sudoku_file << std::endl;

    Matrix sudoku = Matrix(9);

    my_board = new board();
    my_board->set_matrix(sudoku);
    my_board->display();

    main_layout->addWidget(my_board);

    QWidget* button_Widget = new QWidget();

    QVBoxLayout* control_Widget_Layout = new QVBoxLayout();

    //incorrect_hint_timer = new QTimer(this);
    //connect(incorrect_hint_timer, SIGNAL(timeout()), this, SLOT(hint_incorrect_recover()));

    //nextstep_hint_timer = new QTimer(this);
    //connect(nextstep_hint_timer, SIGNAL(timeout()), this, SLOT(hint_nextstep_recover()));

    title_label = new QLabel("SUDOKU!");
    title_label->setStyleSheet(this->title_Style);
    title_label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    title_label->adjustSize();
    title_label->setFixedHeight(70);

    newgame_button = new QPushButton("Start");
    newgame_button->setStyleSheet(this->button_Style);

    quit_button = new QPushButton("Quit");
    quit_button->setStyleSheet(this->button_Style);

    empty_button = new QPushButton("Clear");
    empty_button->setEnabled(false);
    empty_button->setStyleSheet(this->button_Style);

    check_button = new QPushButton("Check");
    check_button->setEnabled(false);
    check_button->setStyleSheet(this->button_Style);

    solve_button = new QPushButton("Solve");
    solve_button->setEnabled(false);
    solve_button->setStyleSheet(this->button_Style);

    restart_button = new QPushButton("Restart");
    restart_button->setEnabled(false);
    restart_button->setStyleSheet(this->button_Style);

    hint_button = new QPushButton("Hint");
    hint_button->setEnabled(false);
    hint_button->setStyleSheet(this->button_Style);

    timeLabel = new QLabel();
    timeLabel->setStyleSheet(this->label_Style);
    timeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    timeLabel->adjustSize();
    timeLabel->setFixedHeight(70);

    correctness_label = new QLabel("");
    correctness_label->setStyleSheet(this->label_Style);


    connect(check_button,SIGNAL(clicked(bool)), this, SLOT(check_answer()));
    connect(ui->actionCheck,SIGNAL(triggered()),this,SLOT(check_answer()));

    connect(newgame_button,SIGNAL(clicked(bool)), this, SLOT(start_newgame()));
    connect(ui->actionNewGame,SIGNAL(triggered()),this,SLOT(start_newgame()));

    connect(quit_button,SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));

    connect(solve_button,SIGNAL(clicked(bool)), this, SLOT(solve_for_me()));
    connect(ui->actionSolveForMe,SIGNAL(triggered()),this,SLOT(solve_for_me()));

    connect(hint_button,SIGNAL(clicked(bool)), this, SLOT(hint()));

    connect(restart_button,SIGNAL(clicked(bool)), this, SLOT(restart()));
    connect(ui->actionRestart,SIGNAL(triggered()),this,SLOT(restart()));

    connect(empty_button,SIGNAL(clicked(bool)), this, SLOT(empty()));
    connect(ui->actionClear,SIGNAL(triggered()),this,SLOT(empty()));

    control_Widget_Layout->addWidget(title_label);

    control_Widget_Layout->addWidget(newgame_button);

    control_Widget_Layout->addWidget(empty_button);

    control_Widget_Layout->addWidget(check_button);

    control_Widget_Layout->addWidget(solve_button);

    control_Widget_Layout->addWidget(restart_button);

    control_Widget_Layout->addWidget(hint_button);

    control_Widget_Layout->addWidget(correctness_label);

    control_Widget_Layout->addWidget(quit_button);

    control_Widget_Layout->addWidget(timeLabel);

    button_Widget->setLayout(control_Widget_Layout);

    main_layout->addWidget(button_Widget);

    this->centralWidget()->setLayout(main_layout);

    this->resize(1200,1000);



    //this->setFixedSize(1200,1000);
}

 void MainWindow::hint(){
    bool any_incorrect_so_far = false;
    std::vector<Entry> incorrect_entries = std::vector<Entry>();
    Matrix displaying_matrix = my_board->get_matrix();
    Matrix solution_matrix = my_board->get_solution_matrix();
    for (int i = 0; i < my_board->get_size(); i++){
        for (int j =0; j < my_board->get_size();j++){
            int num = displaying_matrix(i,j);
            if (num == 0) continue;
            if (num != solution_matrix(i,j)){
                any_incorrect_so_far = true;
                incorrect_row = i;
                incorrect_column = j;
                incorrect_entries.push_back(Entry(i,j));
                //break;
            }
        }
        //if (any_incorrect_so_far) break;
    }

    //if (incorrect_row != -1 && incorrect_column != -1){
    if (incorrect_entries.size()>0){
        for (Entry e:incorrect_entries){
            incorrect_row = e.get_row();
            incorrect_column = e.get_col();
            my_board->set_warning_style(my_board->get_table()[incorrect_row][incorrect_column],false);
        }
        my_board->emit invokeSlotValueChanged();
        //incorrect_hint_timer->start(500);
        hint_incorrect_recover();

    }else{
        if (displaying_matrix.is_complete()){
               check_answer();
               return;
        }
        if (next_to_update == Entry(-1,-1) || displaying_matrix(next_to_update) ==  solution_matrix(next_to_update)){
            Sudoku_Solver temp_Solver = Sudoku_Solver(displaying_matrix);
            this->next_to_update = temp_Solver.get_next_to_update();
        }
        int answer = solution_matrix(next_to_update);
        int row = next_to_update.get_row();
        int col = next_to_update.get_col();
        my_board->get_table()[row][col]->setText(QString::fromStdString(std::to_string(answer)));
        my_board->set_matrix_value(next_to_update,answer);
        my_board->get_table()[row][col]->setStyleSheet(hint_style);
        //nextstep_hint_timer->start(500);
        hint_nextstep_recover();
        return;

    }
    return;
 }

 void MainWindow::hint_incorrect_recover(){
    //my_board->recover_from_warning();
     my_board->get_warning_hint_timer()->start(500);
    incorrect_column=-1;
    incorrect_row = -1;
 }
 void MainWindow::hint_nextstep_recover(){
    my_board->get_warning_hint_timer()->start(500);
    return;
 }


 void MainWindow::check_answer(){
    bool correct = my_board->check_answer();
    if(correct){
        correctness_label->setText("Correct!");
        timer.stop();
        time.start();
    }
    else{
        correctness_label->setText("Incorrect!");
    }
 }



 void MainWindow::start_newgame(){
     newgame_button->setEnabled(false);
     this->repaint();
     Sudoku_Generator generator = Sudoku_Generator(9);
     Matrix sudoku = generator.generate();
     original_matrix = sudoku;

     my_board->set_matrix(sudoku);
     my_board->display();
     restart_button->setEnabled(true);
     solve_button->setEnabled(true);
     check_button->setEnabled(true);
     hint_button->setEnabled(true);
     newgame_button->setEnabled(true);
     empty_button->setEnabled(true);

     ui->actionRestart->setEnabled(true);
     ui->actionSolveForMe->setEnabled(true);
     ui->actionCheck->setEnabled(true);
     ui->actionNewGame->setEnabled(true);
     ui->actionClear->setEnabled(true);

     Entry next_to_update = Entry(-1,-1);
     correctness_label->setText("");

     time.start();
     updateDisplay();
     connect(&timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
     timer.start(1000);
 }

 void MainWindow::solve_for_me(){
    Matrix solution_matrix = my_board->get_solution_matrix();
    my_board->set_matrix(solution_matrix);
    my_board->display();

    correctness_label->setText("Correct!");
    timer.stop();
    time.start();

 }

 void MainWindow::empty(){
     empty_button->setEnabled(false);
     check_button->setEnabled(false);
     solve_button->setEnabled(false);
     restart_button->setEnabled(false);
     hint_button->setEnabled(false);

     ui->actionClear->setEnabled(false);
     ui->actionCheck->setEnabled(false);
     ui->actionSolveForMe->setEnabled(false);
     ui->actionRestart->setEnabled(false);

     Matrix sudoku = Matrix(9);
     original_matrix = sudoku;

     my_board->set_matrix(sudoku);
     my_board->display();
     Entry next_to_update = Entry(-1,-1);

     correctness_label->setText("");
     timer.stop();
     time.start();
     timeLabel->setText("00:00:00");


 }

 void MainWindow::restart(){
     my_board->set_matrix(original_matrix);
     my_board->display();
     Entry next_to_update = Entry(-1,-1);
     empty_button->setEnabled(true);
     check_button->setEnabled(true);
     solve_button->setEnabled(true);
     restart_button->setEnabled(true);
     hint_button->setEnabled(true);


     ui->actionClear->setEnabled(true);
     ui->actionCheck->setEnabled(true);
     ui->actionSolveForMe->setEnabled(true);
     ui->actionRestart->setEnabled(true);

     correctness_label->setText("");
     time.start();
     updateDisplay();
     connect(&timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
     timer.start(1000);
 }

MainWindow::~MainWindow()
{
    delete ui;
}
