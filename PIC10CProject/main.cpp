#include "mainwindow.h"
#include <QApplication>
//#include "../Sudoku_Generator.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>



using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    return a.exec();
}
