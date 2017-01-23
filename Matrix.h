#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Stack.h"
#include "Dictionary.h"
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

	friend int solve(Matrix m);

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
		Dictionary feasible_values_dict = feasible_values_dict_stack.get_last_without_pop();
		int row = e.row_coord;
		int col = e.col_coord;
		int key = row*size + col;
		return feasible_values_dict.get(key);
	}

	void remove_feasible_value_from_entry(Entry e, int num) {
		int row = e.row_coord;
		int col = e.col_coord;
		int key = row*size + col;
		Dictionary feasible_values_dict = feasible_values_dict_stack.pop();
		feasible_values_dict.remove_feasible_value_from_entry(key, num);
		feasible_values_dict_stack.push(feasible_values_dict);
		return;
	}

	void init() {
		Dictionary feasible_values_dict = Dictionary();
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				int key = row*size + col;
				std::vector<int> fv= default_feasible_values();
				feasible_values_dict.add(key, fv);
				
			}
		}
		level++;
		feasible_values_dict_stack.push(feasible_values_dict);
	}

private:
	int** sudoku;
	int size = 0;
	int level = 0;
	Stack<Dictionary> feasible_values_dict_stack;
	//std::unordered_map<int, std::vector<int>> feasible_values_dict;

};
#endif
