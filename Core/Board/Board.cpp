// Core/Board/Board.cpp
#include "Board.h"
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
void Board::setCell(int row, int col, int value, bool isOriginal) {
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
bool Board::isCellOriginal(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    return original[row][col] != EMPTY_CELL;
}

// Add pencil mark
void Board::addPencilMark(int row, int col, int value) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return;
    if (value < 1 || value > 9) return;
    
    vector<int>& marks = pencilMarks[row][col];
    
    // Check if already exists
    for (int mark : marks) {
        if (mark == value) return;
    }
    
    marks.push_back(value);
}

// Get pencil marks
const vector<int>& Board::getPencilMarks(int row, int col) const {
    static vector<int> empty;
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return empty;
    }
    return pencilMarks[row][col];
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

// Print board
void Board::printBoard() const {
    cout << "Sudoku Board:\n";
    cout << "  0 1 2 3 4 5 6 7 8\n";
    cout << "  -----------------\n";
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << "|";
        for (int j = 0; j < BOARD_SIZE; j++) {
            int val = grid[i][j];
            if (val == EMPTY_CELL) cout << ". ";
            else cout << val << " ";
        }
        cout << "\n";
    }
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