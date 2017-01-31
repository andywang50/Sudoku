#include "Sudoku_Generator.h"
#include <iostream>
Sudoku_Generator::Sudoku_Generator()
{
	size = 0;
	matrix = Matrix();

}

Sudoku_Generator::Sudoku_Generator(int n)
{
	size = n;
	matrix = Matrix(n);
}

Sudoku_Generator::Sudoku_Generator(const Sudoku_Generator & b)
{
	size = b.size;
	matrix = b.matrix;
}

Sudoku_Generator & Sudoku_Generator::operator=(Sudoku_Generator b)
{
	swap(b);
	return *this;
}

Sudoku_Generator::~Sudoku_Generator()
{
}

Matrix Sudoku_Generator::generate() {
	if (size == 0) {
		std::cout << "Error! size = 0!\n";
		return Matrix();
	}

	Sudoku_Solver solver = Sudoku_Solver(size);
	solver.solve_no_log_init();
	matrix = solver.get_matrix();

	std::vector<Entry> entry_vector = std::vector<Entry>();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			Entry current_entry = Entry(i, j);
			entry_vector.push_back(current_entry);
		}
	}
	
	std::random_shuffle(entry_vector.begin(), entry_vector.end());
	
	int cannot_remove_count = 0;
	int removed_count = 0;
	int cannot_remove_consecutive_count = 0;
	for (Entry current_entry : entry_vector) {
		int num = matrix(current_entry);
		matrix(current_entry) = 0;
		solver = Sudoku_Solver(matrix);
		//std::cout << count << ":\n";
		//std::cout << newsolver.matrix << std::endl;
		solver.remove_feasible_value_from_entry(current_entry, num);
		bool flag = solver.solve_no_log_init();
		//std::cout << count << ":\n";
		//std::cout << newsolver.matrix << std::endl;
		if (flag) {
			matrix(current_entry) = num;
			cannot_remove_count++;
			cannot_remove_consecutive_count++;
		}
		else {
			removed_count++;
			cannot_remove_consecutive_count = 0;
		}
		if ((removed_count >= NUMBER_OF_ENTRIES_NEEDED_TO_BE_REMOVED_UPPER_THRESHOLD
			|| (cannot_remove_count >= NUMBER_OF_ENTRIES_FAILED_TO_REMOVE_THRESHOLD 
			|| cannot_remove_consecutive_count >= NUMBER_OF_ENTRIES_FAILED_TO_REMOVE_CONSECUTIVELY_THRESHOLD)
			&& removed_count >= NUMBER_OF_ENTRIES_NEEDED_TO_BE_REMOVED_LOWER_THRESHOLD)) break;
		
	}
	return matrix;
}
