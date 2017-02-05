#ifndef SUDOKU_SOLVER_H
#define SUDOkU_SOLVER_H

#include "Matrix.h"
#include "Stack.h"
#include "Dictionary.h"

class Sudoku_Solver {

public:
	friend class Sudoku_Generator;
	Sudoku_Solver();
	Sudoku_Solver(Matrix m);
	Sudoku_Solver(int n);
	Sudoku_Solver(const Sudoku_Solver& b);
	Sudoku_Solver& operator = (Sudoku_Solver b);
	virtual ~Sudoku_Solver();
	//const Entry Sign_of_Success = Entry(Entry::SIGN_OF_SUCCESS, Entry::SIGN_OF_SUCCESS);
	const Entry Sign_of_Failure = Entry(Entry::DEFAULT_INIT_COORD, Entry::DEFAULT_INIT_COORD);

	bool solve();
	bool solve(Entry current_entry, std::ofstream& fout);
	bool solve_no_log_init();
	bool solve_no_log(Entry current_entry);
	void update_status();
	Entry get_next_to_update() const;
	void printlogpush(std::ofstream& fout, Entry current_entry, int guess);
	void printlogpop(std::ofstream& fout, Entry current_entry);

	std::vector<Entry> get_row(int row) const;
	std::vector<Entry> get_row(Entry coord) const;

	std::vector<Entry> get_col(int col) const;
	std::vector<Entry> get_col(Entry coord)const;

	std::vector<Entry> get_square(Entry coord)const;

	std::vector<int> default_feasible_values() const;

	std::vector<int> get_feasbile_values(Entry e) const;

	void remove_feasible_value_from_entry(Entry e, int num);
	void remove_all_feasible_values_from_entry(Entry e);

	Matrix get_matrix() const;

	void init();
private:
	int size = 0;
	Stack<Dictionary> feasible_values_dict_stack;
	Matrix matrix;
	std::vector<int> dfv = std::vector<int>();

	void swap(Sudoku_Solver& b) {
		std::swap(feasible_values_dict_stack, b.feasible_values_dict_stack);
		std::swap(size, b.size);
		std::swap(matrix, b.matrix);
		std::swap(dfv, b.dfv);
	}

};

#endif 