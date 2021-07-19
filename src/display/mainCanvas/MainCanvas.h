#pragma once

#include "../Canvas.h"

class MAIN_CANVAS : public CANVAS
{
public:
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y, double angle);
    void handleBTN1();
    void handleBTN2();
    void onSelect();

private:
    int page = 0;
};
MAIN_CANVAS *getMainCanvasInstance();

class MAIN_MENU_ENTRY
{
public:
    virtual void drawPage(Adafruit_ILI9341 tft, long frame);
    virtual void onSelect();
};