#pragma once
#include <raylib.h>

class Button
{
protected:
    Texture2D texture;
    Vector2 position;

public:
    Button(const char* imagePath, Vector2 imagePosition, float scale);
    virtual ~Button();          // IMPORTANT: virtual destructor
    void Draw();        // virtual for polymorphism
    bool isPressed(Vector2 mousePos, bool mousePressed);
};
