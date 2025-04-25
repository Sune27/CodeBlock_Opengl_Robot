#include "../include/UI.h"

using namespace std;
//ui elements
UI_Elements::UI_Elements(){disable = false;}
UI_Elements::~UI_Elements(){}
void UI_Elements::draw(){}
void UI_Elements::buttonOver(int mouseX, int mouseY){}
bool UI_Elements::getStatusHovered(){}
void UI_Elements::setStatusHovered(bool status){}
bool UI_Elements::getDisable()
{
    return disable;
}
void UI_Elements::setDisable(bool status)
{
    disable = status;
}
void UI_Elements::setPosition(int x, int y){}
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
Button::Button(){}
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
    if(isDisable == true)
    {
        drawX(x, y, width, height, background);
    }
}
void Button::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
bool Button::getStatusHovered()
{
    return isHovered;
}
void Button::buttonOver(int mouseX, int mouseY)
{
    isHovered = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}
void Button::setDisable(bool status)
{
    isDisable = status;
}
bool Button::getDisable()
{
    return isDisable;
}

//Symbol
Symbol::Symbol(){}
Symbol::Symbol(int x, int y, int width, int height, string type)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->type = type;
    this->color = WHITE;
    this->hoverColor = GRAY;
    this->isButtonHovered = false;
}
void Symbol::setStatusHovered(bool status)
{
    isButtonHovered = status;
}
void Symbol::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Symbol::draw()
{
    Color currentColor = (isButtonHovered)?hoverColor:color;
    if(type == "LEFT_ARROW")
        drawArrow(x, y, width, height, 1, currentColor);
    else if(type == "UP_ARROW")
        drawArrow(x, y, width, height, 2, currentColor);
    else if(type == "RIGHT_ARROW")
        drawArrow(x, y, width, height, 3, currentColor);
    else if(type == "DOWN_ARROW")
        drawArrow(x, y, width, height, 4, currentColor);
    else if(type == "RIGHT_HAND" || type == "LEFT_HAND")
        drawOpenU(x, y, width, height, currentColor);

}

