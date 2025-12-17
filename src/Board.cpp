// Core/Board/Board.cpp
#include "Board.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
Board::Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
            original[i][j] = EMPTY_CELL;
            pencilMarks[i][j].clear();
        }
    }
}

// Set cell value
void Board::solverSetCell(int row, int col, int value, bool isOriginal) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return;
    
    grid[row][col] = value;
    if (isOriginal) {
        original[row][col] = value;
    }
}

// Get cell value
int Board::getCell(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return EMPTY_CELL;
    }
    return grid[row][col];
}

// Check if cell is original
// Its used in the KeyboardHandler.hpp
bool Board::isCellOriginal(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    return original[row][col] != EMPTY_CELL;
}

// Check if move is valid
bool Board::isValidMove(int row, int col, int value) const {
    if (value == EMPTY_CELL) return true;
    
    // Check row
    // Ensures uniqueness in row.
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (j != col && grid[row][j] == value) return false; //grid[row][j] == value : This is the check to check if value already exists in the current row or not
    }
    
    // Check column
    // Ensures uniqueness in column.
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i != row && grid[i][col] == value) return false; //grid[row][j] == value : This is the check to check if value already exists in the current column or not
    }
    
    // Check 3x3 box
    int boxRow = row - row % BOX_SIZE;
    int boxCol = col - col % BOX_SIZE;
    
    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            int r = boxRow + i;
            int c = boxCol + j;
            if (r != row && c != col && grid[r][c] == value) return false;
        }
    }
    
    return true;
}

bool Board::userSetCell(int row, int col, int value)
{
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;
    if (grid[row][col] != 0)
        return false;

    if (userInputCount >= 35)
        return false;

    grid[row][col] = value;
    userInputCount++;
    return true;
}

void Board::clearCell(int row, int col)
{
    if (grid[row][col] != 0) {
        grid[row][col] = 0;
        userInputCount--;
    }
}

int Board::getUserInputCount() const
{
    return userInputCount;
}

bool Board::canAddMoreInputs() const
{
    return userInputCount < 35;
}


// Add this method to Board.cpp (at the end, before the last }):
void Board::clearBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
            original[i][j] = EMPTY_CELL;
            pencilMarks[i][j].clear();
        }
    }
}