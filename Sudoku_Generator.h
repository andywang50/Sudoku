#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H
#include "Sudoku_Solver.h"


class Sudoku_Generator {
public:
    double FRACT_OF_ENTRIES_NEEDED_TO_BE_REMOVED_LOWER_THRESHOLD =0.2; //can stop removing entries only if more than x entries has already be removed.
    double FRACT_OF_ENTRIES_NEEDED_TO_BE_REMOVED_UPPER_THRESHOLD = 0.5; //must stop removing entries if more than x entries has already be removed.
	int NUMBER_OF_ENTRIES_FAILED_TO_REMOVE_THRESHOLD =3; // can stop removing entries only if we've failed to remove y entries or more.
	int NUMBER_OF_ENTRIES_FAILED_TO_REMOVE_CONSECUTIVELY_THRESHOLD = 2;
	Sudoku_Generator();
	Sudoku_Generator(int n);
	Sudoku_Generator(const Sudoku_Generator& b);
	Sudoku_Generator& operator = (Sudoku_Generator b);
	virtual ~Sudoku_Generator();

	Matrix generate();


private:
	void swap(Sudoku_Generator& b) {
		std::swap(size, b.size);
		std::swap(matrix, b.matrix);
	}
	Matrix matrix;
	int size = 0;
};

#endif
