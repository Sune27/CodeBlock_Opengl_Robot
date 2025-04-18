#include "../include/UI.h"

using namespace std;
//ui elements
UI_Elements::UI_Elements(){}
UI_Elements::~UI_Elements(){}
void UI_Elements::draw(){}
void UI_Elements::buttonOver(int mouseX, int mouseY){};

//button
Button::Button(int x, int y, int width, int height, Color background, Color backgroundHover)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->background = background;
    this->background_hover = backgroundHover;
    this->is_hovered = false;
}

void Button::draw()
{
    if(is_hovered)
    {
        drawButton(x, y, width, height, background_hover);
    }
    else
    {
        drawButton(x, y, width, height, background);
    }
}

void Button::buttonOver(int mouseX, int mouseY)
{
    is_hovered = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}

//UI manager
UI_Manager::UI_Manager()
{
    UI_Maps[UIObject::EXIT_BUTTON_UI] = make_unique<Button>(X_exitButton, Y_exitButton, Width_exitButton, Height_exitButton, Background_exitButton, BackgroundHover_exitButton);
}

void UI_Manager::draw()
{
    glDisable(GL_DEPTH_TEST);
	// Lưu lại projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); // Thiết lập orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	// Vẽ các thành phần UI 2D
    UI_Maps[UIObject::EXIT_BUTTON_UI]->draw();

	// Khôi phục projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void UI_Manager::checkAllButtonOver(int mouseX, int mouseY)
{
    UI_Maps[UIObject::EXIT_BUTTON_UI]->buttonOver(mouseX, mouseY);
}
UI_Manager::~UI_Manager(){}
Button::~Button(){}