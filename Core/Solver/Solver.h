// Core/Solver/Solver.h
#pragma once
#include <array>
#include "../Board/Board.h"
using namespace std;

class Solver {
private:
    bool solveBacktracking(array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid);
    bool findEmptyCell(const array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int& row, int& col);
    bool isValidPlacement(const array<array<int, BOARD_SIZE>, BOARD_SIZE>& grid, int row, int col, int num);
    
public:
    Solver() {}
    bool solve(Board& board);
    bool isSolvable(Board& board);
};