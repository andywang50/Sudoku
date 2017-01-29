# -*- coding: utf-8 -*-
"""
Created on Mon Jan 16 21:24:01 2017

@author: andy
"""

import numpy as np
import math
import random
from copy import deepcopy
#initialize sudoku here:

sudoku = np.zeros((9,9))

filename = 'sudoku2.txt'


def find_square(coord):
    row = coord[0]
    col = coord[1]
    return int(col/3)+3*int(row/3)
    
def find_row(coord):
    return coord[0]

def find_col(coord):
    return coord[1]

def find_entries_in_square(square_num):
    row_list = [int(square_num/3)*3+i for i in range(3)]
    col_list = [square_num%3*3+i for i in range(3)]
    entries = []
    for row in row_list:
        for col in col_list:
            entry = (row,col)
            entries.append(entry)
    return entries
        
def find_entries_in_row(row_num):
    return [(row_num,i) for i in range(9)]
    
def find_entries_in_col(col_num):
    return [(i,col_num) for i in range(9)]
    



def solve_init(sudoku,filename = 'empty'):
    initialized = []
    if not filename == 'empty':
        f = open(filename, 'r')
        sources = f.read().splitlines()
        f.close()
        sudoku = np.zeros((9,9))
        for i in range(9):
            for j in range(9):
                sudoku[(i,j)] = sources[i][j]
    w = open(filename+'_log.txt','w')

    known_solutions=[0]
    feasible_stack = []
    feasible = {}
    for i in range(9):
        for j in range(9):
            num = sudoku[i,j]
            entry = (i,j)
            if (num != 0):
                initialized.append((i,j))
                
    for i in range(9):
        for j in range(9):
            entry = (i,j)
            if sudoku[entry] == 0:
                feasible[entry] = set([i for i in range(1,10)])
            
    for i in range(9):
        for j in range(9):
            entry = (i,j)
            num = sudoku[entry]
            if (num != 0):
                for other_entry in find_entries_in_row(i):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                for other_entry in find_entries_in_col(j):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                for other_entry in find_entries_in_square(find_square(entry)):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                    
    feasible_set_cardinality = {}
    for entry in feasible.keys():
        if not entry in initialized:
            feasible_set = feasible[entry]
            card = len(feasible_set)
            if (card == 0):
                print('init error: no feasible solution! (ErrorCode:0)')
                return 0
            feasible_set_cardinality[entry] = card
    if len(feasible_set_cardinality) == 0:
        print('init error: already complete! (ErrorCode:2)')
        return 0
    else:   
        next_to_solve = min(feasible_set_cardinality,key = feasible_set_cardinality.get)
        feasible_stack.append(feasible)
        can_solve = solve(sudoku,next_to_solve,feasible_stack,known_solutions,w)
        if(can_solve or known_solutions[0] >0):
            print('success!')
            if known_solutions[0] == 1: 
                print('only one solution exists.')
                return 1

            else:
                print('multiple solutions exist')
                return 2
                
            #print(sudoku)
        else:
            print('init error: cannot solve! (ErrorCode:1)')
            return 0
    w.close()
def only_solve_once_init(sudoku, current_entry, banned_num = 0):
    initialized = []
    
    feasible_stack = []
    feasible = {}
    for i in range(9):
        for j in range(9):
            num = sudoku[i,j]
            entry = (i,j)
            if (num != 0):
                initialized.append((i,j))
                
    for i in range(9):
        for j in range(9):
            entry = (i,j)
            if sudoku[entry] == 0:
                feasible[entry] = set([i for i in range(1,10)])
            
    for i in range(9):
        for j in range(9):
            entry = (i,j)
            num = sudoku[entry]
            if (num != 0):
                for other_entry in find_entries_in_row(i):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                for other_entry in find_entries_in_col(j):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                for other_entry in find_entries_in_square(find_square(entry)):
                    if not other_entry in initialized:
                        feasible[other_entry].discard(num)
                     
    feasible[current_entry].discard(banned_num)
    feasible_set_cardinality = {}
    for entry in feasible.keys():
        if not entry in initialized:
            feasible_set = feasible[entry]
            card = len(feasible_set)
            if (card == 0):
                print('init error: no feasible solution! (ErrorCode:0)')
                return 0
            feasible_set_cardinality[entry] = card
    if len(feasible_set_cardinality) == 0:
        print('init error: already complete! (ErrorCode:2)')
        return 0
    else:   
        feasible_stack.append(feasible)
        can_solve = only_solve_once(sudoku,current_entry,feasible_stack,banned_num)
        if(can_solve):
            print('success!')
            return 1
            #print(sudoku)
        else:
            print('init error: cannot solve! (ErrorCode:1)')
            return 0
				
