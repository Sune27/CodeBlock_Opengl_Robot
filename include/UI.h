#include <GL/glut.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "UI_Attributes.h"
using namespace std;

#ifndef UI_H
#define UI_H

class UI_Elements
{
    public:
        UI_Elements();
        ~UI_Elements();
        virtual void draw() = 0;
        virtual void buttonOver(int mouseX, int mouseY);
        virtual bool getStatusHovered();
        virtual void setStatusHovered(bool status);
        virtual bool getDisable();
        virtual void setDisable(bool status);
        virtual void setPosition(int x, int y);
    private:
        bool disable;
};


class Label : public UI_Elements 
{
    public:
        Label();
        Label(int x, int y, string text, Color color, Color hoverColor);
        ~Label();
        void setPosition(int, int);
        void setStatusHovered(bool status) override;
        void draw() override;
    private:
        int x, y;
        string text;
        Color color, hoverColor;
        bool isButtonHovered;
};

class Button : public UI_Elements
{
    public:
        Button();
        Button(int x, int y, int width, int height, Color background, Color background_hover);
        ~Button();
        void draw() override;
        void buttonOver(int mouseX, int mouseY) override;
        bool getStatusHovered() override;
        bool getDisable() override;
        void setDisable(bool status) override;
        void setPosition(int x, int y) override;
    private:
        int x, y, width, height;
        Color background, background_hover;
        bool isHovered;
        bool isDisable;
};

class Symbol : public UI_Elements
{
    public:
        Symbol();
        Symbol(int x, int y, int width, int height, string type);
        ~Symbol();
        void setStatusHovered(bool status) override;
        void draw() override;
        void setPosition(int, int) override;
    private:
        int x, y, width, height;
        Color color, hoverColor;
        bool isButtonHovered;
        string type;
};
class Checkbox : public UI_Elements
{
    public:
        Checkbox();
        ~Checkbox();
    private:
};

class UI_Manager
{
    public:
        unordered_map<UIObject, unique_ptr<UI_Elements>> UI_Maps;
        UI_Manager();
        ~UI_Manager();
        void draw();
        void checkAllButtonOver(int mouseX, int mouseY);
    private:

};

#endif