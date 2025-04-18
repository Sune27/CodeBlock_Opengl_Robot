#include "../include/UserInterface.h"

using namespace std;

Button::Button()
{
	isHover = false;
}
void Button::setValue(float x, float y, float width, float height, Color background, Color backgroundHover, Color textColor)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->background = background;
	this->backgroundHover = backgroundHover;
	this->textColor = textColor;
}
void Button::draw(const char* text)
{
	if(isHover)
		drawButton(x, y, width, height, backgroundHover);
	else
		drawButton(x, y, width, height, background);
}
bool Button::isMouseOver(int mouseX, int mouseY)
{

	isHover = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
	return isHover;
}

UIManager::UIManager()
{
    cout << "Constructor UI class" << endl;
	exitButton.setValue
	(
		10, 10, 100, 100,
		RED, YELLOW, BLACK
	);
	userManualButton.setValue
	(
		200, 200, 100, 100,
		BLUE, DARK_BLUE, WHITE
	);
	leftArrow.setValue
	(
		500, 500, 100, 100,
		GREEN, DARK_GREEN, ALUMINUM
	);
	rightArrow.setValue
	(
		700, 500, 100, 100,
		GREEN, DARK_GREEN, ALUMINUM
	);
}

void UIManager::mouseLeftClicked(int mouseX, int mouseY)
{
	if(exitButton.isMouseOver(mouseX, mouseY))
		exitButtonLeftClicked();
	else if(leftArrow.isMouseOver(mouseX, mouseY))
		leftArrowLeftClicked();
	else if(rightArrow.isMouseOver(mouseX, mouseY))
		rightArrowLeftClicked();
}
void UIManager::passiveMouseMotion(int mouseX, int mouseY)
{
	exitButton.isMouseOver(mouseX, mouseY);
	userManualButton.isMouseOver(mouseX, mouseY);
	leftArrow.isMouseOver(mouseX, mouseY);
	rightArrow.isMouseOver(mouseX, mouseY);
}

bool UIManager::getButtonOver(TypeButtonOver button, int mouseX, int mouseY)
{
	switch (button)
	{
	case LEFT_ARROW_BUTTON:
		return leftArrow.isMouseOver(mouseX, mouseY);
	case RIGHT_ARROW_BUTTON:
		return rightArrow.isMouseOver(mouseX, mouseY);
	default:
		break;
	}
}
void UIManager::leftArrowLeftClicked()
{
	cout << "leftArrow clicked" << endl;
}
void UIManager::rightArrowLeftClicked()
{
	cout << "rightArrow clicked" << endl;
}
void UIManager::exitButtonLeftClicked()
{
	exit(0);
}
void UIManager::draw2DUI()
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
	//drawViewport();
	exitButton.draw("EXIT");
	userManualButton.draw("User Manual");
	leftArrow.draw("<-");
	rightArrow.draw("->");

	// Khôi phục projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void UIManager::drawViewport()
{
	setColor(ALUMINUM);
	glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, VIEWPORT_HEIGHT);
        glVertex2f(WINDOW_WIDTH, VIEWPORT_HEIGHT);
        glVertex2f(WINDOW_WIDTH, 0);
    glEnd();

}

UIManager::~UIManager(){}
Button::~Button(){}
