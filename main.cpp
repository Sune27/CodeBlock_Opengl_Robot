#include <bits/stdc++.h>
#include <GL/glut.h>
#include "include/Config.h"
#include "include/Utils.h"
#include "include/Console.h"
#include "include/RobotArm.h"
#include "include/UserInterface.h"
using namespace std;
//dcm thang nghia
//dcm sifu

RobotArm robotArm;
UIManager uiManager;
vector<bool> keys(256, false);
vector<bool> specialKeys(256, false);
float cameraAngle = 0;

void display();
void reshape(int, int);
void keyboardFunc(unsigned char, int, int);
void keyboardUpFunc(unsigned char, int, int);
void specialFunc(int, int, int);
void specialUpFunc(int, int, int);
void mouseFunc(int, int, int, int);
void passiveMouseMotion(int, int);

void checkEventKeyboard();
void checkEventSpecialKeys();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Project");
	hideCursor();

	glEnable(GL_DEPTH_TEST);

	//event
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialFunc);
	glutSpecialUpFunc(specialUpFunc);
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(passiveMouseMotion);
	//glutMotionFunc();
	//glutIdleFunc();
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

void display()
{
	setCursorPosition(0, 0);
	cout << __TIME__ << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt
	(
		eyeX*cos(cameraAngle), eyeY*sin(cameraAngle), eyeZ,
		centerX, centerY, centerZ,
		upX, upY, upZ
	);

	robotArm.draw();
	uiManager.draw2DUI();
	checkEventKeyboard();
	checkEventSpecialKeys();

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);

}
void keyboardFunc(unsigned char key, int x, int y)
{

	if(key == 32)
		robotArm.changeStatus(HAND_OPEN);
	else if(key == '=')
		robotArm.changeStatus(SHOW_DIRECTION);
	else if(key == '+')
	{
		if(robotArm.getStatus(RIGHT_HAND_CLAWING) == false)
		robotArm.changeStatus(LEFT_HAND_CLAWING);
	}
	else keys[key] = true;
}
void keyboardUpFunc(unsigned char key, int x, int y)
{
	keys[key] = false;
}
void mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
	{
        if (state == GLUT_DOWN)
		{
			if(uiManager.getButtonOver(LEFT_ARROW_BUTTON, x, y) == true)
			{
				keys['z'] = true;
			}
			else if(uiManager.getButtonOver(RIGHT_ARROW_BUTTON, x, y) == true)
			{
				keys['x'] = true;
			}
			else
			{
				uiManager.mouseLeftClicked(x, y);
			}
        } else if (state == GLUT_UP)
		{
			if(uiManager.getButtonOver(LEFT_ARROW_BUTTON, x, y) == true)
			{
				keys['z'] = false;
			}
			else if(uiManager.getButtonOver(RIGHT_ARROW_BUTTON, x, y) == true)
			{
				keys['x'] = false;
			}
        }
        glutPostRedisplay(); // Vẽ lại
    }
}

void passiveMouseMotion(int x, int y)
{
	uiManager.passiveMouseMotion(x, y);
}

void checkEventKeyboard()
{
	if(keys[27])
		exit(0);
	if(keys['6'])
		robotArm.rotateAngle(ANGLEZ_RIGHT_LONG_ARM, ROTATE);
	if(keys['3'])
		robotArm.rotateAngle(ANGLEZ_RIGHT_LONG_ARM, -ROTATE);
	if(keys['e'])
		robotArm.rotateAngle(ANGLEZ_LEFT_LONG_ARM, ROTATE);
	if(keys['d'])
		robotArm.rotateAngle(ANGLEZ_LEFT_LONG_ARM, -ROTATE);
	if(keys['5'])
		robotArm.rotateAngle(ANGLEX_RIGHT_LONG_ARM, ROTATE);
	if(keys['2'])
		robotArm.rotateAngle(ANGLEX_RIGHT_LONG_ARM, -ROTATE);
	if(keys['w'])
		robotArm.rotateAngle(ANGLEX_LEFT_LONG_ARM, ROTATE);
	if(keys['s'])
		robotArm.rotateAngle(ANGLEX_LEFT_LONG_ARM, -ROTATE);
	if(keys['-'])
		robotArm.changeStatus(SHOW_OBJECT_STATUS);
	if(keys['q'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, ROTATE);
	if(keys['a'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, -ROTATE);
	if(keys['4'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, ROTATE);
	if(keys['1'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, -ROTATE);
	if(keys['z'])
		robotArm.rotateAngle(ANGLE_X, ROTATE);
	if(keys['x'])
		robotArm.rotateAngle(ANGLE_X, -ROTATE);

	robotArm.checkMinValueAngle();
	robotArm.checkMaxValueAngle();
	glutPostRedisplay();
}

void specialUpFunc(int key, int x, int y)
{
    specialKeys[key] = false;
}
void specialFunc(int key, int x, int y)
{
	if(key == GLUT_KEY_F1)
	{
		if(robotArm.getStatus(LEFT_HAND_CLAWING) == false)
		robotArm.changeStatus(RIGHT_HAND_CLAWING);
	}
	else
	{
		specialKeys[key] = true;
	}
}
void checkEventSpecialKeys()
{
	float rotate = 0.01;

	if(specialKeys[GLUT_KEY_LEFT])
		normalizeAngle(cameraAngle += rotate);
	if(specialKeys[GLUT_KEY_RIGHT])
		normalizeAngle(cameraAngle -= rotate);

}
