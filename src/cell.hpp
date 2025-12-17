#pragma once
#include <raylib.h>

class Cell {
private:
    int row;
    int col;
    Rectangle bounds;
    int value;        // 0 = empty
    bool fixed;       // true if part of original puzzle

public:
    Cell(int r, int c, Rectangle rect, int val = 0, bool isFixed = false);

    void setValue(int v);
    int  getValue() const;

    int getCol() const;
    int getRow() const;

    bool isFixedCell() const;

    void Draw(Font font, bool selected = false) const;
};
