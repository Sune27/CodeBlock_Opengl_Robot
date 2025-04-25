#include "../include/Robot.h"

using namespace std;

int Robot_Parts::ID_Number = -1;
float Robot_Parts::angleX = 125;
Vector Robot_Parts::normalBase = {0, 0, 1};
Vector Robot_Parts::robotDirectionXY_Vertical = {0, 0, 0};
Vector Robot_Parts::robotDirectionXY_Horizontal = {0, 0, 0};
void Robot::drawEverything()
{
    for(auto& part : robotParts)
    {
        part->draw();
    }
    for(auto it : listID)
    {
        cout << "Name: " << it.first << " ID: " << it.second << endl;
    }
}


void Robot_Parts::draw(){};
void Robot_Head::draw()
{
    glPushMatrix();
    drawSolidSphere(robotHead_Point, headRadius, head_Color);
    glPopMatrix();
}
void Robot_Body::draw()
{
    drawCylinderWithCaps(bodyRadius, bodyHeight, bodyRadius, body_Point, normalBase, body_Color);
    drawCylinderOutline(bodyRadius, bodyHeight, body_Point, normalBase, body_OutlineColor);
}
void Robot_Wheel::draw()
{
    cout << "draw wheel" << endl;
}

Robot::Robot()
{
    unique_ptr<Robot_Head> head = make_unique<Robot_Head>(HEAD_ID, HEAD_RADIUS, HEAD_COLOR);
    listID[HEAD_ID] = Robot_Parts::getID_Number();

    unique_ptr<Robot_Body> body = make_unique<Robot_Body>(BODY_ID, BODY_RADIUS, BODY_HEIGHT, BODY_COLOR, BODY_OUTLINECOLOR);
    listID[BODY_ID] = Robot_Parts::getID_Number();

    robotParts.push_back(move(head));
    robotParts.push_back(move(body));

}
void Robot::update()
{
    Robot_Parts::robotDirectionXY_Vertical.vertical(Robot_Parts::angleX);
    Robot_Parts::robotDirectionXY_Horizontal.horizontal(Robot_Parts::robotDirectionXY_Vertical);

}
Robot_Parts::Robot_Parts()
{
    ID_Number++;
}
Robot_Head::Robot_Head(string ID, float radius, Color color)
{
    this->ID = ID;
    this->headRadius = radius;
    robotHead_Point.setValue(0, 0, HEAD_Z_POSITION);
    this->head_Color = color;
}
Robot_Wheel::Robot_Wheel()
{
    init();
}
Robot_Body::Robot_Body(string ID, float radius, float height, Color color, Color outline)
{
    this->ID = ID;
    this->bodyRadius = radius;
    this->bodyHeight = height;
    this->body_Color = color;
    this->body_OutlineColor = outline;
    body_Point.setValue(0, 0, BODY_Z_POSITION);
}
Robot_Joint::Robot_Joint(){}
void Robot_Head::init()
{
    cout << "Init Robot Head class" << endl;
}
void Robot_Body::init()
{
    cout << "Init Robot Body class" << endl;
}
void Robot_Wheel::init()
{
    cout << "Init Robot Wheel class" << endl;
}
void Robot_Joint::init()
{}
Robot::~Robot(){}
Robot_Parts::~Robot_Parts(){}
Robot_Head::~Robot_Head(){}
Robot_Wheel::~Robot_Wheel(){}
Robot_Body::~Robot_Body(){}
Robot_Joint::~Robot_Joint(){}
int Robot_Parts::getID_Number()
{
    return ID_Number;
}
