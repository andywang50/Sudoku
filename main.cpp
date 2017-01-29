
#include "Stack.h"
#include "Matrix.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <ctime>        // std::time
#include <cstdlib> 

using namespace std;

int main() {
	srand(unsigned(std::time(0)));

	Matrix sudoku = Matrix(9);
	cout << "0" << endl;
	cout << sudoku << endl << endl;

	cout << "1" << endl;
	Matrix sudoku1 = Matrix();
	cout << sudoku1 << endl << endl;

	cout << "2" << endl;
	Matrix sudoku2(sudoku);
	cout << sudoku2 << endl << endl;

	cout << "3" << endl;
	Matrix sudoku3= Matrix(9);
	sudoku3 = sudoku;
	cout << sudoku3 << endl << endl;
	
	Entry testEntry1 = Entry(4, 4);
	Entry testEntry2 = Entry(4, 5);

	sudoku.remove_feasible_value_from_entry(testEntry1, 1);

	std::vector<int> sudoku_4_4 = sudoku.get_feasbile_values(testEntry1);
	std::vector<int> sudoku_4_5 = sudoku.get_feasbile_values(testEntry2);
	std::vector<int> sudoku1_4_4 = sudoku1.get_feasbile_values(testEntry1);
	std::vector<int> sudoku2_4_4 = sudoku2.get_feasbile_values(testEntry1);
	std::vector<int> sudoku3_4_4 = sudoku3.get_feasbile_values(testEntry1);

	for (int num : sudoku_4_4) cout << num << " ";
	cout << endl;
	
	for (int num : sudoku_4_5) cout << num << " ";
	cout << endl;

	for (int num : sudoku1_4_4) cout << num << " ";
	cout << endl; 

	for (int num : sudoku2_4_4) cout << num << " ";
	cout << endl;

	for (int num : sudoku3_4_4) cout << num << " ";
	cout << endl;

	Matrix sudoku0 = Matrix(9);
	Entry test_entry = Entry(4, 4);
	vector<Entry> row_list = sudoku0.get_row(test_entry);
	vector<Entry> col_list = sudoku0.get_col(test_entry);
	vector<Entry> square_list = sudoku0.get_square(test_entry);

	cout << "Testing row" << endl;
	for (Entry e : row_list) cout << e;
	cout << endl;
	cout << "Testing col" << endl;
	for (Entry e : col_list) cout << e;
	cout << endl;
	cout << "Testing sqr" << endl;
	for (Entry e : square_list) cout << e;
	cout << endl;

	Entry test_entry1 = Entry(4, 4);
	cout << (test_entry1 == test_entry) << endl;

	test_entry1 = test_entry;
	cout << (test_entry1 == test_entry) << endl;

	Entry test_entry2 = Entry(test_entry);
	cout << (test_entry1 == test_entry2) << endl;

	Entry test_entry3 = Entry(4, 5);
	cout << (test_entry3 != test_entry) << endl;

	test_entry3 = Entry(5, 4);
	cout << (test_entry3 != test_entry) << endl;

	test_entry3 = Entry(5, 5);
	cout << (test_entry3 != test_entry) << endl;
	
	
	Matrix sudoku_file = Matrix("sudoku100.txt");


	cout << sudoku_file.solve() << endl;
	cout << sudoku_file << endl;
	return 0;
}