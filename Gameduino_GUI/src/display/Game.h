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
    BOUNDINGBOX(int x, int y, int w, int h)
    {
        bbx = x;
        bby = y;
        bbw = w;
        bbh = h;
    }
    Point *getCorners()
    {
        Point *ol = new Point(bbx, bby);
        Point *por = new Point(bbx + bbw, bby);
        Point *ul = new Point(bbx, bby + bbh);
        Point *ur = new Point(bbx + bbw, bby + bbh);
        static Point returner[] = {*ol, *por, *ul, *ur};
        return returner;
    }
    bool isOverlapping(Point p)
    {
        int x = p.gx;
        int y = p.gy;
        return (x >= bbx && x <= bbx + bbw && y >= bby && y <= bby + bbh);
    }
    //
    void show(Adafruit_ILI9341 tft, int r, int g, int b)
    {
        tft.fillRect(bbx, bby, bbw, bbw, tft.color565(r, g, b));
        Point *corners = getCorners();
        for (int index = 0; index <= 3; index++)
        {
            Point p = corners[index];
            tft.fillCircle(p.gx, p.gy, 2, tft.color565(abs(255 - r), abs(255 - g), abs(255 - b)));
        }
    }
};