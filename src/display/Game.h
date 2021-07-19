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
    Point(int x, int y)
    {
        gx = x;
        gy = y;
    }
    int gx;
    int gy;
};

class BOUNDINGBOX
{
public:
    int bbx;
    int bby;
    int bbw;
    int bbh;
    BOUNDINGBOX()
    {
    }
    BOUNDINGBOX(int x, int y, int w, int h)
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
        int x = p.gx;
        int y = p.gy;

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