//UI manager
UI_Manager::UI_Manager()
{
    UI_Maps[UIObject::EXIT_BUTTON_UI] = make_unique<Button>(X_exitButton, Y_exitButton, Width_exitButton, Height_exitButton, Background_exitButton, BackgroundHover_exitButton);
    UI_Maps[UIObject::LEFT_ARROW_BUTTON_UI] = make_unique<Button>(X_leftArrowButton, Y_leftArrowButton, Width_leftArrowButton, Height_leftArrowButton, Background_leftArrowButton, BackgroundHover_leftArrowButton);
    UI_Maps[UIObject::RIGHT_ARROW_BUTTON_UI] = make_unique<Button>(X_rightArrowButton, Y_rightArrowButton, Width_rightArrowButton, Height_rightArrowButton, Background_rightArrowButton, BackgroundHover_rightArrowButton);
    UI_Maps[UIObject::UP_ARROW_BUTTON_UI] = make_unique<Button>(X_upArrowButton, Y_upArrowButton, Width_upArrowButton, Height_upArrowButton, Background_upArrowButton, BackgroundHover_upArrowButton);
    UI_Maps[UIObject::DOWN_ARROW_BUTTON_UI] = make_unique<Button>(X_downArrowButton, Y_downArrowButton, Width_downArrowButton, Height_downArrowButton, Background_downArrowButton, BackgroundHover_downArrowButton);
    UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI] = make_unique<Button>(X_rightHandButton, Y_rightHandButton, Width_rightHandButton, Height_rightHandButton, Background_rightHandButton, BackgroundHover_rightHandButton);
    UI_Maps[UIObject::LEFT_HAND_BUTTON_UI] = make_unique<Button>(X_leftHandButton, Y_leftHandButton, Width_leftHandButton, Height_leftHandButton, Background_leftHandButton, BackgroundHover_leftHandButton);

    UI_Maps[UIObject::EXIT_LABEL_UI] = make_unique<Label>(X_exitLabel, Y_exitLabel, Text_exitLabel, Color_exitLabel, HoverColor_exitLabel);

    UI_Maps[UIObject::LEFT_ARROW_SYMBOL_UI] = make_unique<Symbol>(X_leftArrowSymbol, Y_leftArrowSymbol, Width_leftArrowSymbol, Height_leftArrowSymbol, Type_leftArrowSymbol);
    UI_Maps[UIObject::RIGHT_ARROW_SYMBOL_UI] = make_unique<Symbol>(X_rightArrowSymbol, Y_rightArrowSymbol, Width_rightArrowSymbol, Height_rightArrowSymbol, Type_rightArrowSymbol);
    UI_Maps[UIObject::UP_ARROW_SYMBOL_UI] = make_unique<Symbol>(X_upArrowSymbol, Y_upArrowSymbol, Width_upArrowSymbol, Height_upArrowSymbol, Type_upArrowSymbol);
    UI_Maps[UIObject::DOWN_ARROW_SYMBOL_UI] = make_unique<Symbol>(X_downArrowSymbol, Y_downArrowSymbol, Width_downArrowSymbol, Height_downArrowSymbol, Type_downArrowSymbol);
    UI_Maps[UIObject::RIGHT_HAND_SYMBOL_UI] = make_unique<Symbol>(X_rightHandSymbol, Y_rightHandSymbol, Width_rightHandSymbol, Height_rightHandSymbol, Type_rightHandSymbol);
    UI_Maps[UIObject::LEFT_HAND_SYMBOL_UI] = make_unique<Symbol>(X_leftHandSymbol, Y_leftHandSymbol, Width_leftHandSymbol, Height_leftHandSymbol, Type_leftHandSymbol);
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
    UI_Maps[UIObject::LEFT_ARROW_BUTTON_UI]->draw();
    UI_Maps[UIObject::RIGHT_ARROW_BUTTON_UI]->draw();
    UI_Maps[UIObject::UP_ARROW_BUTTON_UI]->draw();
    UI_Maps[UIObject::DOWN_ARROW_BUTTON_UI]->draw();
    UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->draw();
    UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->draw();

    UI_Maps[UIObject::EXIT_LABEL_UI]->draw();
    UI_Maps[UIObject::LEFT_ARROW_SYMBOL_UI]->draw();
    UI_Maps[UIObject::RIGHT_ARROW_SYMBOL_UI]->draw();
    UI_Maps[UIObject::UP_ARROW_SYMBOL_UI]->draw();
    UI_Maps[UIObject::DOWN_ARROW_SYMBOL_UI]->draw();
    UI_Maps[UIObject::RIGHT_HAND_SYMBOL_UI]->draw();
    UI_Maps[UIObject::LEFT_HAND_SYMBOL_UI]->draw();
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
    UI_Maps[UIObject::LEFT_ARROW_BUTTON_UI]->buttonOver(mouseX, mouseY);
    UI_Maps[UIObject::RIGHT_ARROW_BUTTON_UI]->buttonOver(mouseX, mouseY);
    UI_Maps[UIObject::UP_ARROW_BUTTON_UI]->buttonOver(mouseX, mouseY);
    UI_Maps[UIObject::DOWN_ARROW_BUTTON_UI]->buttonOver(mouseX, mouseY);
    UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->buttonOver(mouseX, mouseY);
    UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->buttonOver(mouseX, mouseY);

    UI_Maps[UIObject::EXIT_LABEL_UI]->setStatusHovered(UI_Maps[UIObject::EXIT_BUTTON_UI]->getStatusHovered());

    UI_Maps[UIObject::LEFT_ARROW_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::LEFT_ARROW_BUTTON_UI]->getStatusHovered());
    UI_Maps[UIObject::RIGHT_ARROW_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::RIGHT_ARROW_BUTTON_UI]->getStatusHovered());
    UI_Maps[UIObject::UP_ARROW_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::UP_ARROW_BUTTON_UI]->getStatusHovered());
    UI_Maps[UIObject::DOWN_ARROW_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::DOWN_ARROW_BUTTON_UI]->getStatusHovered());
    UI_Maps[UIObject::RIGHT_HAND_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->getStatusHovered());
    UI_Maps[UIObject::LEFT_HAND_SYMBOL_UI]->setStatusHovered(UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->getStatusHovered());

}

//all destructor
UI_Manager::~UI_Manager(){}
Button::~Button(){}
Label::~Label(){}
Symbol::~Symbol(){}
