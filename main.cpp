
#include "Stack.h"
#include "Matrix.h"
#include "Sudoku_Solver.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <ctime>        // std::time
#include <cstdlib> 

using namespace std;

int main() {
	srand(unsigned(std::time(0)));

	Matrix sudoku_file = Matrix("sudokutest.txt");
	cout << sudoku_file << endl;

	Sudoku_Solver solver1 = Sudoku_Solver(sudoku_file);

	cout << sudoku_file << endl;
	cout << solver1.solve() << endl;
	cout << solver1.get_matrix() << endl;

	return 0;
}