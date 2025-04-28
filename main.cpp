#include <bits/stdc++.h>
#include <GL/glut.h>
#include "include/Config.h"
#include "include/Utils.h"
#include "include/Console.h"
#include "include/RobotArm.h"
#include "include/UI.h"
using namespace std;

RobotArm robotArm;
UI_Manager widget;
vector<bool> keys(256, false);
vector<bool> specialKeys(256, false);
float cameraAngle = 0;
float cameraAngleZ = 0;

//test
int lastMouseX = 0;
int lastMouseY = 0;
bool isDragging = false;
bool changed = false;
bool thirdPerspective = true;

void display();
void reshape(int, int);
void keyboardFunc(unsigned char, int, int);
void keyboardUpFunc(unsigned char, int, int);
void specialFunc(int, int, int);
void specialUpFunc(int, int, int);
void mouseFunc(int, int, int, int);
void passiveMouseMotion(int, int);
void motion(int, int);
void update(int);

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
	glutMotionFunc(motion);
	glutTimerFunc(0, update, 0);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

void display()
{
	setCursorPosition(0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(thirdPerspective == true)
	{
		gluLookAt
		(
			eyeX*cos(cameraAngle), eyeY*sin(cameraAngle), eyeZ+cameraAngleZ,
			robotArm.getCenterPoint().arr[0], robotArm.getCenterPoint().arr[1], robotArm.getCenterPoint().arr[2],
			upX, upY, upZ
		);
	}
	else
	{
		Point eye = robotArm.getCenterHeadPoint();
		eye.move(robotArm.getVector(ROBOTDIRECTIONXY_VERTICAL), 5);
		Point center = eye;
		center.move(robotArm.getVector(ROBOTDIRECTIONXY_VERTICAL), -10);
		gluLookAt(
			eye.arr[0], eye.arr[1], eye.arr[2],
			center.arr[0], center.arr[1], center.arr[2],
			upX, upY, upZ
		);
	}
	robotArm.draw();
	widget.draw();
	checkEventKeyboard();
	checkEventSpecialKeys();

	glFlush();
	glutSwapBuffers();
}

void update(int value)
{
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

	if(key == '=')
		robotArm.changeStatus(SHOW_DIRECTION);
	else if(key == '+')
	{
		if(robotArm.getStatus(RIGHT_HAND_CLAWING) == false)
		robotArm.changeStatus(LEFT_HAND_CLAWING);
	}
	else if(key == '-')
    {
        robotArm.changeStatus(SHOW_OBJECT_STATUS);
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
			if(widget.UI_Maps[UIObject::EXIT_BUTTON_UI]->getStatusHovered())
			{
				exit(0);
			}
			else if(widget.UI_Maps[UIObject::Q_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['q'] = true;
			}
			else if(widget.UI_Maps[UIObject::A_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['a'] = true;
			}
			else if(widget.UI_Maps[UIObject::W_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['w'] = true;
			}
			else if(widget.UI_Maps[UIObject::S_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['s'] = true;
			}
			else if(widget.UI_Maps[UIObject::E_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['e'] = true;
			}
			else if(widget.UI_Maps[UIObject::D_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['d'] = true;
			}
			else if(widget.UI_Maps[UIObject::ONE_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['1'] = true;
			}
			else if(widget.UI_Maps[UIObject::TWO_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['2'] = true;
			}
			else if(widget.UI_Maps[UIObject::THREE_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['3'] = true;
			}
			else if(widget.UI_Maps[UIObject::FOUR_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['4'] = true;
			}
			else if(widget.UI_Maps[UIObject::FIVE_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['5'] = true;
			}
			else if(widget.UI_Maps[UIObject::SIX_KEYBOARD_BUTTON_UI]->getStatusHovered())
			{
				keys['6'] = true;
			}

			else if(widget.UI_Maps[UIObject::LEFT_ARROW_BUTTON_UI]->getStatusHovered())
			{
				specialKeys[GLUT_KEY_LEFT] = true;
			}
			else if(widget.UI_Maps[UIObject::RIGHT_ARROW_BUTTON_UI]->getStatusHovered())
			{
				specialKeys[GLUT_KEY_RIGHT] = true;
			}
			else if(widget.UI_Maps[UIObject::UP_ARROW_BUTTON_UI]->getStatusHovered())
			{
				specialKeys[GLUT_KEY_UP] = true;
			}
			else if(widget.UI_Maps[UIObject::DOWN_ARROW_BUTTON_UI]->getStatusHovered())
			{
				specialKeys[GLUT_KEY_DOWN] = true;
			}
			else if(
				widget.UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->getStatusHovered()
			&& widget.UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->getDisable() == false
			&& robotArm.getStatus(RIGHT_HAND_CLAWING) == false
			)
			robotArm.changeStatus(LEFT_HAND_CLAWING);
			else if(
				widget.UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->getStatusHovered()
			&& widget.UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->getDisable() == false
			&& robotArm.getStatus(LEFT_HAND_CLAWING) == false
			)
			robotArm.changeStatus(RIGHT_HAND_CLAWING);
			else{
                isDragging = true;
                lastMouseX = x;
                lastMouseY = y;
			}

        }
		else if (state == GLUT_UP)
		{
			isDragging = false;
			specialKeys[GLUT_KEY_LEFT] = false;
			specialKeys[GLUT_KEY_RIGHT] = false;
			specialKeys[GLUT_KEY_UP] = false;
			specialKeys[GLUT_KEY_DOWN] = false;
			keys['1'] = false;
			keys['2'] = false;
			keys['3'] = false;
			keys['4'] = false;
			keys['5'] = false;
			keys['6'] = false;
			keys['q'] = false;
			keys['a'] = false;
			keys['s'] = false;
			keys['w'] = false;
			keys['e'] = false;
			keys['d'] = false;
        }
        glutPostRedisplay(); // Vẽ lại
    }
}

void passiveMouseMotion(int x, int y)
{
	widget.checkAllButtonOver(x,y);
	// cout << "mouseX: " << x << endl;
	// cout << " mouseY: " << y << endl;
	//widget.UI_Maps[Q_KEYBOARD_LABEL_UI]->setPosition(x, y);
}

void motion(int x, int y)
{
    if (isDragging) {
        // Tính độ dịch chuyển chuột
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Cập nhật góc camera
        cameraAngle += deltaX * 0.01;  // Điều chỉnh tốc độ xoay
        cameraAngleZ += deltaY * 0.1;
		if(cameraAngleZ <= CAMERA_ANGLE_Z_MIN) cameraAngleZ = CAMERA_ANGLE_Z_MIN;


        // Lưu vị trí chuột hiện tại
        lastMouseX = x;
        lastMouseY = y;

        // Yêu cầu vẽ lại
        glutPostRedisplay();
    }
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
	if(keys['q'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, ROTATE);
	if(keys['a'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, -ROTATE);
	if(keys['4'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, ROTATE);
	if(keys['1'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, -ROTATE);

	for(int i = (int)'a'; i < (int)'z'; ++i)
	{
		cout << (char)i << ": " << keys[i] << endl;
	}
	widget.UI_Maps[UIObject::LEFT_HAND_BUTTON_UI]->setDisable(!robotArm.getStatus(CAN_LEFT_HAND_CLAW));
	widget.UI_Maps[UIObject::RIGHT_HAND_BUTTON_UI]->setDisable(!robotArm.getStatus(CAN_RIGHT_HAND_CLAW));
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
		thirdPerspective = !thirdPerspective;
		robotArm.changeStatus(PERSPECTIVE);
	}
	else
	{
		specialKeys[key] = true;
	}
}
void checkEventSpecialKeys()
{
	if(specialKeys[GLUT_KEY_RIGHT])
		robotArm.rotateAngle(ANGLE_X, ROTATE);
	if(specialKeys[GLUT_KEY_LEFT])
		robotArm.rotateAngle(ANGLE_X, -ROTATE);
	if(specialKeys[GLUT_KEY_UP])
	{
		//robotArm.rotateAngle(ANGLE_WHEEL, ROTATE);
		robotArm.move(-0.2);
	}
	if(specialKeys[GLUT_KEY_DOWN])
	{
		//robotArm.rotateAngle(ANGLE_WHEEL, ROTATE);
		robotArm.move(0.2);
	}
}
