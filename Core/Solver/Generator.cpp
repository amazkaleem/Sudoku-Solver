// Core/Solver/Generator.cpp
#include "Generator.h"
#include <algorithm>
#include <chrono>
using namespace std;

// Initialize random number generator
mt19937 Generator::rng(chrono::steady_clock::now().time_since_epoch().count());

// Generate a complete Sudoku board
void Generator::generateFullBoard(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid) {
    // Fill with zeros
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
        }
    }
    
    // Fill diagonal boxes (they are independent)
    fillDiagonalBoxes(grid);
    
    // Fill remaining cells
    fillRemaining(grid, 0, BOX_SIZE);  //The Generator's solver. User input can be checked by 
    //comparing with this function's generated solution
    
    // Shuffle the board
    shuffleBoard(grid);
}

// Fill the 3 diagonal boxes
void Generator::fillDiagonalBoxes(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid) {
    for (int box = 0; box < BOARD_SIZE; box += BOX_SIZE) {
        // Create numbers 1-9
        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffle(numbers.begin(), numbers.end(), rng);
        
        // Fill the box
        int index = 0;
        for (int i = 0; i < BOX_SIZE; i++) {
            for (int j = 0; j < BOX_SIZE; j++) {
                grid[box + i][box + j] = numbers[index++];
            }
        }
    }
}

// Fill remaining cells using backtracking
bool Generator::fillRemaining(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int row, int col) {
    // If we've reached the end
    if (row == BOARD_SIZE - 1 && col == BOARD_SIZE) {
        return true;
    }
    
    // Move to next row if at end of column
    if (col == BOARD_SIZE) {
        row++;
        col = 0;
    }
    
    // Skip if cell is already filled (diagonal boxes)
    if (grid[row][col] != EMPTY_CELL) {
        return fillRemaining(grid, row, col + 1);
    }
    
    // Try numbers 1-9
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(numbers.begin(), numbers.end(), rng);
    
    for (int num : numbers) {
        // Check if number can be placed
        bool valid = true;
        
        // Check row
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (grid[row][j] == num) {
                valid = false;
                break;
            }
        }
        
        // Check column
        if (valid) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (grid[i][col] == num) {
                    valid = false;
                    break;
                }
            }
        }
        
        // Check box
        if (valid) {
            int boxRow = row - row % BOX_SIZE;
            int boxCol = col - col % BOX_SIZE;
            
            for (int i = 0; i < BOX_SIZE; i++) {
                for (int j = 0; j < BOX_SIZE; j++) {
                    if (grid[boxRow + i][boxCol + j] == num) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }
        }
        
        if (valid) {
            grid[row][col] = num;
            
            if (fillRemaining(grid, row, col + 1)) {
                return true;
            }
            
            grid[row][col] = EMPTY_CELL;
        }
    }
    
    return false;
}

// Shuffle the board (swap rows/columns within boxes)
void Generator::shuffleBoard(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid) {
    uniform_int_distribution<int> dist(0, BOX_SIZE - 1);
    
    // Swap rows within the same box group
    for (int box = 0; box < BOARD_SIZE; box += BOX_SIZE) {
        for (int i = 0; i < BOX_SIZE; i++) {
            int swapWith = dist(rng);
            for (int j = 0; j < BOARD_SIZE; j++) {
                swap(grid[box + i][j], grid[box + swapWith][j]);
            }
        }
    }
    
    // Swap columns within the same box group
    for (int box = 0; box < BOARD_SIZE; box += BOX_SIZE) {
        for (int i = 0; i < BOX_SIZE; i++) {
            int swapWith = dist(rng);
            for (int j = 0; j < BOARD_SIZE; j++) {
                swap(grid[j][box + i], grid[j][box + swapWith]);
            }
        }
    }
}

// Remove numbers to create a puzzle
void Generator::removeNumbers(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int cellsToRemove) {
    uniform_int_distribution<int> dist(0, BOARD_SIZE - 1);
    
    while (cellsToRemove > 0) {
        int row = dist(rng);
        int col = dist(rng);
        
        if (grid[row][col] != EMPTY_CELL) {
            int backup = grid[row][col];
            grid[row][col] = EMPTY_CELL;
            
            // Check if puzzle still has unique solution
            array<array<int, BOARD_SIZE>, BOARD_SIZE> tempGrid = grid;
            Solver solver;
            Board tempBoard;
            
            // Create temporary board
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    tempBoard.setCell(i, j, tempGrid[i][j], true);
                }
            }
            
            if (solver.isSolvable(tempBoard)) {
                cellsToRemove--;
            } else {
                // Restore if not solvable
                grid[row][col] = backup;
            }
        }
    }
}

// Create puzzle with specified difficulty
void Generator::createPuzzle(Board& board, int difficulty) {
    array<array<int, BOARD_SIZE>, BOARD_SIZE> grid;
    
    // Generate full board
    generateFullBoard(grid);
    
    // Determine how many cells to remove based on difficulty
    int cellsToRemove;
    switch (difficulty) {
        case 0: cellsToRemove = 30; break; // Easy
        case 1: cellsToRemove = 40; break; // Medium
        case 2: cellsToRemove = 50; break; // Hard
        default: cellsToRemove = 40; break;
    }
    
    // Remove numbers
    removeNumbers(grid, cellsToRemove);
    
    // Set board with puzzle
    board.clearBoard();
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j] != EMPTY_CELL) {
                board.setCell(i, j, grid[i][j], true);
            }
        }
    }
}