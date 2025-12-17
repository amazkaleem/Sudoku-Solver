// Core/Solver/Generator.h
#pragma once
#include <array>
#include <random> //Provides --> std::mt19937 (Mersenne Twister) , High-quality randomness for puzzle generation 👉 Essential — Sudoku generation must be random.
#include "../Board/Board.h"
#include "Solver.h"
using namespace std; //Works fine --> Better avoided in headers, but acceptable for learning

//👉 This is a dependency chain: Board ← Solver ← Generator
class Generator {
private:
    static mt19937 rng; //mt19937 is a high-quality random number engine, static makes it shared across the class, and rng provides consistent randomness for Sudoku generation. This is the single source of randomness for:
    // 1) Shuffling rows & columns
    // 2) Filling diagonal boxes
    // 3) Choosing which cells to remove
    // 4) Randomizing generation order

    /*
    Without static:
        Each Generator object would have its own RNG.
    But:
        You never create Generator objects
        Generator is used like a utility class
    */
    
    static void shuffleBoard(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid); //If you generate a board deterministically:
    // You’ll keep getting the same solution
    // Puzzles will look repetitive
    //shuffleBoard() ensures:
    // High randomness
    // Visual variety
    // No repeated patterns

    static void fillDiagonalBoxes(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid);
    //Quickly and safely fills the 3 diagonal 3×3 boxes.
    //These boxes are: (0,0)   (3,3)   (6,6)
    //Why diagonal boxes specifically?
    //Diagonal 3×3 boxes:
    //1) Do not share rows or columns with each other
    //2) Can be filled independently
    //This guarantees:
    //1) No conflicts
    //2) No backtracking
    //3) Fast setup

    /*
    Starting from an empty grid and backtracking everything is:
    much slower, much deeper recursion
    Diagonal filling: reduces problem size, makes generation efficient
    */

    /*
    Conceptual analogy : “Lay strong foundations before building the house.”
    */

    static bool fillRemaining(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int row, int col);
    //Completes the rest of the Sudoku grid using backtracking.
    // This is the generator’s solver.

    
public:
    static void generateFullBoard(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid);
    static void createPuzzle(Board& board, int difficulty);
    
    // Helper functions
    static void removeNumbers(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int cellsToRemove); //Purpose --> Removes values (sets to EMPTY_CELL) --> Controls difficulty --> More removed cells = harder puzzle.
    static int countSolutions(array<array<int, BOARD_SIZE>, BOARD_SIZE> grid); //Counts how many valid solutions a puzzle has
};