UCLA Winter 2017
PIC 10C Project
Author: Guoan Wang

**IMPORTANT: Using RELEASE mode to run the program is STRONGLY RECOMMENDED. Since using backtracking to generate a sudoku game takes time. (NP-Complete.)
**
		If you use DEBUG mode instead, it might take 5 seconds or more to generate a new sudoku problem. 

Brief Introduction:

This is a (9*9) sudoku game with a Graphic User Interface (GUI). The program is coded in C++ (sudoku part) and Qt (GUI part). 

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

		3. board.h + board.cpp. A widget that has 9*9 QLineEdit objects for user to enter.

			Functionality: 

			1. The QLineEdit objects automatically check whether the input is correct. (Only numbers 1-9, and backspace are accepted)

			2. When user modify the sudoku, automatically check whether there are any violations (e.g. two same number in the same row/ column/ square

				If there are, change the background color of the incorrect grids with warning color (red or pink depending on whether this grid is a pre-defined value) for 0.5 seconds.


Enjoy!