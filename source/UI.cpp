#include "../include/UI.h"

using namespace std;
//ui elements
UI_Elements::UI_Elements(){}
UI_Elements::~UI_Elements(){}
void UI_Elements::draw(){}
void UI_Elements::buttonOver(int mouseX, int mouseY){};
bool UI_Elements::getStatusHovered(){}
void UI_Elements::setStatusHovered(bool status){}
//label
Label::Label(){}
Label::Label(int x, int y, string text, Color color, Color hoverColor)
{
    this->x = x;
    this->y = y;
    this->text = text;
    this->color = color;
    this->hoverColor = hoverColor;
    this->isButtonHovered = false;
}

void Label::draw()
{
    if(isButtonHovered)
    {
        drawText(x, y, text, hoverColor);
    }
    else{
        drawText(x, y, text, color);
    }
}
void Label::setStatusHovered(bool status)
{
    isButtonHovered = status;
}
//button
Button::Button(int x, int y, int width, int height, Color background, Color backgroundHover)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->background = background;
    this->background_hover = backgroundHover;
    this->isHovered = false;
}

void Button::draw()
{
    if(isHovered)
    {
        drawButton(x, y, width, height, background_hover);
    }
    else
    {
        drawButton(x, y, width, height, background);
    }
}

bool Button::getStatusHovered()
{
    return isHovered;
}
void Button::buttonOver(int mouseX, int mouseY)
{
    isHovered = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}

//UI manager
UI_Manager::UI_Manager()
{
    UI_Maps[UIObject::EXIT_BUTTON_UI] = make_unique<Button>(X_exitButton, Y_exitButton, Width_exitButton, Height_exitButton, Background_exitButton, BackgroundHover_exitButton);
    UI_Maps[UIObject::EXIT_LABEL_UI] = make_unique<Label>(X_exitLabel, Y_exitLabel, Text_exitLabel, Color_exitLabel, HoverColor_exitLabel);
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
    UI_Maps[UIObject::EXIT_LABEL_UI]->draw();

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
    UI_Maps[UIObject::EXIT_LABEL_UI]->setStatusHovered(UI_Maps[UIObject::EXIT_BUTTON_UI]->getStatusHovered());
}

//all destructor
UI_Manager::~UI_Manager(){}
Button::~Button(){}
Label::~Label(){}