def solve(sudoku,current_entry,feasible_stack,known_solutions,log_file):
    feasible = feasible_stack[-1]
    possible_guesses = feasible[current_entry]

    possible_guesses_list = list(possible_guesses)
    random.shuffle(possible_guesses_list)
    for guess in possible_guesses_list:
        log = "  "*(len(feasible_stack)-1)+"trying "+str(current_entry) + " with " + str(guess)+"\n"
        log_file.write(log)        
        feas_copy = deepcopy(feasible)
        current_guess_feasible = True
        sudoku[current_entry] = guess;
        row = current_entry[0]
        col = current_entry[1]
        for other_entry in find_entries_in_row(row):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
        for other_entry in find_entries_in_col(col):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
        for other_entry in find_entries_in_square(find_square(current_entry)):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
                
        del feas_copy[current_entry]
                
        feasible_set_cardinality = {}
        for entry in feas_copy.keys():
            if sudoku[entry] == 0:
                feasible_set = feas_copy[entry]
                card = len(feasible_set)
                if (card == 0):
                    current_guess_feasible = False
                    break
                feasible_set_cardinality[entry] = card
        if not current_guess_feasible:
            continue
        if (len(feasible_set_cardinality) == 0):
            if (known_solutions[0] > 0):
                print(sudoku)
                log = 'Another success!\n'
                known_solutions[0] += 1
                log_file.write(log)
                return True
            else:
                print(sudoku)
                log = 'First success!\n'
                known_solutions[0] += 1
                log_file.write(log)
        else:
            next_to_solve = min(feasible_set_cardinality,key = feasible_set_cardinality.get)
            feasible_stack.append(feas_copy)
            flag = solve(sudoku,next_to_solve,feasible_stack,known_solutions,log_file)   
            if flag:
                return True
    sudoku[current_entry] = 0
    del feasible_stack[-1]
    log = "  "*(len(feasible_stack))+"pop " + str(current_entry) + "\n"
    log_file.write(log)    
    return False


solve_init(sudoku,filename)
#solve_init(sudoku)

def generate():
    sudoku = np.zeros((9,9))
    feasible_stack = []
    feasible = {}
    for i in range(9):
        for j in range(9):
            entry = (i,j)
            if sudoku[entry] == 0:
                feasible[entry] = set([i for i in range(1,10)])
            
                    
    feasible_set_cardinality = {}
    for entry in feasible.keys():					
            feasible_set = feasible[entry]
            card = len(feasible_set)
            if (card == 0):
                print('init error: no feasible solution! (ErrorCode:0)')
                return 0
            feasible_set_cardinality[entry] = card

    else:   
        next_to_solve = min(feasible_set_cardinality,key = feasible_set_cardinality.get)
        feasible_stack.append(feasible)
        only_solve_once(sudoku,next_to_solve,feasible_stack)
    entry_list = list(feasible_set_cardinality.keys())
    random.shuffle(entry_list)
    for entry in entry_list:
					
	        num = sudoku[entry]
	        sudoku[entry]= 0
	        print(num)
              							
   
	        flag = only_solve_once_init(sudoku,entry,num)
	        if flag != 0: sudoku[entry] = num
    print(sudoku)

    return sudoku
										

def only_solve_once(sudoku,current_entry,feasible_stack,banned_num = 0):
    feasible = feasible_stack[-1]
    if banned_num != 0:
								feasible[current_entry].discard(banned_num)
    possible_guesses = feasible[current_entry]    
    possible_guesses_list = list(possible_guesses)
    random.shuffle(possible_guesses_list)
    for guess in possible_guesses_list:      
        feas_copy = deepcopy(feasible)
        current_guess_feasible = True
        sudoku[current_entry] = guess;
        row = current_entry[0]
        col = current_entry[1]
        for other_entry in find_entries_in_row(row):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
        for other_entry in find_entries_in_col(col):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
        for other_entry in find_entries_in_square(find_square(current_entry)):
            if sudoku[other_entry] == 0:
                feas_copy[other_entry].discard(guess)
                
        del feas_copy[current_entry]
                
        feasible_set_cardinality = {}
        for entry in feas_copy.keys():
            if sudoku[entry] == 0:
                feasible_set = feas_copy[entry]
                card = len(feasible_set)
                if (card == 0):
                    current_guess_feasible = False
                    break
                feasible_set_cardinality[entry] = card
        if not current_guess_feasible:
            continue
        if (len(feasible_set_cardinality) == 0):						
                print(sudoku)
                
                return True
                
        else:
            next_to_solve = min(feasible_set_cardinality,key = feasible_set_cardinality.get)
            feasible_stack.append(feas_copy)
            flag = only_solve_once(sudoku,next_to_solve,feasible_stack)   
            if flag:
                return True
    sudoku[current_entry] = 0
    del feasible_stack[-1]
   
    return False

sudoku = generate()
solve_init(sudoku)