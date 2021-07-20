#pragma once

#include "PageManager.h"

class GAME : public CANVAS
{
public:
};

enum GAMESTATE
{
    LOADING,
    SETTINGS,
    PLAY,
    END
};

class Point
{
public:
    uint16 gx;
    uint16 gy;
    Point(uint16 x, uint16 y)
    {
        gx = x;
        gy = y;
    }
};

class BOUNDINGBOX
{
public:
    uint16 bbx;
    uint16 bby;
    uint16 bbw;
    uint16 bbh;
    BOUNDINGBOX()
    {
    }
    BOUNDINGBOX(uint16 x, uint16 y, uint16 w, uint16 h)
    {
        bbx = x;
        bby = y;
        bbw = w;
        bbh = h;
    }

    Point getUL_Point()
    {
        return Point(bbx, bby + bbh);
    }
    Point getUR_Point()
    {
        return Point(bbx + bbw, bby + bbh);
    }
    Point getOL_Point()
    {
        return Point(bbx, bby);
    }
    Point getOR_Point()
    {
        return Point(bbx + bbw, bby);
    }
    bool intersects(BOUNDINGBOX bb)
    {
        return bb.isOverlapping(getOL_Point()) || bb.isOverlapping(getOR_Point()) ||
               bb.isOverlapping(getUL_Point()) || bb.isOverlapping(getUR_Point());
    }
    bool isOverlapping(Point p)
    {
        uint16 x = p.gx;
        uint16 y = p.gy;

        Serial.print(x);
        Serial.print(" >= ");
        Serial.print(bbx);
        Serial.print(" | ");
        Serial.print(x >= bbx);
        Serial.print("   |   ");
        Serial.print(x);
        Serial.print(" <= ");
        Serial.print(bbx + bbw);
        Serial.print(" | ");
        Serial.print(x <= bbx + bbw);
        Serial.print("   |   ");
        Serial.print(y);
        Serial.print(" >= ");
        Serial.print(bby);
        Serial.print(" | ");
        Serial.print(y <= bby);
        Serial.print("   |   ");
        Serial.print(y);
        Serial.print(" <= ");
        Serial.print(bby + bbh);
        Serial.print(" | ");
        Serial.print(y <= bby + bbh);

        return (
            x >= bbx &&
            x <= bbx + bbw &&
            y >= bby &&
            y <= bby + bbh);
    }
    //
    void show(Adafruit_ILI9341 tft, int r, int g, int b)
    {
        tft.fillRect(bbx, bby, bbw, bbw, tft.color565(r, g, b));
        Point corners[] = {getOL_Point(), getOR_Point(), getUL_Point(), getUR_Point()};
        for (int index = 0; index <= 3; index++)
        {
            Point p = corners[index];
            tft.fillCircle(p.gx, p.gy, 2, tft.color565(abs(255 - r), abs(255 - g), abs(255 - b)));
        }
    }
};