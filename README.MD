UCLA Winter 2017
PIC 10C Project
Author: Guoan Wang

**IMPORTANT: Using RELEASE mode to run the program is STRONGLY RECOMMENDED. Since using backtracking to generate a sudoku game takes time. (NP-Complete.)
**

		If you use DEBUG mode instead, it might take (more than) 5 seconds or more to generate a new sudoku problem. 

Brief Introduction:

This is a (9*9) sudoku game with a Graphic User Interface (GUI). The program is coded in C++ (sudoku part) and Qt (GUI part). 

The sudoku part is in the root directory. Needed files are:

	1. Dictionary.h, Dictionary.cpp.
	2. Matrix.h, Matrix.cpp.
	3. Node.h
	4. Stack.h
	5. Sudoku_Generator.h, Sudoku_Generator.cpp
	6. Sudoku_Solver.h, Sudoku_Solver.cpp
	
The GUI part is in the PIC10CPorject folder. Needed files are:

	1. PIC10CPorject/main.cpp  IMPORTANT: Use your QT to start from this main.cpp.
	2. PIC10CPorject/board.h, board.cpp
	3. PIC10CPorject/mainwindow.h, mainwindow.cpp
	4. PIC10CPorject/mainwindow.ui
	5. PIC10CPorject/PIC10CProject.pro
	6. PIC10CPorject/PIC10CProject.pro.user

I will introduce two parts respectively:

Background: (sudoku part)

	Files.

		1. Node.h + Stack.h. Self-implemented Stack. (Used for backtracking)

		2. Matrix.cpp + Matrix.h. 2-dim array that stores the numbers in each entry.

		3. Sudoku_Solver.h + Sudoku._Solver.cpp. Sudoku solver based on the method of backtracking and constraint programming.

		4. Dictionary. Self-implemented class to store the feasible values for each entry. (uses unordered_map)

		5. Sudoku_Generator.h + Sudoku_Generator.cpp. Generate a new sudoku game with unique solution. Method:

			a) Start from an empty 9*9 matrix.

			b) Solve this in a random style. Get a randomly complete sudoku.

			c) Repeat the following until the sudoku does not have unique solution anymore.

				1) randomly choose a nonempty entry and remove its number.

				2) solve the new sudoku, with additional constraint that the newly-deleted entry cannot use its original number.

				3) if it turns out that it can be solved, put this number back and jump out of the loop.
		
			
GUI part: (Qt)

	Files. (In the subfolder "PIC10CProject")

		1. main.cpp. Main function to initiate the game.

		2. mainwindow.h + mainwindow.cpp. Game board. with buttons in it.

			Buttons: 

			1. Start. Start a new game.

			2. Check. Check whether the solution is correct.

			3. Restart. Retry this game.

			4. Quit. Quit the game.

			5. Solve. Display the answer of this game.
			
			6. Hint. Compare the contemporary matrix with the solution matrix, two cases:
				a) By so far, if all the non-empty entries are the same as the solution matrix. Give a hint for the next step: Insert an empty entry with the correct value
				
				b) By so far, if there are any entered values that are different from the solution. Highlight these wrong entries (warning), and highlight violations (row, column, square containing same values).

		3. board.h + board.cpp. A widget that has 9*9 QLineEdit objects for user to enter.

			Functionality: 

			1. The QLineEdit objects automatically check whether the input is correct. (Only numbers 1-9, and backspace are accepted)

			2. When user modify the sudoku, automatically check whether there are any violations (e.g. two same number in the same row/ column/ square

				If there are, change the background color of the incorrect grids with warning color (red or pink depending on whether this grid is a pre-defined value) for 0.5 seconds.


Enjoy!