#include "Sudoku_Solver.h"

void Sudoku_Solver::update_status() {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int num = matrix.sudoku[row][col];
			if (num != 0) {
				Entry current_entry = Entry(row, col);
				this->remove_all_feasible_values_from_entry(current_entry);
				for (Entry other_entry : this->get_row(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;					
					if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
				for (Entry other_entry : this->get_col(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;
					if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
				for (Entry other_entry : this->get_square(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;
					if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
			}
		}
	}
}

Sudoku_Solver::Sudoku_Solver():size(0),
matrix(Matrix()),
feasible_values_dict_stack(Stack<Dictionary>())
{}

Sudoku_Solver::Sudoku_Solver(Matrix m) : size(m.size),matrix(m),feasible_values_dict_stack(Stack<Dictionary>())
{
	init();
}

Sudoku_Solver::Sudoku_Solver(int n) {
	size = n;
	matrix = Matrix(n);
	feasible_values_dict_stack = Stack<Dictionary>();
	init();
}

Sudoku_Solver::Sudoku_Solver(const Sudoku_Solver & b)
{
	size = b.size;
	matrix = b.matrix;
	feasible_values_dict_stack = b.feasible_values_dict_stack;
	init();
}

Sudoku_Solver & Sudoku_Solver::operator=(Sudoku_Solver b)
{
	swap(b);
	return *this;
}

Sudoku_Solver::~Sudoku_Solver()
{
}

bool Sudoku_Solver::solve() {
	bool solved = false;
	std::ofstream fout;
	fout.open("log.txt");
	if (matrix.is_complete()) return true;
	// remember to initialize. i.e. remove all feasible values if sudoku[i][j] != 0;
	update_status();
	Entry next_to_update = get_next_to_update();
	if (next_to_update == this->Sign_of_Failure) {
		std::cout << "Initialize error: seems no feasible solution in the first place" << std::endl;
		solved= false;
	}
	else {
		solved= solve(next_to_update,fout);
	}
	return solved;
}

Entry Sudoku_Solver::get_next_to_update() const {
	Dictionary current_dict = feasible_values_dict_stack.get_last_without_pop();
	int min_possible_values = size + 1;
	Entry next_to_update = Sign_of_Failure;
	bool feasible = true;
	std::vector<int> rows = dfv;
	std::random_shuffle(rows.begin(), rows.end());
	for (int row : rows) {
		int x = row - 1;
		std::vector<int> cols = dfv;
		std::random_shuffle(cols.begin(), cols.end());
		for (int col : cols) {
			int y = col - 1;
			if (matrix.sudoku[x][y] == 0) {
				int key = x*size + y;
				int current_num_guesses_of_this_entry = current_dict.get_num_guesses(key);
				if (current_num_guesses_of_this_entry == 0) {
					feasible = false;
					next_to_update = Sign_of_Failure;
					break;
				}
				else {
					if (current_num_guesses_of_this_entry < min_possible_values) {
						min_possible_values = current_num_guesses_of_this_entry;
						next_to_update = Entry(x, y);
					}
				}
			}
			
		}
		if (!feasible) break;
	}


	return next_to_update;
}

void Sudoku_Solver::printlogpush(std::ofstream & fout, Entry current_entry, int guess)
{
	int l = this->feasible_values_dict_stack.get_length();
	for (int i = 0; i < l; i++) fout << " ";
	fout << "trying ( " << current_entry.row_coord << "," << current_entry.col_coord << " ) with guess " << guess << "." <<std::endl;
}

void Sudoku_Solver::printlogpop(std::ofstream & fout, Entry current_entry)
{
	int l = this->feasible_values_dict_stack.get_length();
	for (int i = 0; i < l; i++) fout << " ";
	fout << "pop ( " << current_entry.row_coord << "," << current_entry.col_coord << " )." << std::endl;
}

bool Sudoku_Solver::solve(Entry current_entry, std::ofstream& fout) {

	int row = current_entry.row_coord;
	int col = current_entry.col_coord;
	int key = row*size + col;
	Dictionary old_dict = feasible_values_dict_stack.get_last_without_pop();
	std::vector<int> possible_guesses = old_dict.get(key);
	std::random_shuffle(possible_guesses.begin(), possible_guesses.end());
	for (int guess : possible_guesses) {
		printlogpush(fout, current_entry, guess);
		Dictionary new_dict = old_dict;
		matrix.sudoku[row][col] = guess;
		
		if (matrix.is_complete()) return true;
		for (Entry other_entry : this->get_row(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0){
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_col(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_square(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		new_dict.remove_all_feasible_values_from_entry(key);
		feasible_values_dict_stack.push(new_dict);
		Entry next_to_update = get_next_to_update();

		// test this method to keep accord with the python file.
		// this->feasible_values_dict_stack.pop();

		if (next_to_update == this->Sign_of_Failure) {
			this->feasible_values_dict_stack.pop();
			continue;
		}
		else {
			//this->feasible_values_dict_stack.push(new_dict);
			bool flag= solve(next_to_update, fout);
			if (flag) return flag;
			else feasible_values_dict_stack.pop();
		}

	}
	matrix.sudoku[row][col] = 0;
	printlogpop(fout, current_entry);
	//this->feasible_values_dict_stack.pop();
	return false;

}

bool Sudoku_Solver::solve_no_log_init()
{
	bool solved = false;
	if (matrix.is_complete()) return true;
	// remember to initialize. i.e. remove all feasible values if sudoku[i][j] != 0;
	update_status();
	Entry next_to_update = get_next_to_update();
	//std::cout << next_to_update << std::endl;
	if (next_to_update == this->Sign_of_Failure) {
		solved = false;
	}
	else {
		solved = solve_no_log(next_to_update);
	}
	return solved;
}
bool Sudoku_Solver::solve_no_log(Entry current_entry)
{

	int row = current_entry.row_coord;
	int col = current_entry.col_coord;
	int key = row*size + col;
	Dictionary old_dict = feasible_values_dict_stack.get_last_without_pop();
	std::vector<int> possible_guesses = old_dict.get(key);
	std::random_shuffle(possible_guesses.begin(), possible_guesses.end());
	for (int guess : possible_guesses) {
		
		Dictionary new_dict = old_dict;
		matrix.sudoku[row][col] = guess;

		if (matrix.is_complete()) return true;
		for (Entry other_entry : this->get_row(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_col(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_square(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (matrix.sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		new_dict.remove_all_feasible_values_from_entry(key);
		feasible_values_dict_stack.push(new_dict);
		Entry next_to_update = get_next_to_update();

		// test this method to keep accord with the python file.
		// this->feasible_values_dict_stack.pop();

		if (next_to_update == this->Sign_of_Failure) {
			this->feasible_values_dict_stack.pop();
			continue;
		}
		else {
			//this->feasible_values_dict_stack.push(new_dict);
			bool flag = solve_no_log(next_to_update);
			if (flag) return flag;
			else feasible_values_dict_stack.pop();
		}

	}
	matrix.sudoku[row][col] = 0;
	//this->feasible_values_dict_stack.pop();
	return false;

}


std::vector<Entry> Sudoku_Solver::get_row(int row) const
{
	std::vector<Entry> row_list;
	for (int i = 0; i < size; i++) {
		row_list.push_back(Entry(row, i));
	}
	return row_list;
}

std::vector<Entry> Sudoku_Solver::get_row(Entry coord) const
{

	return get_row(coord.row_coord);
}

std::vector<Entry> Sudoku_Solver::get_col(int col) const
{
	std::vector<Entry> col_list;
	for (int i = 0; i < size; i++) {
		col_list.push_back(Entry(i, col));
	}
	return col_list;
}

std::vector<Entry> Sudoku_Solver::get_col(Entry coord) const
{
	return get_col(coord.col_coord);
}

std::vector<Entry> Sudoku_Solver::get_square(Entry coord) const
{
	int a = (int) sqrt(size);
	std::vector<Entry> square_list;
	int x = coord.row_coord / a * a;
	int y = coord.col_coord / a * a;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			Entry newEntry = Entry(x + i, y + j);
			square_list.push_back(newEntry);
		}
	}
	return square_list;
}
/*
std::vector<int> Sudoku_Solver::default_feasible_values() const {
	std::vector<int> fv;
	for (int i = 1; i <= size; i++) fv.push_back(i);
	return fv;
}
*/
std::vector<int> Sudoku_Solver::get_feasbile_values(Entry e) const
{
	Dictionary feasible_values_dict = feasible_values_dict_stack.get_last_without_pop();
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	return feasible_values_dict.get(key);
}

void Sudoku_Solver::remove_feasible_value_from_entry(Entry e, int num)
{
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	Dictionary feasible_values_dict = feasible_values_dict_stack.pop();
	feasible_values_dict.remove_feasible_value_from_entry(key, num);
	feasible_values_dict_stack.push(feasible_values_dict);
	return;
}

void Sudoku_Solver::remove_all_feasible_values_from_entry(Entry e)
{
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	Dictionary feasible_values_dict = feasible_values_dict_stack.pop();
	feasible_values_dict.remove_all_feasible_values_from_entry(key);
	feasible_values_dict_stack.push(feasible_values_dict);
	return;
}

Matrix Sudoku_Solver::get_matrix() const
{
	return this->matrix;
}

void Sudoku_Solver::init()
{
	for (int i = 1; i <= size; i++) dfv.push_back(i);
	Dictionary feasible_values_dict = Dictionary();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int key = row*size + col;
			feasible_values_dict.add(key, dfv);

		}
	}
	feasible_values_dict_stack = Stack<Dictionary>();
	feasible_values_dict_stack.push(feasible_values_dict);
}
