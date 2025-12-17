// UI/UIConstants.h - UI-specific constants
#pragma once

namespace UIConstants {
    // Window settings
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Sudoku Game - OOP Project";
    
    // Board rendering
    const int BOARD_MARGIN = 50;
    const int CELL_SIZE = 46;
    const int BOARD_SIZE = CELL_SIZE * 9;
    const int BOARD_X = (SCREEN_WIDTH - BOARD_SIZE) / 2;
    const int BOARD_Y = 30;
    
    // UI elements
    const int BUTTON_WIDTH = 120;
    const int BUTTON_HEIGHT = 40;
    const int BUTTON_MARGIN = 20;
    const int FONT_SIZE_NORMAL = 20;
    const int FONT_SIZE_LARGE = 30;
    const int FONT_SIZE_SMALL = 16;
}