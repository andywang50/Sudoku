#include "Matrix.h"


std::ostream & operator<<(std::ostream & os, const Entry & e)
{
	os << e.toString();
	return os;
}

std::ostream& operator << (std::ostream& os, const Matrix& m) {
	for (int i = 0; i < m.size; i++) {
		for (int j = 0; j < m.size; j++) {
			int num = m.sudoku[i][j];
			if (num < 10) 
				os << m.sudoku[i][j];
			else {
				switch (num) {
					case 10: os << "A"; break;
					case 11: os << "B"; break;
					case 12: os << "C"; break;
					case 13: os << "D"; break;
					case 14: os << "E"; break;
					case 15: os << "F"; break;
				}

			}
		}
		os << std::endl;
	}
	return os;
}

Matrix::Matrix() {
	size = 0;
	level = 0;
	init();
}

Matrix::Matrix(int N) {
	if (N != 4 || N != 9 || N != 16) {
		N = 9;
	}
	size = N;
	sudoku = new int*[size];
	for (int i = 0; i < size; i++) {
		sudoku[i] = new int[size];
		for (int j = 0; j < size; j++) {
			sudoku[i][j] = 0;
		}
	}
	init();
}

Matrix::Matrix(const Matrix& b) {
	size = b.size;
	this->feasible_values_dict_stack = b.feasible_values_dict_stack;
	sudoku = new int*[size];
	for (int i = 0; i < size; i++) {
		sudoku[i] = new int[size];
		for (int j = 0; j < size; j++) {
			sudoku[i][j] = b.sudoku[i][j];
		}
	}
	init();
}

Matrix& Matrix::operator = (const Matrix& b) {
	if (this != &b) {
		size = b.size;
		feasible_values_dict_stack = b.feasible_values_dict_stack;
		sudoku = new int*[size];
		for (int i = 0; i < size; i++) {
			sudoku[i] = new int[size];
			for (int j = 0; j < size; j++) {
				sudoku[i][j] = b.sudoku[i][j];
			}
		}
	}
	init();
	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i < size; i++) {
		delete[] sudoku[i];
	}
	delete[] sudoku;
}

std::vector<Entry> Matrix::get_row(int row) const
{
	std::vector<Entry> row_list;
	for (int i = 0; i < size; i++) {
		row_list.push_back(Entry(row, i));
	}
	return row_list;
}

std::vector<Entry> Matrix::get_row(Entry coord) const
{

	return get_row(coord.row_coord);
}

std::vector<Entry> Matrix::get_col(int col) const
{
	std::vector<Entry> col_list;
	for (int i = 0; i < size; i++) {
		col_list.push_back(Entry(i, col));
	}
	return col_list;
}

std::vector<Entry> Matrix::get_col(Entry coord) const
{
	return get_col(coord.col_coord);
}

std::vector<Entry> Matrix::get_square(Entry coord) const
{
	std::vector<Entry> square_list;
	int x = coord.row_coord / 3 *3;
	int y = coord.col_coord / 3 *3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Entry newEntry = Entry(x+i,y+j);
			square_list.push_back(newEntry);
		}
	}
	return square_list;
}
