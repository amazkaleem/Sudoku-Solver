// Core/Solver/Solver.cpp
#include "Solver.hpp"
#include <iostream>
using namespace std;

// Backtracking algorithm
bool Solver::solveBacktracking(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid) {
    int row, col;
    
    // Find empty cell
    if (!findEmptyCell(grid, row, col)) {
        return true; // Puzzle solved
    }
    
    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isValidPlacement(grid, row, col, num)) {
            grid[row][col] = num;
            
            if (solveBacktracking(grid)) {
                return true;
            }
            
            // Backtrack
            grid[row][col] = EMPTY_CELL;
        }
    }
    
    return false; // No solution
}

// Find first empty cell
bool Solver::findEmptyCell(const array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int& row, int& col) {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (grid[row][col] == EMPTY_CELL) {
                return true;
            }
        }
    }
    return false;
}

// Check if number can be placed
bool Solver::isValidPlacement(const array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int row, int col, int num) {
    // Check row
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (grid[row][j] == num) return false;
    }
    
    // Check column
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (grid[i][col] == num) return false;
    }
    
    // Check 3x3 box
    int boxRow = row - row % BOX_SIZE;
    int boxCol = col - col % BOX_SIZE;
    
    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            if (grid[boxRow + i][boxCol + j] == num) return false;
        }
    }
    
    return true;
}

// Solve the board
bool Solver::solve(Board& board) {
    array<array<int, BOARD_SIZE>, BOARD_SIZE> grid = board.getGrid();
    
    if (solveBacktracking(grid)) {
        // Update board with solution
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board.getCell(i, j) == EMPTY_CELL) {
                    board.solverSetCell(i, j, grid[i][j], false);
                }
            }
        }
        return true;
    }
    
    return false;
}