#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <utility>

#include "Utils.h"
#include "Config.h"

#ifndef ROBOTARM_H
#define ROBOTARM_H

class RobotHead
{
    public:
    RobotHead();
    ~RobotHead();
    void drawHead();
    void setDirection(Vector other);
    private:
    float headRadius;
    float headZPosition;

    Color head_Color;

    Point centerHeadPoint;

    Vector normal;
    Vector direction;
};

class RobotArm
{
public:
    RobotArm();
    ~RobotArm();
    void draw();
    void drawRobotBody();
    void drawRobotJoint();
    void drawRobotShortArm();
    void drawRobotLongArm();
    void drawRobotHand();
    void drawContainer();
    void drawDirection();
    void printAttributes();
    bool checkHandClaw();
    void checkMinValueAngle();
    void checkMaxValueAngle();
    void printAttributeToTxt();
    void update();
    void test();

    void rotateAngle(TypeAngle angle, float rotate);
    void changeStatus(TypeStatus status);

    bool getStatus(TypeStatus status);
    Vector getVector(TypeVector v);
    float getAngle(TypeAngle a);

private:
    //special
    RobotHead head;
    bool showDirection;
    bool showRobot;
    bool isHandOpen;
    bool isLeftHandClaw;
    bool isRightHandClaw;
    bool canLeftHandClaw;
    bool canRightHandClaw;
    //base
    float angleX;
    float angleZ;
    float bodyRadius;
    float bodyHeight;
    float bodyZPosition;
    //joint
    float jointZPosition;
    float jointRadius;
    //short arm
    float angleLeftShortArm;
    float angleRightShortArm;
    float shortArmDistanceVertical;
    float shortArmDistanceHorizontal;
    float shortArmLength;
    float shortArmRadius;
    //longArm
    float angleXLeftLongArm;
    float angleXRightLongArm;
    float angleZLeftLongArm;
    float angleZRightLongArm;
    float hingeRadius;
    float longArmRadius;
    float longArmLength;
    //hand
    float wristRadius;
    float fingerRadius;
    float fingerHeight;
    float fingerThickness;
    float fingerDistance;
    pair<float, float> angleFingerLeftHand1_Open;
    pair<float, float> angleFingerRightHand1_Open;
    pair<float, float> angleFingerLeftHand2_Open;
    pair<float, float> angleFingerRightHand2_Open;
    pair<float, float> angleFingerLeftHand1_Close;
    pair<float, float> angleFingerRightHand1_Close;
    pair<float, float> angleFingerLeftHand2_Close;
    pair<float, float> angleFingerRightHand2_Close;

    //container
    float containerLength;
    double distanceContainerToLeft;
    double distanceContainerToRight;

    Color body_Color;
    Color body_OutlineColor;
    Color joint_Color;
    Color joint_OutlineColor;
    Color shortArm_Color;
    Color shortArm_OutlineColor;
    Color hinge_Color;
    Color hinge_OutlineColor;
    Color longArm_Color;
    Color longArm_OutlineColor;
    Color wrist_Color;
    Color wrist_OutlineColor;
    Color fingerDisableClaw_Color;
    Color fingerDisableClaw_OutlineColor;
    Color container_Color;
    Color container_OutlineColor;

    Vector normalBase; // (0,0,1)
    Vector robotDirectionXY_Vertical;// lam goc cho tat ca vector khac;
    Vector robotDirectionXY_Horizontal;
    Vector robotDirectionXYZ;
    Vector leftShortArmDirection;
    Vector rightShortArmDirection;
    Vector leftLongArmDirection;
    Vector rightLongArmDirection;
    Vector leftHandDirection;
    Vector rightHandDirection;
    Vector othorgonalLeftHandDirection;
    Vector othorgonalRightHandDirection;
    Vector containerDirection;

    Point centerBodyPoint;
    Point leftArmJointPoint;
    Point rightArmJointPoint;
    Point leftShortArmPoint;
    Point rightShortArmPoint;
    Point leftHingePoint;
    Point rightHingePoint;
    Point leftLongArmPoint;
    Point rightLongArmPoint;
    Point leftWristPoint;
    Point rightWristPoint;
    Point centerLeftHandPoint;
    Point centerRightHandPoint;
    Point fingerLeftHand1Point;
    Point fingerLeftHand2Point;
    Point fingerRightHand1Point;
    Point fingerRightHand2Point;
    Point containerPoint;
};

#endif
