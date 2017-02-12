#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout* main_layout = new QHBoxLayout();
    srand(unsigned(std::time(0)));

    Matrix sudoku_file = Matrix("sudokutest.txt");
    std::cout << sudoku_file << std::endl;

    my_board = new board();
    my_board->set_matrix(sudoku_file);
    my_board->display();

    main_layout->addWidget(my_board);

    QWidget* button_Widget = new QWidget();

    QVBoxLayout* control_Widget_Layout = new QVBoxLayout();

    check_button = new QPushButton("check!");

    correctness_label = new QLabel("False");

    connect(check_button,SIGNAL(clicked(bool)), this, SLOT(check_answer()));

    control_Widget_Layout->addWidget(check_button);

    control_Widget_Layout->addWidget(correctness_label);

    button_Widget->setLayout(control_Widget_Layout);

    main_layout->addWidget(button_Widget);

    this->centralWidget()->setLayout(main_layout);

    this->resize(1200,1000);
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

MainWindow::~MainWindow()
{
    delete ui;
}
