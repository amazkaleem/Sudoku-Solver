// main.cpp - Testing Generator
#include <iostream>
#include "Core/Board/Board.h"
#include "Core/Solver/Solver.h"
#include "Core/Solver/Generator.h"
using namespace std;

void displayMenu() {
    cout << "\n=================================\n";
    cout << "     SUDOKU GENERATOR TEST\n";
    cout << "=================================\n";
    cout << "1. Generate Easy Puzzle (30 cells removed)\n";
    cout << "2. Generate Medium Puzzle (40 cells removed)\n";
    cout << "3. Generate Hard Puzzle (50 cells removed)\n";
    cout << "4. Solve Current Puzzle\n";
    cout << "5. Exit\n";
    cout << "=================================\n";
    cout << "Choice: ";
}

int main() {
    cout << "=================================\n";
    cout << "     SUDOKU PUZZLE GENERATOR\n";
    cout << "     Abdul Nafeh - CSC241\n";
    cout << "=================================\n\n";
    
    Board board;
    Solver solver;
    int choice = 0;
    
    while (choice != 5) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\nGenerating Easy Puzzle...\n";
                Generator::createPuzzle(board, 0);
                cout << "Easy Puzzle Generated!\n";
                board.printBoard();
                break;
            }
            
            case 2: {
                cout << "\nGenerating Medium Puzzle...\n";
                Generator::createPuzzle(board, 1);
                cout << "Medium Puzzle Generated!\n";
                board.printBoard();
                break;
            }
            
            case 3: {
                cout << "\nGenerating Hard Puzzle...\n";
                Generator::createPuzzle(board, 2);
                cout << "Hard Puzzle Generated!\n";
                board.printBoard();
                break;
            }
            
            case 4: {
                cout << "\nSolving Puzzle...\n";
                if (solver.solve(board)) {
                    cout << "Solution Found!\n";
                    board.printBoard();
                } else {
                    cout << "No Solution Found!\n";
                }
                break;
            }
            
            case 5: {
                cout << "\nExiting Program. Goodbye!\n";
                break;
            }
            
            default: {
                cout << "\nInvalid choice! Please try again.\n";
                break;
            }
        }
    }
    
    return 0;
}