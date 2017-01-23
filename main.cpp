#include <iostream>
#include <vector>
#include "Stack.h"
#include "Matrix.h"
#include <unordered_map>
#include <map>
using namespace std;

int main() {
	/*
	Stack<int> test = Stack<int>();
	test.push(1);
	test.push(2);

	
	Stack<int> test1 = Stack<int>(test);
	

	Stack<int> test2 = Stack<int>();
	test2 = test1;


	while (test.get_length() > 0) {
		cout << test.pop() << endl;

	}
	while (test1.get_length() > 0) {
		cout << test1.pop() << endl;

	}
	while (test2.get_length() > 0) {
		cout << test2.pop() << endl;

	}

	Stack<int> test3 = Stack<int>(test2);
	*/
	
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
	Matrix sudoku3 = sudoku;
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
	
	/*
	unordered_map<char, vector<int>> test;
	test['a'] = {1,2,3};
	test['b'] = { 2,3,4 };
	vector<int>* v = &test['a'];
	auto it = std::find(v->begin(), v->end(), 2);
	if (it != v->end())
		v->erase(it);
	cout << "A" << endl;
	*/
	/*
	Matrix sudoku = Matrix(9);
	Entry test_entry = Entry(4, 4);
	vector<Entry> row_list = sudoku.get_row(test_entry);
	vector<Entry> col_list = sudoku.get_col(test_entry);
	vector<Entry> square_list = sudoku.get_square(test_entry);

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
	*/

	return 0;
}