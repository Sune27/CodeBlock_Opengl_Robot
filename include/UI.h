#include <GL/glut.h>
#include <memory>
#include <unordered_map>
#include "Config.h"
#include "Utils.h"

#ifndef UI_H
#define UI_H

class Icon : public UI_Elements
{
public:
private:
};

class Label : public UI_Elements 
{
public:
private:
};

class Button : public UI_Elements
{
public:
private:
};

class UI_Elements
{
public:
    UI_Elements();
    ~UI_Elements();
    virtual void draw();
private:
};

class UI_Manager
{
public:
    UI_Manager();
    ~UI_Manager();
private:
};

#endif