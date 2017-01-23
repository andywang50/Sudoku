#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


template <typename Container>
struct container_hash {
	std::size_t operator()(Container const& c) const {
		return boost::hash_range(c.begin(), c.end());

	}
};
class Matrix;
class Entry {
public:
	int DEFAULT_INIT_COORD = -1;

	friend class Matrix;
	Entry() {
		row_coord = DEFAULT_INIT_COORD;
		col_coord = DEFAULT_INIT_COORD;

	}
	Entry(const int& x, const int& y) : row_coord(x), col_coord(y) {}
	Entry(const Entry& b) {
		row_coord = b.row_coord;
		col_coord = b.col_coord;
	}
		
	Entry& operator = (Entry b) {
		this->swap(b);
		return *this;
	}

	void swap(Entry& b) {
		std::swap(row_coord, b.row_coord);
		std::swap(col_coord, b.col_coord);
	}
	~Entry() {};

	std::string toString() const { return "(" + std::to_string(this->row_coord) + "," + std::to_string(this->col_coord) + ")"; }

	friend std::ostream& operator << (std::ostream& os, const Entry& e);
	bool operator == (const Entry& b) const { return row_coord == b.row_coord && col_coord == b.col_coord; }
	bool operator != (const Entry& b) const { return !(*this == b); }
private:
	int row_coord;
	int col_coord;
};

class Matrix {
public:
	friend std::ostream& operator << (std::ostream& os, const Matrix& m);
	Matrix();
	Matrix(int N);

	Matrix(const Matrix& b);
	Matrix& operator = (const Matrix& b);

	~Matrix();

	int& operator ()(int row, int column){	return sudoku[row][column];	}
	int operator ()(int row, int column) const {return sudoku[row][column];}

	int& operator ()(Entry coord) { return sudoku[coord.row_coord][coord.col_coord]; }
	int operator ()(Entry coord) const { return sudoku[coord.row_coord][coord.col_coord]; }

	std::vector<Entry> get_row(int row) const;
	std::vector<Entry> get_row(Entry coord) const;

	std::vector<Entry> get_col(int col) const;
	std::vector<Entry> get_col(Entry coord)const;

	std::vector<Entry> get_square(Entry coord)const;

	std::vector<int> default_feasible_values() {
		std::vector<int> fv;
		for (int i = 1; i <= size; i++) fv.push_back(i);
		return fv;
	}

	std::vector<int> get_feasbile_values(Entry e) const {
		int row = e.row_coord;
		int col = e.col_coord;
		int key = row*size + col;
		std::unordered_map<int, std::vector<int>>::const_iterator got = feasible_values_dict.find(key);
		std::vector<int> v;
		if (got == feasible_values_dict.end())
			std::cout << "Entry(" << row << "," << col << ") " << "not found\n";
		else
			v = got->second;

		return v;
	}

	void remove_feasible_value_from_entry(Entry e, int num) {
		int row = e.row_coord;
		int col = e.col_coord;
		int key = row*size + col;
		std::vector<int>* v_ptr = &(feasible_values_dict[key]);

 		auto it = std::find(v_ptr->begin(), v_ptr->end(), num);
		if (it != v_ptr->end()) {
			v_ptr->erase(it);
		}
	}

	void init() {
	
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				int key = row*size + col;
				std::vector<int> fv= default_feasible_values();
				feasible_values_dict[key] = fv;
				
			}
		}
		
	}

private:
	int** sudoku;
	int size = 0;

	
	std::unordered_map<int, std::vector<int>> feasible_values_dict;

};
#endif
