#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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


    newgame_button = new QPushButton("Start");

    quit_button = new QPushButton("Quit");

    check_button = new QPushButton("Check");
    check_button->setEnabled(false);

    solve_button = new QPushButton("Solve");
    solve_button->setEnabled(false);

    restart_button = new QPushButton("Restart");
    restart_button->setEnabled(false);

    correctness_label = new QLabel("");

    connect(check_button,SIGNAL(clicked(bool)), this, SLOT(check_answer()));

    connect(newgame_button,SIGNAL(clicked(bool)), this, SLOT(start_newgame()));

    connect(quit_button,SIGNAL(clicked(bool)), QApplication::instance(), SLOT(quit()));

    connect(solve_button,SIGNAL(clicked(bool)), this, SLOT(solve_for_me()));

    connect(restart_button,SIGNAL(clicked(bool)), this, SLOT(restart()));


    control_Widget_Layout->addWidget(newgame_button);

    control_Widget_Layout->addWidget(check_button);

    control_Widget_Layout->addWidget(solve_button);

    control_Widget_Layout->addWidget(restart_button);

    control_Widget_Layout->addWidget(correctness_label);

    control_Widget_Layout->addWidget(quit_button);

    button_Widget->setLayout(control_Widget_Layout);

    main_layout->addWidget(button_Widget);

    this->centralWidget()->setLayout(main_layout);

    this->resize(1200,1000);

    //this->setFixedSize(1200,1000);
}

 void MainWindow::check_answer(){
    bool correct = my_board->check_answer();
    if(correct){
        correctness_label->setText("Correct!");
    }
    else{
        correctness_label->setText("Incorrect!");
    }
 }

 void MainWindow::start_newgame(){
     Sudoku_Generator generator = Sudoku_Generator(9);
     Matrix sudoku = generator.generate();
     original_matrix = sudoku;
     std::cout<<original_matrix<<std::endl;

     my_board->set_matrix(sudoku);
     my_board->display();
     restart_button->setEnabled(true);
     solve_button->setEnabled(true);
     check_button->setEnabled(true);

 }

 void MainWindow::solve_for_me(){
    Matrix solution_matrix = my_board->get_solution_matrix();
    my_board->set_matrix(solution_matrix);
    my_board->display();
    std::cout<<original_matrix<<std::endl;

 }

 void MainWindow::restart(){
     my_board->set_matrix(original_matrix);
     my_board->display();
 }

MainWindow::~MainWindow()
{
    delete ui;
}
