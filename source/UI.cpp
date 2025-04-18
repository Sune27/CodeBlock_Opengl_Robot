#include "../include/UI.h"

using namespace std;
//ui elements
UI_Elements::UI_Elements(){}
UI_Elements::~UI_Elements(){}
void UI_Elements::draw(){};

//button
Button::Button(int x, int y, int width, int height, Color background, Color backgroundHover)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->background = background;
    this->background_hover = backgroundHover;
}

//UI manager
UI_Manager::UI_Manager()
{
    UI_Maps[UIObject::EXIT_BUTTON_UI] = make_unique<Button>(X_exitButton, Y_exitButton, Width_exitButton, Height_exitButton, Background_exitButton, BackgroundHover_exitButton);
}