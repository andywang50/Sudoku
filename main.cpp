
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
	
	
	Sudoku_Generator generator1 = Sudoku_Generator(9);

	Matrix generated = generator1.generate();

	cout << generated << endl << endl;

	
	Sudoku_Solver solver9 = Sudoku_Solver(generated);
	solver9.solve();
	cout << solver9.get_matrix() << endl;
	
	
	


	return 0;
}