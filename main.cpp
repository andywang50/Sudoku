
#include "Stack.h"
#include "Matrix.h"
//#include "Sudoku_Solver.h"
#include "Sudoku_Generator.h"
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
	solver1.solve();
	cout << solver1.get_matrix() << endl;
	
	
	Sudoku_Generator generator1 = Sudoku_Generator(9);

	Matrix generated = generator1.generate();

	cout << generated << endl << endl;

	
	Sudoku_Solver solver16 = Sudoku_Solver(generated);
	solver16.solve();
	cout << solver16.get_matrix() << endl;
	
	
	


	return 0;
}