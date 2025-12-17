#include <raylib.h>
#include <iostream>
#include "button.hpp"
#include "cell.hpp"
#include "Board.hpp"
#include "Constants.hpp"
#include "GridRenderer.hpp"
#include "UIConstants.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "SelectionHandler.hpp"
#include "Solver.hpp"

//Don't change the name of the folder, "Sudoku". It causes issues with compiler Error: ${filebasename} cannot be resolved
// UI states for menu
enum class MenuState {
    MAIN_MENU,
    SOLVER_BOARD
};



int main()
{
    InitWindow(800, 600, "RayLib Sudoku Menu");
    SetTargetFPS(60);


    Board board;
    GridRenderer gridRenderer(
        UIConstants::BOARD_X,
        UIConstants::BOARD_Y,
        UIConstants::CELL_SIZE
    );

    SelectionHandler selection;
    KeyboardHandler keyboardHandler(selection);
    MouseHandler mouseHandler(selection, gridRenderer);
    Solver solvePuzzle;


    std::vector<Cell> cells;


    //Fonts
    Font timesFont = LoadFontEx("Fonts/times.ttf", 64, 0, 0);

    // Background
    Texture2D background = LoadTexture("Graphics/background.png");
    Texture2D gameBackground = LoadTexture("Graphics/solveBackground.png");

    // Main menu buttons
    Button playButton  { "Graphics/PLAY.png", {150, 350}, 0.65f };
    Button solveButton  { "Graphics/SOLVER.png", {450, 450}, 0.65f };

    bool exit = false;
    bool solved = false;

    MenuState menuState = MenuState::MAIN_MENU;

    while (!WindowShouldClose() && !exit)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // ---------------- INPUT ----------------
        switch (menuState)
        {
            case MenuState::MAIN_MENU:
            {
                if (playButton.isPressed(mousePosition, mousePressed))
                {
                    menuState = MenuState::SOLVER_BOARD;
                    cells.clear();
                    for (int row = 0; row < 9; row++) {
                        for (int col = 0; col < 9; col++) {
                            Rectangle rect = gridRenderer.getCellRect(row, col);
                            int value = board.getCell(row, col);
                            bool fixed = value != 0;
                            cells.emplace_back(row, col, rect, value, fixed);
                        }
                    }
                }
                break;
            }

            case MenuState::SOLVER_BOARD:
            {
                mouseHandler.handleMouseClick();
                keyboardHandler.handleKeyboardInput(board);
                if (!solved && solveButton.isPressed(mousePosition, mousePressed)) {
                    solvePuzzle.solve(board);
                    solved = true;
                }
                break;

            }

            default:
                break;
        }

        // ---------------- DRAW ----------------
        BeginDrawing();
        ClearBackground(BLACK);
        
        if (menuState == MenuState::MAIN_MENU)
        {
            DrawTexture(background, 0, 0, WHITE);
            playButton.Draw();
        }
        else if (menuState == MenuState::SOLVER_BOARD)
        {
            DrawTextEx(
                timesFont,
                TextFormat("Inputs: %d / 35", board.getUserInputCount()),
                Vector2{ 50.0f, 50.0f },
                24.0f,          // font size
                1.0f,           // spacing
                BLACK
            );
            DrawTexture(gameBackground, 0, 0, WHITE);
            solveButton.Draw();
            gridRenderer.draw();   // draw grid lines

            for (Cell& cell : cells) {
                int r = cell.getRow();
                int c = cell.getCol();
                cell.setValue(board.getCell(r, c));

                bool isSelected =
                    selection.hasSelectedCell() &&
                    selection.getSelectedRow() == cell.getRow() &&
                    selection.getSelectedCol() == cell.getCol();
                gridRenderer.draw();
                cell.Draw(timesFont, isSelected);       // draw numbers, highlights
            }
        }

        EndDrawing();
    }

    UnloadFont(timesFont);
    CloseWindow();
    return 0;
}
