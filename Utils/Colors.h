// Utils/Colors.h
#pragma once
#include "raylib/include/raylib.h"  // For Color type

namespace UIColors {
    // Background colors
    const Color BACKGROUND = { 25, 25, 35, 255 };      // Dark blue-gray
    const Color PANEL_BG = { 40, 40, 50, 220 };        // Slightly lighter
    
    // Grid colors
    const Color GRID_LINE_THIN = { 80, 80, 100, 255 };  // Light gray-blue
    const Color GRID_LINE_THICK = { 120, 120, 140, 255 };// Medium gray-blue
    
    // Cell colors
    const Color CELL_BACKGROUND = { 30, 30, 40, 255 };   // Dark cell bg
    const Color CELL_SELECTED = { 60, 80, 120, 100 };    // Blue highlight
    const Color CELL_HIGHLIGHT = { 70, 70, 90, 80 };     // Gray highlight
    
    // Number colors
    const Color NUMBER_ORIGINAL = { 220, 220, 240, 255 };// White-ish
    const Color NUMBER_USER = { 180, 200, 255, 255 };    // Light blue
    const Color NUMBER_ERROR = { 255, 100, 100, 255 };   // Red
    const Color PENCIL_MARK = { 150, 150, 170, 180 };    // Light gray
    
    // UI colors
    const Color TEXT_PRIMARY = { 240, 240, 255, 255 };   // White
    const Color TEXT_SECONDARY = { 180, 180, 200, 255 }; // Light gray
    const Color BUTTON_NORMAL = { 60, 80, 120, 255 };    // Blue
    const Color BUTTON_HOVER = { 80, 100, 140, 255 };    // Light blue
    const Color BUTTON_PRESSED = { 40, 60, 100, 255 };   // Dark blue
}