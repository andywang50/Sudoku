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
	
}

Matrix& Matrix::operator = (Matrix b) {
	swap(b);
	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i < size; i++) {
		//std::cout << "Matrix Destructor called\n";
		delete[] sudoku[i];
	}
	delete[] sudoku;
}

Matrix::Matrix(std::string filename)
{
	std::ifstream myfile;
	myfile.open(filename);
	std::string line;
	int file_indicated_size = -1;
	int row = 0;
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			if (file_indicated_size == -1) {
				file_indicated_size = atoi(line.c_str());
				size = file_indicated_size;
				delete[] sudoku;			
				sudoku = new int*[size];
				for (int i = 0; i < size; i++) {
					sudoku[i] = new int[size];
					for (int j = 0; j < size; j++) {
						sudoku[i][j] = 0;
					}
				}
			}
			else {
				for (int col = 0; col < size; col++) {
					int num = line[col] - '0';
					sudoku[row][col] = num;

				}
				row++;
			}
		}
		myfile.close();
		init();
	}
	else {
		std::cout << "unable" << std::endl;
	}
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

std::vector<int> Matrix::default_feasible_values() const {
	std::vector<int> fv;
	for (int i = 1; i <= size; i++) fv.push_back(i);
	return fv;
}

std::vector<int> Matrix::get_feasbile_values(Entry e) const
{
	Dictionary feasible_values_dict = feasible_values_dict_stack.get_last_without_pop();
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	return feasible_values_dict.get(key);
}

void Matrix::remove_feasible_value_from_entry(Entry e, int num)
{
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	Dictionary feasible_values_dict = feasible_values_dict_stack.pop();
	feasible_values_dict.remove_feasible_value_from_entry(key, num);
	feasible_values_dict_stack.push(feasible_values_dict);
	return;
}

void Matrix::remove_all_feasible_values_from_entry(Entry e)
{
	int row = e.row_coord;
	int col = e.col_coord;
	int key = row*size + col;
	Dictionary feasible_values_dict = feasible_values_dict_stack.pop();
	feasible_values_dict.remove_all_feasible_values_from_entry(key);
	feasible_values_dict_stack.push(feasible_values_dict);
	return;
}

void Matrix::init()
{
	Dictionary feasible_values_dict = Dictionary();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int key = row*size + col;
			std::vector<int> fv = default_feasible_values();
			feasible_values_dict.add(key, fv);

		}
	}
	
	feasible_values_dict_stack.push(feasible_values_dict);
}
