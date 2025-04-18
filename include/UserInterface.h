#include <GL/glut.h>
#include "Config.h"
#include "Utils.h"

using namespace std;

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


class Button
{
public:
	Button();
	~Button();
	void setValue(float, float, float, float, Color, Color, Color);
	void draw(const char* text);
	bool isMouseOver(int mouseX, int mouseY);
private:
	float x, y, width, height;
	Color background;
	Color backgroundHover;
	Color textColor;
	bool isHover;
};

class UIManager
{
public:
	UIManager();
	~UIManager();
	void draw2DUI();
	void passiveMouseMotion(int mouseX, int mouseY);
	void mouseLeftClicked(int mouseX, int mouseY);
	void drawViewport();
	bool getButtonOver(TypeButtonOver button, int mouseX, int mouseY);
	void exitButtonLeftClicked();
	void rightArrowLeftClicked();
	void leftArrowLeftClicked();
private:
	Button exitButton;
	Button userManualButton;
	Button leftArrow;
	Button rightArrow;
};

#endif
