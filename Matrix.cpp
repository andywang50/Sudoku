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
				os << num;
			else {
				switch (num) {
					case 10: os << "A"; break;
					case 11: os << "B"; break;
					case 12: os << "C"; break;
					case 13: os << "D"; break;
					case 14: os << "E"; break;
					case 15: os << "F"; break;
					case 16: os << "G"; break;
				}

			}
		}
		os << std::endl;
	}
	return os;
}

Matrix::Matrix() {
	size = 0;
	try {
		sudoku = nullptr;
	
	}
	catch (std::exception e) {
		std::cout << "Error in default constructor.\n";
	}
}

Matrix::Matrix(int N) {
	if (N != 4 && N != 9 && N != 16) {
		N = 9;
	}
	size = N;
	try {
		sudoku = new int*[size];
	}
	catch (std::exception e) {
		delete[] sudoku;
		sudoku = nullptr;
		std::cout << "Error in constructor, step 1 " << std::endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		try {
			sudoku[i] = new int[size];
		}
		catch (std::exception e) {
			for (int j = 0; j <= i; j++) {
				delete[] sudoku[j];
				sudoku[j] = nullptr;

			}
			std::cout << "Error in constructor, step 2, loop " << i << std::endl;
			delete[] sudoku;
			sudoku = nullptr;

			return;
		}
		for (int j = 0; j < size; j++) {
			sudoku[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& b) {
	size = b.size;
	try {
		sudoku = new int*[size];
	}
	catch (std::exception e) {
		delete[] sudoku;
		sudoku = nullptr;
		std::cout << "Error in copy constructor, step 1 " << std::endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		try {
			sudoku[i] = new int[size];
		}
		catch (std::exception e) {
			for (int j = 0; j <= i; j++) {
				delete[] sudoku[j];
				sudoku[j] = nullptr;

			}
			std::cout << "Error in copy constructor, step 2, loop " << i << std::endl;
			delete[] sudoku;
			sudoku = nullptr;

			return;
		}
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
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			//std::cout << "Matrix Destructor called\n";
			if (sudoku[i] != nullptr) {
				delete[] sudoku[i];
				sudoku[i] = nullptr;
			}
		}
	}
	if (sudoku != nullptr) {
		delete[] sudoku;
		sudoku = nullptr;
	}
	
}

Matrix::Matrix(std::string filename)
{
	std::ifstream myfile;
	try {
		myfile.open(filename);
	}
	catch (std::exception e) {
		std::cout << "Error in file reading." << std::endl;
	}
	std::string line;
	int file_indicated_size = -1;
	int row = 0;
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			if (file_indicated_size == -1) {
				file_indicated_size = atoi(line.c_str());
				size = file_indicated_size;
				try {
					sudoku = new int*[size];
				}
				catch (std::exception e) {
					delete[] sudoku;
					sudoku = nullptr;
					std::cout << "Error in string constructor, step 1 " << std::endl;
					return;
				}
				for (int i = 0; i < size; i++) {
					try {
						sudoku[i] = new int[size];
					}
					catch (std::exception e) {
						for (int j = 0; j <= i; j++) {
							delete[] sudoku[j];
							sudoku[j] = nullptr;

						}
						std::cout << "Error in copy constructor, step 2, loop " << i << std::endl;
						delete[] sudoku;
						sudoku = nullptr;
						return;
					}
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
	}
	else {
		std::cout << "unable" << std::endl;
	}
	

}

bool Matrix::is_complete() const {
	bool finished = true;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (sudoku[i][j] == 0) {
				finished = false;
				break;
			}
		}
		if (!finished) break;
	}
	//std::cout << "Finished\n";
	return finished;
}

