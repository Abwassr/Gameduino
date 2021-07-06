#include <Arduino.h>
#include "display/PageManager.h"
#include "Utils.h"

int *getBBoxOfText(Adafruit_ILI9341 tft, String text)
{
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    static int returner[] = {w, h, (HALF_LCD_WIDTH - w / 2), (HALF_LCD_HEIGHT - h / 2)};

    return returner;
}

int *getJoyStickPos()
{

    static int returner[] = {0, 0};

    return returner;
}

Direction getJoyStickDirection()
{
    double angle = getJoyStickAngle();
    if (angle == -1000)
    {
        return TO_WEAK;
    }
    if (angle < -157.5 || angle > 157.5)
    {
        return SOUTH;
    }
    if (angle < -157.5 && angle > -112.5)
    {
        return SOUTH_WEST;
    }
    if (angle < -112.5 && angle > -67.5)
    {
        return WEST;
    }
    if (angle < -67.5 && angle > -22.5)
    {
        return WEST_NORTH;
    }
    if (angle > -22.5 && angle < 22.5)
    {
        return NORTH;
    }
    if (angle > 22.5 && angle < 67.5)
    {
        return NORTH_EAST;
    }
    if (angle > 67.5 && angle < 112.5)
    {
        return EAST;
    }
    if (angle > 112.5 && angle < 157.5)
    {
        return EAST_SOUTH;
    }
    return UNDEFINED;
}
double getJoyStickAngle()
{
    int *pos = getJoyStickPos();
    int x = pos[0];
    int y = pos[1];
    if (abs(x) > 50 || abs(y) > 50)
    {
        double angle = (double)(atan((double)y / (double)x) * (double)180 / (double)3.1415);
        return normalizeAngle(angle);
    }
    return -1000;
}

double normalizeAngle(double angle)
{
    if (angle > 180)
    {
        return normalizeAngle(angle - 360);
    }
    if (angle < -180)
    {
        return normalizeAngle(angle + 360);
    }
    return angle;
}
