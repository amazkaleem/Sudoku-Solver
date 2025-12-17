#include "Cell.hpp"

Cell::Cell(int r, int c, Rectangle rect, int val, bool isFixed)
    : row(r), col(c), bounds(rect), value(val), fixed(isFixed) {}

void Cell::setValue(int v) {
    if (!fixed) value = v;
}

int Cell::getValue() const {
    return value;
}

int Cell::getCol() const {
    return col;
}

int Cell::getRow() const {
    return row;
}

bool Cell::isFixedCell() const {
    return fixed;
}

void Cell::Draw(Font font, bool selected) const {
    // Background
    if (selected) {
        DrawRectangleRec(bounds, Color{240, 223, 188, 255});
    } else {
        DrawRectangleRec(bounds, Color{254, 255, 237, 255});
    }

    // Border
    DrawRectangleLinesEx(bounds, 1, BLACK);

    // Number
    if (value != 0) {
        const char text[2] = { char('0' + value), '\0' };

        Vector2 textSize = MeasureTextEx(font, text, 24, 0);

        float x = bounds.x + (bounds.width  - textSize.x) / 2;
        float y = bounds.y + (bounds.height - textSize.y) / 2;

        DrawTextEx(
            font,
            text,
            { x, y },
            30,
            0,
            BLACK // Can be replaced with "fixed ? DARKBLUE : BLACK" in future
        );
    }
}
