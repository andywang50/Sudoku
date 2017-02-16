#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Stack.h"
#include <fstream>
#include <ctime>        // std::time
#include <cstdlib> 
#include <algorithm>
class Matrix;
class Entry {
public:

	static const int DEFAULT_INIT_COORD = -1;
	static const int SIGN_OF_SUCCESS = -2;
	friend class Matrix;
	friend class Sudoku_Solver;
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
	virtual ~Entry() {};

	std::string toString() const { return "(" + std::to_string(this->row_coord) + "," + std::to_string(this->col_coord) + ")"; }

	friend std::ostream& operator << (std::ostream& os, const Entry& e);
	bool operator == (const Entry& b) const { return row_coord == b.row_coord && col_coord == b.col_coord; }
	bool operator != (const Entry& b) const { return !(*this == b); }

    int get_row() const{return row_coord;}
    int get_col() const{return col_coord;}
private:
	int row_coord;
	int col_coord;
};

class Matrix {
public:

	friend class Sudoku_Solver;
	friend class Sudoku_Generator;
	bool is_complete() const;

	


	friend std::ostream& operator << (std::ostream& os, const Matrix& m);
	Matrix();
	Matrix(int N);

	Matrix(const Matrix& b);
	Matrix& operator = (Matrix b);

	virtual ~Matrix();

	Matrix(std::string filename);

	int& operator ()(int row, int column){	return sudoku[row][column];	}
	int operator ()(int row, int column) const {return sudoku[row][column];}

	int& operator ()(Entry coord) { return sudoku[coord.row_coord][coord.col_coord]; }
	int operator ()(Entry coord) const { return sudoku[coord.row_coord][coord.col_coord]; }

    int get_size() const;

private:
	int** sudoku = nullptr;
	int size = 0;
	void swap(Matrix& b) {
		std::swap(size, b.size);
		std::swap(sudoku, b.sudoku);

	}
	//std::unordered_map<int, std::vector<int>> feasible_values_dict;



};
#endif
