// Core/Board/Board.h
#pragma once
#include <array>
#include <vector>
#include "../../Utils/Constants.h"
using namespace std;

class Board {
private:
    array<array<int, BOARD_SIZE>, BOARD_SIZE> grid; //The sub-array represents a single column array of elements, that is one row of the board, the syntax is following the notation of template classes
    //where template<class T, size_t N>, That means it must be "array< TYPE , SIZE >"
    //What this actually means :
    //array<int, BOARD_SIZE> --> int → type of each element, BOARD_SIZE → number of elements
    //So this represent --> int[BOARD_SIZE]
    array<array<int, BOARD_SIZE>, BOARD_SIZE> original;
    array<array<vector<int>, BOARD_SIZE>, BOARD_SIZE> pencilMarks;
    //Why dynamic array used for pencil marks?
    //Purpose: A vector is a dynamic array. This allows a single cell to hold multiple values at once (e.g., "I think this cell could be a 1, 3, or 7").

public:
    // Constructor
    Board();
    
    // Cell operations
    void setCell(int row, int col, int value, bool isOriginal = false); //isOriginal exists to answer one question: “Is this value part of the original puzzle?” is Original is true when
    //initializing the puzzle. isOriginal is false when used for player input
    int getCell(int row, int col) const;
    bool isCellOriginal(int row, int col) const;
    
    // Pencil marks
    void addPencilMark(int row, int col, int value);
    const vector<int>& getPencilMarks(int row, int col) const;
    
    // Validation
    bool isValidMove(int row, int col, int value) const;
    
    // Display
    void printBoard() const;
    
    // Get grid (for Solver)
    const array<array<int, BOARD_SIZE>, BOARD_SIZE>& getGrid() const {
        return grid;
    }
    // Add this method declaration in Board.h:
    void clearBoard();
};