#pragma once

#include "Adafruit_ILI9341.h"
#include "Utils.h"

class CANVAS
{
public:
    virtual void drawScreen(Adafruit_ILI9341 tft, long frame);
    virtual void handleJoyStick(int x, int y, double angle);
    virtual void handleBTN1();
    virtual void handleBTN2();
};
