#include "Matrix.h"



bool Matrix::solve() {
	bool solved = false;

	// remember to initialize. i.e. remove all feasible values if sudoku[i][j] != 0;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int num = sudoku[row][col];
			if (num != 0) {
				Entry current_entry = Entry(row, col);
				this->remove_all_feasible_values_from_entry(current_entry);
				for (Entry other_entry : this->get_row(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;
					int other_entry_key = other_entry_row*size + other_entry_col;
					if (sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
				for (Entry other_entry : this->get_col(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;
					int other_entry_key = other_entry_row*size + other_entry_col;
					if (sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
				for (Entry other_entry : this->get_square(current_entry)) {
					int other_entry_row = other_entry.row_coord;
					int other_entry_col = other_entry.col_coord;
					int other_entry_key = other_entry_row*size + other_entry_col;
					if (sudoku[other_entry_row][other_entry_col] == 0) {
						remove_feasible_value_from_entry(other_entry, num);
					}
				}
			}
		}
	}
	Entry next_to_update = get_next_to_update();
	if (next_to_update == this->Sign_of_Failure) {
		std::cout << "Initialize error: seems no feasible solution in the first place" << std::endl;
		solved= false;
	}
	else if (next_to_update == this->Sign_of_Success) {
		std::cout << "Initialize error: seems completed already" << std::endl;
		solved =  true;
	}
	else {
		solved= solve(next_to_update);
	}
	return solved;
}

Entry Matrix::get_next_to_update() const {
	int next = 0;
	Dictionary current_dict = feasible_values_dict_stack.get_last_without_pop();
	int min_possible_values = size + 1;
	int next_to_update_key = -1;
	Entry next_to_update = Entry();
	bool feasible = true;
	bool finished = true;
	std::vector<int> rows = default_feasible_values();
	std::random_shuffle(rows.begin(), rows.end());
	for (int row : rows) {
		int x = row - 1;
		std::vector<int> cols = default_feasible_values();
		std::random_shuffle(cols.begin(), cols.end());
		for (int col : cols) {
			int y = col - 1;
			if (sudoku[x][y] == 0) {
				finished = false;
				int key = x*size + y;
				int current_num_guesses_of_this_entry = current_dict.get_num_guesses(key);
				if (current_num_guesses_of_this_entry == 0) {
					feasible = false;
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

	if (finished) next_to_update = Sign_of_Success;

	return next_to_update;
}

bool Matrix::solve(Entry current_entry) {
	int row = current_entry.row_coord;
	int col = current_entry.col_coord;
	int key = row*size + col;
	Dictionary old_dict = feasible_values_dict_stack.get_last_without_pop();
	std::vector<int> possible_guesses = old_dict.get(key);
	std::random_shuffle(possible_guesses.begin(), possible_guesses.end());
	for (int guess : possible_guesses) {
		Dictionary new_dict = old_dict;
		bool current_guess_feasible = true;
		sudoku[row][col] = guess;
		for (Entry other_entry : this->get_row(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (sudoku[other_entry_row][other_entry_col] == 0){
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_col(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		for (Entry other_entry : this->get_square(current_entry)) {
			int other_entry_row = other_entry.row_coord;
			int other_entry_col = other_entry.col_coord;
			int other_entry_key = other_entry_row*size + other_entry_col;
			if (sudoku[other_entry_row][other_entry_col] == 0) {
				new_dict.remove_feasible_value_from_entry(other_entry_key, guess);
			}
		}
		new_dict.remove_all_feasible_values_from_entry(key);
		this->feasible_values_dict_stack.push(new_dict);
		Entry next_to_update = get_next_to_update();

		// test this method to keep accord with the python file.
		this->feasible_values_dict_stack.pop();

		if (next_to_update == this->Sign_of_Failure) {
			continue;
		}
		else if (next_to_update == this->Sign_of_Success) {
			return true;
		}
		else {
			this->feasible_values_dict_stack.push(new_dict);
			bool flag= solve(next_to_update);
			if (flag) return flag;
			//else feasible_values_dict_stack.pop();
		}

	}
	sudoku[row][key] = 0;
	this->feasible_values_dict_stack.pop();
	return false;

}